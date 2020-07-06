#include "stdafx.h"

#include "ThreadManager.h"
#include "Ini.h"
#include "WorkerThread.h"
#include "WorkerManager.h"
#include "Config.h"



ThreadManager*	g_pThreadManager=NULL ;

ThreadManager::ThreadManager( )
{
__ENTER_FUNCTION

	m_pThreadPool = new ThreadPool ;
	Assert( m_pThreadPool ) ;

	m_pServerThread = new ServerThread ;
	Assert( m_pServerThread ) ;

	m_nThreads = 0 ;

__LEAVE_FUNCTION
}

ThreadManager::~ThreadManager( )
{
__ENTER_FUNCTION

	SAFE_DELETE( m_pThreadPool) ;
	SAFE_DELETE( m_pServerThread) ;

__LEAVE_FUNCTION
}

BOOL ThreadManager::Init( UINT MaxWorkerCount )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;

	//根据配置文件读取需要使用的场景，为每个场景分配一个线程；
	//读取场景数量
	UINT count = MaxWorkerCount ;

	Assert( count<=MAX_WORKER ) ;

	UINT uMaxThreadCount = 0 ;
	UINT i ;
	for( i=0; i<count; i++ )
	{
		//读取场景“i”
		WorkerID_t WorkerID = (WorkerID_t)(g_Config.m_WorkerInfo.m_pWorker[i].m_WorkerID) ;
		Assert( WorkerID<MAX_WORKER ) ;

		UINT ServerID = g_Config.m_WorkerInfo.m_pWorker[i].m_ServerID ;
		if( ServerID != g_Config.m_ConfigInfo.m_ServerID )
		{//不是当前服务器的程序运行的场景
			continue ;
		}

		if( (ID_t)uMaxThreadCount<g_Config.m_WorkerInfo.m_pWorker[i].m_ThreadIndex )
		{
			uMaxThreadCount = g_Config.m_WorkerInfo.m_pWorker[i].m_ThreadIndex ;
		}
	}

	WorkerThread* pWorkerThread=NULL ;
	for( i=0; i<=uMaxThreadCount; i++ )
	{
		pWorkerThread = new WorkerThread ;
		Assert( pWorkerThread ) ;

		ret = m_pThreadPool->AddThread( pWorkerThread ) ;
		Assert( ret ) ;

		m_nThreads ++ ;
	}


	for( i=0; i<count; i++ )
	{
		//读取场景“i”
		WorkerID_t WorkerID = (WorkerID_t)(g_Config.m_WorkerInfo.m_pWorker[i].m_WorkerID) ;
		Assert( WorkerID<MAX_WORKER ) ;

		UINT ServerID = g_Config.m_WorkerInfo.m_pWorker[i].m_ServerID ;
		if( ServerID != g_Config.m_ConfigInfo.m_ServerID )
		{//不是当前服务器的程序运行的场景
			continue ;
		}

		WorkerThread* pWorkerThread = (WorkerThread*)(m_pThreadPool->GetThreadByIndex(g_Config.m_WorkerInfo.m_pWorker[i].m_ThreadIndex)) ;
		if( pWorkerThread==NULL )
		{
			AssertEx(FALSE,"没有创建所需的线程") ;
		}
		else
		{
			Worker* pWorker = g_pWorkerManager->GetWorker(WorkerID) ;

			pWorkerThread->AddWorker( pWorker ) ;
		}
	}

	if( m_pServerThread->IsActive() )
	{
		m_nThreads ++ ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL ThreadManager::Start( )
{
__ENTER_FUNCTION

	BOOL ret ;

	m_pServerThread->start() ;

	MySleep( 500 ) ;

	ret = m_pThreadPool->Start( ) ;
	
	

	return ret ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL ThreadManager::Stop( )
{
__ENTER_FUNCTION

	if( m_pServerThread )
	{
		m_pServerThread->stop( ) ;
	}

	return m_pThreadPool->Stop( ) ;

__LEAVE_FUNCTION

	return FALSE ;
}

