#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Scene.h"

/////////////////////////////////////////////////////////////////////////////////
// SceneManager
/////////////////////////////////////////////////////////////////////////////////
class SceneManager
{
public :
	SceneManager( ) ;
	~SceneManager( ) ;

	//初始化接口
	BOOL			Init( UINT MaxSceneCount = MAX_SCENE ) ;

	//根据场景号取得场景对象指针
	Scene*			GetScene( SceneID_t SceneID ) ;
	//根据场景号取得场景配置信息
	_SCENE_DATA*	GetSceneInfo( SceneID_t SceneID ) ;
	//根据场景号判断此场景是否在当前服务器端程序处理
	BOOL			IsInCurServer( SceneID_t SceneID ) ;
	//根据场景号判断此场景是否被当前服务器上的某个服务器端程序处理
	BOOL			IsInCurMachine( SceneID_t SceneID ) ;

	//向系统内添加一个场景
	BOOL			AddScene( Scene* pScene ) ;
	//将一个场景从系统中删除
	BOOL			DelScene( SceneID_t SceneID ) ;

	//设置某个场景中的人数
	VOID			SetScenePlayerCount( SceneID_t SceneID, INT count ){
		if( SceneID < 0 && SceneID>=MAX_SCENE ) return ;
		m_aScenePlayerCount[SceneID] = count ;
	};
	//读取某个场景中的人数
	INT				GetScenePlayerCount( SceneID_t SceneID ){
		if( SceneID < 0 && SceneID>=MAX_SCENE ) return 0 ;
		return m_aScenePlayerCount[SceneID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;
	SceneID_t		GetSpecialSceneIDFromCurServer( ) ;//取到一个在当前Server上的游戏逻辑场景
    BOOL BroadCast_Scene(Packet* pMsg);

private :
	Scene*			m_pScene[MAX_SCENE] ;			//场景数据指针
	INT				m_aScenePlayerCount[MAX_SCENE] ;//场景中人数
	UINT			m_Count ;//当前系统中的场景数量

	INT				m_nTotalPlayerCount ;//整个游戏世界的人数总和
};

extern SceneManager* g_pSceneManager ;


#endif
