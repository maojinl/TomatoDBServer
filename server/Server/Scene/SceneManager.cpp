#include "stdafx.h"

#include "SceneManager.h"
#include "Ini.h"
#include "ScenePlayerManager.h"
#include "ServerManager.h"
#include "MachineManager.h"


SceneManager* g_pSceneManager=NULL ;

/////////////////////////////////////////////////////////////////////////////////
//
//	SceneManager
//
/////////////////////////////////////////////////////////////////////////////////
SceneManager::SceneManager( )
{
__ENTER_FUNCTION

	for( INT i=0; i<MAX_SCENE; i++ )
	{
		m_pScene[i]=NULL ;
		m_aScenePlayerCount[i]=0 ;
	}
	m_Count = 0 ;

__LEAVE_FUNCTION
}

SceneManager::~SceneManager( )
{
__ENTER_FUNCTION

	for( INT i=0; i<MAX_SCENE; i++ )
	{
		SAFE_DELETE(m_pScene[i]) ;
	}
	m_Count = 0 ;

__LEAVE_FUNCTION
}

Scene* SceneManager::GetScene( SceneID_t SceneID )
{
__ENTER_FUNCTION

	if( (UINT)SceneID>=MAX_SCENE )
	{
		return NULL ;
	}

	return m_pScene[SceneID] ;

__LEAVE_FUNCTION

	return NULL ;
}

_SCENE_DATA* SceneManager::GetSceneInfo( SceneID_t SceneID )
{
__ENTER_FUNCTION

	Assert( SceneID != INVALID_ID && SceneID < MAX_SCENE ) ;

	INT iIndex = g_Config.m_SceneInfo.m_HashScene[SceneID] ;

	return &(g_Config.m_SceneInfo.m_pScene[iIndex]) ;

__LEAVE_FUNCTION

	return NULL ;
}


