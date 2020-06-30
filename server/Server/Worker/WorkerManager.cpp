#include "stdafx.h"

#include "WorkerManager.h"
#include "Ini.h"
#include "ScenePlayerManager.h"
#include "ServerManager.h"
#include "MachineManager.h"


WorkerManager* g_pWorkerManager=NULL ;

/////////////////////////////////////////////////////////////////////////////////
//
//	WorkerManager
//
/////////////////////////////////////////////////////////////////////////////////
WorkerManager::WorkerManager( )
{
__ENTER_FUNCTION

	for( INT i=0; i < MAX_WORKER; i++ )
	{
		m_pWorker[i]=NULL ;
		m_aScenePlayerCount[i]=0 ;
	}
	m_Count = 0 ;

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

Scene* WorkerManager::GetScene(WorkerID_t WorkerID)
{
__ENTER_FUNCTION

	if( (UINT)WorkerID >=MAX_WORKER )
	{
		return NULL ;
	}

	return m_pWorker[WorkerID] ;

__LEAVE_FUNCTION

	return NULL ;
}

_WORKER_DATA* WorkerManager::GetWorkerInfo(WorkerID_t WorkerID)
{
__ENTER_FUNCTION

	Assert(WorkerID != INVALID_ID && WorkerID < MAX_WORKER ) ;

	INT iIndex = g_Config.m_WorkerInfo.m_HashWorker[WorkerID] ;

	return &(g_Config.m_WorkerInfo.m_pWorker[iIndex]) ;

__LEAVE_FUNCTION

	return NULL ;
}


BOOL WorkerManager::Init( UINT MaxSceneCount )
{
__ENTER_FUNCTION

	BOOL ret ;

	UINT count = MaxSceneCount ;

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

		Scene* pScene = new Scene(WorkerID) ;
		Assert( pScene ) ;

		pScene->SetSceneType( g_Config.m_WorkerInfo.m_pWorker[i].m_Type ) ;

		switch( pScene->GetSceneType() )
		{
		case WORKER_TYPE_DB_LOGIC://游戏逻辑场景
			{
				//read scn data
				//pScene->SetLoadData( g_Config.m_WorkerInfo.m_pWorker[i].m_szFileName, load ) ;
				//ret = pScene->Load( &load ) ;
				//Assert( ret ) ;
				//启动时候创建的场景直接进入运行模式
				//普通游戏场景没有OnSceneInit事件
				pScene->SetSceneStatus( WORKER_STATUS_RUNNING ) ;
			}
			break ;
		default:
			{
				Assert(FALSE) ;
			}
			break; 
		};


		ret = this->AddScene( pScene ) ;
		Assert( ret ) ;
	}
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::AddScene( Scene* pScene )
{
__ENTER_FUNCTION

	Assert( pScene ) ;
	if( pScene==NULL )
		return FALSE ;

	WorkerID_t SceneID = pScene->SceneID() ;
	Assert( SceneID < MAX_WORKER ) ;
	
	Assert( m_pWorker[SceneID]==NULL ) ;
	m_pWorker[SceneID] = pScene ;

	m_Count ++ ;
	Assert( m_Count<MAX_WORKER ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WorkerManager::DelScene( WorkerID_t SceneID )
{
__ENTER_FUNCTION

	Assert( SceneID < MAX_WORKER ) ;
	Assert( m_pWorker[SceneID] ) ;
	if( m_pWorker[SceneID] ) 
		return FALSE ;

	m_pWorker[SceneID] = NULL ;
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

BOOL WorkerManager::IsInCurMachine( WorkerID_t SceneID )
{
__ENTER_FUNCTION

    _WORKER_DATA* pData = GetWorkerInfo( SceneID ) ;
	Assert( pData ) ;

	_SERVER_DATA* pServerData = g_pServerManager->FindServerInfo(pData->m_ServerID) ;
	Assert( pServerData ) ;

	if( g_pMachineManager->GetMachineID() == pServerData->m_MachineID )
		return TRUE ;

	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

WorkerID_t WorkerManager::GetSpecialSceneIDFromCurServer( )//取到一个在当前Server上的游戏逻辑场景
{
__ENTER_FUNCTION

	ID_t CurServerID = g_Config.m_ConfigInfo.m_ServerID ;
	for( INT i=0; i<MAX_WORKER; i++ )
	{
		_WORKER_DATA* pData = GetWorkerInfo( (WorkerID_t)i ) ;
		if( pData==NULL )
			continue ;

		if( CurServerID==pData->m_ServerID )
			return (WorkerID_t)i ;
	}

__LEAVE_FUNCTION

	return INVALID_ID ;
}

BOOL WorkerManager::BroadCast_Scene(Packet* pMsg) {
  BOOL ret = FALSE;
  for (UINT i = 0, num = 0; num < m_Count && i < MAX_WORKER; i++) {
    if (g_Config.m_WorkerInfo.m_pWorker[i].m_ServerID !=
            g_Config.m_ConfigInfo.m_ServerID) {
      continue;
    }
    if (m_pWorker[i]) {
      ++num;
      ret = m_pWorker[i]->BroadCast_Scene(pMsg);
      if (!ret) {
        return FALSE;
      }
    } else {
      continue;
    }
  }
  return TRUE;
}