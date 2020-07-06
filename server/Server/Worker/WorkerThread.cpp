#include "stdafx.h"


#include "WorkerThread.h"
#include "Log.h"
#include "WorkerManager.h"


WorkerThread::WorkerThread( )
{
__ENTER_FUNCTION

	m_Active = TRUE ;
	m_nWorkerCount = 0 ;
	for( INT i=0; i<MAX_WORKER_PER_THREAD; i++ )
	{
		m_apWorker[i] = NULL ;
	}

__LEAVE_FUNCTION

}

WorkerThread::~WorkerThread( )
{
__ENTER_FUNCTION


__LEAVE_FUNCTION
}

VOID WorkerThread::Quit( )
{
__ENTER_FUNCTION

	for( INT i=0; i<m_nWorkerCount; i++ )
	{
		m_apWorker[i]->GetPlayerManager()->RemoveAllPlayer( ) ;
	}

__LEAVE_FUNCTION
}

VOID WorkerThread::run( )
{
__ENTER_FUNCTION
	
	INT i;

	TID cTid = getTID( ) ;
	for( i=0; i<m_nWorkerCount; i++ )
	{
		m_apWorker[i]->m_ThreadID = cTid ;
	}

	if( m_nWorkerCount==0 )
	{
		Log::SaveLog( SERVER_LOGFILE, "WorkerThread:: no scene add! TID:%d", cTid ) ;
		return ;
	}

	_MY_TRY
	{

		for( i=0; i<m_nWorkerCount; i++ )
		{
			Log::SaveLog( SERVER_LOGFILE, "WorkerThread::run() TID:%d SID:%d SName:%d...", 
				cTid, m_apWorker[i]->WorkerID(), g_pWorkerManager->GetWorkerInfo(m_apWorker[i]->WorkerID())->m_ThreadIndex ) ;
		}

		while( IsActive() )
		{
			for( i=0; i<m_nWorkerCount; i++ )
			{
				BOOL ret = m_apWorker[i]->Tick( ) ;
				Assert( ret ) ;
			}
		}
	}
	_MY_CATCH
	{
		SaveCodeLog( ) ;
	}

	Quit( ) ;


__LEAVE_FUNCTION
}

BOOL WorkerThread::AddWorker(Worker* pScene )
{
__ENTER_FUNCTION

	if( m_nWorkerCount>=MAX_WORKER_PER_THREAD )
	{
		Assert(FALSE) ;
		return FALSE ;
	}

	m_apWorker[m_nWorkerCount] = pScene ;
	m_nWorkerCount ++ ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

