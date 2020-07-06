#include "stdafx.h"

#include "Performance.h"
#include "Worker.h"
#include "WorkerManager.h"
#include "Log.h"
#include "TimeManager.h"
#include "ShareMemManager.h"
#include "SMUManager.h"
#include "ServerManager.h"


PerformanceManager* g_pPerformanceManager=NULL ;

ShareMemoryNotifyer	g_ShareMemNotifyer;

PerformanceManager::PerformanceManager( )
{
__ENTER_FUNCTION

	CleanUp( ) ;

__LEAVE_FUNCTION
}

PerformanceManager::~PerformanceManager( )
{
__ENTER_FUNCTION
__LEAVE_FUNCTION
}

VOID PerformanceManager::CleanUp( )
{
__ENTER_FUNCTION

	m_PerforCount = 0 ;
	
	for( INT i=0; i<MAX_WORKER; i++ )
	{
		m_aHash[i] = INVALID_INDEX ;
	}

__LEAVE_FUNCTION
}

BOOL PerformanceManager::Init( )
{
__ENTER_FUNCTION

	for( INT i=0; i<MAX_WORKER; i++ )
	{
		Worker* pWorker = g_pWorkerManager->GetWorker( (WorkerID_t)i ) ;
		if(pWorker == NULL)
			continue ;

		m_aHash[i] = m_PerforCount ;
		m_aPerforData[m_PerforCount].m_WorkerID = (WorkerID_t)i ;
		m_PerforCount ++ ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL PerformanceManager::HeartBeat( UINT uTime )
{
__ENTER_FUNCTION

#define PERFOR_TIME 30000

	if( !m_OperateTime.IsSetTimer() )
	{
		m_OperateTime.BeginTimer( PERFOR_TIME, uTime ) ;
		return TRUE ;
	}
	if( !m_OperateTime.CountingTimer(uTime) )
	{
		return TRUE ;
	}

	for( INT i=0; i<m_PerforCount; i++ )
	{
		CompareScenePerformance( i ) ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

VOID PerformanceManager::CompareScenePerformance( INT index )
{
__ENTER_FUNCTION

	if( index<0 || index>=MAX_PERFOR_SIZE )
	{
		Assert(FALSE) ;
		return ;
	}

	WORKER_PERFOR* pPerfor = &m_aPerforData[index] ;
	

	Worker* pWorker = g_pWorkerManager->GetWorker( pPerfor->m_WorkerID ) ;
	if( pWorker ==NULL )
	{
		Assert(FALSE) ;
		return ;
	}

	if( pWorker->GetWorkerStatus()!=WORKER_STATUS_RUNNING )
	{//未激活的场景不需要监控
		return ;
	}

	if( memcmp(&pWorker->m_Perfor, pPerfor, sizeof(WORKER_PERFOR) )==0 )
	{//场景锁死，异常

		Log::SaveLog( SERVER_ERRORFILE, "SceneID=%d Dead Lock!", pPerfor->m_WorkerID) ;
		for( INT i=0; i<SPT_NUMBER; i++ )
		{
			Log::SaveLog( SERVER_ERRORFILE, "%d: %d", i, pPerfor->m_aPerfor[i] ) ;
		}
		Log::SaveLog( SERVER_ERRORFILE, "End" ) ;

		return ;
	}

	memcpy( pPerfor, &pWorker->m_Perfor, sizeof(WORKER_PERFOR) ) ;


__LEAVE_FUNCTION
}

BOOL		ShareMemoryNotifyer::HeartBeat(UINT uTime)
{
	__ENTER_FUNCTION

		const _SERVER_DATA*	pCurrentSData =	g_pServerManager->GetCurrentServerInfo();

	if(pCurrentSData->m_EnableShareMem)
	{
		UINT Date = g_pTimeManager->CurrentDate();
		g_HumanSMUPool.SetHeadVer(Date);
	}

	
	
	return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

