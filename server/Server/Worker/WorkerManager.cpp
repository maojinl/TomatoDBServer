#include "stdafx.h"

#include "WorkerManager.h"
#include "Ini.h"
#include "WorkerPlayerManager.h"
#include "ServerManager.h"
#include "MachineManager.h"


WorkerManager* g_pWorkerManager=nullptr ;

/////////////////////////////////////////////////////////////////////////////////
//
//	WorkerManager
//
/////////////////////////////////////////////////////////////////////////////////
WorkerManager::WorkerManager() : m_Count(0), m_NextWorkerID(0)
{
__ENTER_FUNCTION

	for( INT i=0; i < MAX_WORKER; i++ )
	{
		m_pWorker[i]=nullptr ;
		m_aWorkerPlayerCount[i]=0 ;
	}
__LEAVE_FUNCTION
}

WorkerManager::~WorkerManager( )
{
__ENTER_FUNCTION

	for( INT i=0; i< MAX_WORKER; i++ )
	{
		SAFE_DELETE(m_pWorker[i]) ;
	}
	m_Count = 0 ;

__LEAVE_FUNCTION
}

WorkerID_t WorkerManager::GetNextWorkerID()
{
	__ENTER_FUNCTION

	if ((UINT)m_NextWorkerID >= m_Count)
	{
		m_NextWorkerID = m_NextWorkerID % m_Count;
	}
	WorkerID_t ret = m_NextWorkerID++;
	return ret;

	__LEAVE_FUNCTION
}

Worker* WorkerManager::GetWorker(WorkerID_t WorkerID)
{
__ENTER_FUNCTION

	if( (UINT)WorkerID >=MAX_WORKER )
	{
		return nullptr ;
	}

	return m_pWorker[WorkerID] ;

__LEAVE_FUNCTION

	return nullptr ;
}

_WORKER_DATA* WorkerManager::GetWorkerInfo(WorkerID_t WorkerID)
{
__ENTER_FUNCTION

	Assert(WorkerID != INVALID_ID && WorkerID < MAX_WORKER ) ;

	INT iIndex = g_Config.m_WorkerInfo.m_HashWorker[WorkerID] ;

	return &(g_Config.m_WorkerInfo.m_pWorker[iIndex]) ;

__LEAVE_FUNCTION

	return nullptr ;
}


BOOL WorkerManager::Init( UINT MaxWorkerCount )
{
__ENTER_FUNCTION

	BOOL ret ;

	UINT count = MaxWorkerCount ;

	Assert( count<=MAX_WORKER ) ;

	for( UINT i=0; i<count; i++ )
	{
		WorkerID_t WorkerID = (WorkerID_t)(g_Config.m_WorkerInfo.m_pWorker[i].m_WorkerID) ;
		Assert(WorkerID < MAX_WORKER) ;

		UINT ServerID = g_Config.m_WorkerInfo.m_pWorker[i].m_ServerID ;
		if( ServerID != g_Config.m_ConfigInfo.m_ServerID )
		{
			//not in current server
			continue ;
		}

		Worker* pWorker = new Worker(WorkerID) ;
		Assert( pWorker ) ;

		pWorker->SetWorkerType( g_Config.m_WorkerInfo.m_pWorker[i].m_Type ) ;

		switch( pWorker->GetWorkerType() )
		{
		case WORKER_TYPE_DB_LOGIC://游戏逻辑场景
			{
				//read scn data
				//pWorker->SetLoadData( g_Config.m_WorkerInfo.m_pWorker[i].m_szFileName, load ) ;
				//ret = pWorker->Load( &load ) ;
				//Assert( ret ) ;
				//启动时候创建的场景直接进入运行模式
				//普通游戏场景没有OnWorkerInit事件
				pWorker->SetWorkerStatus( WORKER_STATUS_RUNNING ) ;
			}
			break ;
		default:
			{
				Assert(FALSE) ;
			}
			break; 
		};


		ret = this->AddWorker( pWorker ) ;
		Assert( ret ) ;
	}
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::AddWorker( Worker* pWorker)
{
__ENTER_FUNCTION

	Assert( pWorker ) ;
	if( pWorker==nullptr )
		return FALSE ;

	WorkerID_t WorkerID = pWorker->WorkerID() ;
	Assert( WorkerID < MAX_WORKER ) ;
	
	Assert( m_pWorker[WorkerID]==nullptr ) ;
	m_pWorker[WorkerID] = pWorker ;

	m_Count ++ ;
	Assert( m_Count<MAX_WORKER ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::DelWorker( WorkerID_t WorkerID )
{
__ENTER_FUNCTION

	Assert( WorkerID < MAX_WORKER ) ;
	Assert( m_pWorker[WorkerID] ) ;
	if( m_pWorker[WorkerID] ) 
		return FALSE ;

	m_pWorker[WorkerID] = nullptr ;
	m_Count -- ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::IsInCurServer( WorkerID_t WorkerID )
{
__ENTER_FUNCTION

	_WORKER_DATA* pData = GetWorkerInfo(WorkerID) ;
	Assert( pData ) ;

	if( g_pServerManager->GetServerID()==pData->m_ServerID )
		return TRUE ;

	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::IsInCurMachine( WorkerID_t WorkerID )
{
__ENTER_FUNCTION

    _WORKER_DATA* pData = GetWorkerInfo( WorkerID ) ;
	Assert( pData ) ;

	_SERVER_DATA* pServerData = g_pServerManager->FindServerInfo(pData->m_ServerID) ;
	Assert( pServerData ) ;

	if( g_pMachineManager->GetMachineID() == pServerData->m_MachineID )
		return TRUE ;

	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::BroadCast_Worker(Packet* pMsg) {
  BOOL ret = FALSE;
  for (UINT i = 0, num = 0; num < m_Count && i < MAX_WORKER; i++) {
    if (g_Config.m_WorkerInfo.m_pWorker[i].m_ServerID !=
            g_Config.m_ConfigInfo.m_ServerID) {
      continue;
    }
    if (m_pWorker[i]) {
      ++num;
      ret = m_pWorker[i]->BroadCast_Worker(pMsg);
      if (!ret) {
        return FALSE;
      }
    } else {
      continue;
    }
  }
  return TRUE;
}