BOOL SceneManager::Init( UINT MaxSceneCount )
{
__ENTER_FUNCTION

	BOOL ret ;
	//根据配置文件，读取所有的场景数据
	//读取场景数量
	UINT count = MaxSceneCount ;

	Assert( count<=MAX_SCENE ) ;

	for( UINT i=0; i<count; i++ )
	{
		SceneID_t SceneID = (SceneID_t)(g_Config.m_SceneInfo.m_pScene[i].m_SceneID) ;
		Assert( SceneID<MAX_SCENE ) ;

		UINT ServerID = g_Config.m_SceneInfo.m_pScene[i].m_ServerID ;
		if( ServerID != g_Config.m_ConfigInfo.m_ServerID )
		{//不是当前服务器的程序运行的场景
			continue ;
		}
		if( g_Config.m_SceneInfo.m_pScene[i].m_IsActive==0 )
		{//不是激活的场景
			continue ;
		}

		Scene* pScene = new Scene(SceneID) ;
		Assert( pScene ) ;

		pScene->SetSceneType( g_Config.m_SceneInfo.m_pScene[i].m_Type ) ;

		switch( pScene->GetSceneType() )
		{
		case SCENE_TYPE_GAMELOGIC://游戏逻辑场景
			{
				//read scn data
				//pScene->SetLoadData( g_Config.m_SceneInfo.m_pScene[i].m_szFileName, load ) ;
				//ret = pScene->Load( &load ) ;
				//Assert( ret ) ;
				//启动时候创建的场景直接进入运行模式
				//普通游戏场景没有OnSceneInit事件
				pScene->SetSceneStatus( SCENE_STATUS_RUNNING ) ;
			}
			break ;
		case SCENE_TYPE_COPY://副本场景
			{
				//pScene->SetLoadData( g_Config.m_SceneInfo.m_pScene[i].m_szFileName, pScene->m_SceneLoad ) ;
				//strncpy( pScene->GetMapName(), pScene->m_SceneLoad.m_szMap, _MAX_PATH-1 ) ;
				pScene->SetSceneStatus( SCENE_STATUS_SLEEP ) ;
			}
			break ;
		case SCENE_TYPE_CIT://城市场景
			{
				//pScene->SetLoadData( g_Config.m_SceneInfo.m_pScene[i].m_szFileName, pScene->m_SceneLoad ) ;
				//strncpy( pScene->GetMapName(), pScene->m_SceneLoad.m_szMap, _MAX_PATH-1 ) ;
				//pScene->SetSceneStatus( SCENE_STATUS_SLEEP ) ;
				//pScene->SetLoadData( g_Config.m_SceneInfo.m_pScene[i].m_szFileName, load ) ;
				//ret = pScene->Load( &load ) ;
				//Assert( ret ) ;
				//启动时候创建的场景直接进入运行模式
				//普通游戏场景没有OnSceneInit事件
				pScene->SetSceneStatus( SCENE_STATUS_RUNNING ) ;
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

BOOL SceneManager::AddScene( Scene* pScene )
{
__ENTER_FUNCTION

	Assert( pScene ) ;
	if( pScene==NULL )
		return FALSE ;

	SceneID_t SceneID = pScene->SceneID() ;
	Assert( SceneID < MAX_SCENE ) ;
	
	Assert( m_pScene[SceneID]==NULL ) ;
	m_pScene[SceneID] = pScene ;

	m_Count ++ ;
	Assert( m_Count<MAX_SCENE ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL SceneManager::DelScene( SceneID_t SceneID )
{
__ENTER_FUNCTION

	Assert( SceneID < MAX_SCENE ) ;
	Assert( m_pScene[SceneID] ) ;
	if( m_pScene[SceneID] ) 
		return FALSE ;

	m_pScene[SceneID] = NULL ;
	m_Count -- ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL SceneManager::IsInCurServer( SceneID_t SceneID )
{
__ENTER_FUNCTION

	_SCENE_DATA* pData = GetSceneInfo( SceneID ) ;
	Assert( pData ) ;

	if( g_pServerManager->GetServerID()==pData->m_ServerID )
		return TRUE ;

	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL SceneManager::IsInCurMachine( SceneID_t SceneID )
{
__ENTER_FUNCTION

	_SCENE_DATA* pData = GetSceneInfo( SceneID ) ;
	Assert( pData ) ;

	_SERVER_DATA* pServerData = g_pServerManager->FindServerInfo(pData->m_ServerID) ;
	Assert( pServerData ) ;

	if( g_pMachineManager->GetMachineID() == pServerData->m_MachineID )
		return TRUE ;


	return FALSE ;

__LEAVE_FUNCTION

	return FALSE ;
}

SceneID_t SceneManager::GetSpecialSceneIDFromCurServer( )//取到一个在当前Server上的游戏逻辑场景
{
__ENTER_FUNCTION

	ID_t CurServerID = g_Config.m_ConfigInfo.m_ServerID ;
	for( INT i=0; i<MAX_SCENE; i++ )
	{
		_SCENE_DATA* pData = GetSceneInfo( (SceneID_t)i ) ;
		if( pData==NULL )
			continue ;

		if( CurServerID==pData->m_ServerID )
			return (SceneID_t)i ;
	}

__LEAVE_FUNCTION

	return INVALID_ID ;
}

BOOL SceneManager::BroadCast_Scene(Packet* pMsg) {
  BOOL ret = FALSE;
  for (UINT i = 0, num = 0; num < m_Count && i < MAX_SCENE; i++) {
    if (!g_Config.m_SceneInfo.m_pScene[i].m_IsActive ||
        g_Config.m_SceneInfo.m_pScene[i].m_ServerID !=
            g_Config.m_ConfigInfo.m_ServerID) {
      continue;
    }
    if (m_pScene[i]) {
      ++num;
      ret = m_pScene[i]->BroadCast_Scene(pMsg);
      if (!ret) {
        return FALSE;
      }
    } else {
      continue;
    }
  }
  return TRUE;
}