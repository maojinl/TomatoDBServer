#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Scene.h"

/////////////////////////////////////////////////////////////////////////////////
// WorkerManager
/////////////////////////////////////////////////////////////////////////////////
class WorkerManager
{
public :
	WorkerManager( ) ;
	~WorkerManager( ) ;

	//初始化接口
	BOOL			Init( UINT MaxSceneCount = MAX_WORKER) ;

	//根据场景号取得场景对象指针
	Scene*			GetScene( WorkerID_t WorkerID ) ;
	//根据场景号取得场景配置信息
	_WORKER_DATA* GetWorkerInfo( WorkerID_t WorkerID) ;
	//根据场景号判断此场景是否在当前服务器端程序处理
	BOOL			IsInCurServer( WorkerID_t WorkerID) ;
	//根据场景号判断此场景是否被当前服务器上的某个服务器端程序处理
	BOOL			IsInCurMachine( WorkerID_t WorkerID) ;

	//向系统内添加一个场景
	BOOL			AddScene( Scene* pScene ) ;
	//将一个场景从系统中删除
	BOOL			DelScene( WorkerID_t WorkerID) ;

	//设置某个场景中的人数
	VOID			SetScenePlayerCount( WorkerID_t WorkerID, INT count ){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return ;
		m_aScenePlayerCount[WorkerID] = count ;
	};
	//读取某个场景中的人数
	INT				GetScenePlayerCount( WorkerID_t WorkerID){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return 0 ;
		return m_aScenePlayerCount[WorkerID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;
	WorkerID_t		GetSpecialSceneIDFromCurServer( ) ;//取到一个在当前Server上的游戏逻辑场景
    BOOL BroadCast_Scene(Packet* pMsg);

private :
	Scene*			m_pWorker[MAX_WORKER] ;			//场景数据指针
	INT				m_aScenePlayerCount[MAX_WORKER] ;//场景中人数
	UINT			m_Count ;//当前系统中的场景数量

	INT				m_nTotalPlayerCount ;//整个游戏世界的人数总和
};

extern WorkerManager* g_pWorkerManager ;


#endif
