/////////////////////////////////////////////////////////////////////////////////
//文件名：Scene.h
//功能描述：游戏场景，单个场景游戏逻辑功能的执行着
//			拥有所有在游戏场景中的游戏逻辑数据，有独立的执行线程来驱动场景的执行
//			管理所有连接在场景中的客户端网络连接，能够独立处理客户端网络消息
//修改记录：2005-3-23创建
//修改记录：2005-11-8整理场景文件结构，之后，所有对场景做修改都需要留下记录
//修改记录：2005-11-14增加场景的事件响应
//修改记录：2005-11-15增加场景的副本系统相关数据和接口
//修改记录：2006-2-7加入摊位管理器
/////////////////////////////////////////////////////////////////////////////////

#ifndef __SCENE_H__
#define __SCENE_H__

#include "Type.h"
#include "ScenePlayerManager.h"
#include "Performance.h"
#include "Rand.h"

class CFileDataMgr;
class SceneTimer;
class Packet;
class GamePlayer ;
class RecyclePlayerManager;

enum SCENE_STATUS {
  SCENE_STATUS_SLEEP = 0,  //没有设置的场景状态，即没有场景数据、处于休眠的状态
  SCENE_STATUS_SELECT,   //场景被检索，处于待装载状态
  SCENE_STATUS_LOAD,     //需要读取场景资源文件的状态
  SCENE_STATUS_INIT,     //需要初始场景数据的状态
  SCENE_STATUS_RUNNING,  //正常运行的场景状态
};

enum SCENE_TYPE {
  SCENE_TYPE_INVALID = -1,
  SCENE_TYPE_GAMELOGIC,    // 普通游戏逻辑场景
  SCENE_TYPE_COPY,         // 副本
  SCENE_TYPE_BATTLEFIELD,  // 战场
  SCENE_TYPE_ARENA,        // 擂台
  SCENE_TYPE_CIT,          // 普通城市港口
  SCENE_TYPE_PIRATE_CIT,   // 海盗港口
  SCENE_TYPE_HOUSE,        // 房子里

  SCENE_TYPE_NUMBERS
};

class Scene
{
public :
/////////////////////////////////////////////////////////////////////////////////
//最底层资源及操作处理
/////////////////////////////////////////////////////////////////////////////////
	Scene( SceneID_t SceneID ) ;
	~Scene( ) ;

	//初始化
	BOOL					Init( ) ;
	//场景的执行接口，此接口会被场景线程定时调用
	BOOL					Tick( ) ;
	//控制当前场景状态的逻辑接口
	BOOL					StatusLogic( ) ;

/////////////////////////////////////////////////////////////////////////////////
//游戏逻辑底层处理
/////////////////////////////////////////////////////////////////////////////////
protected :
	//场景的逻辑接口
	BOOL					HeartBeat( ) ;

	//处理场景的缓存消息
	BOOL					ProcessCacheCommands( ) ;

	//读取当前场景缓存消息
	BOOL					RecvPacket( Packet*& pPacket, PlayerID_t& PlayerID, UINT& Flag ) ;

	//重新调整缓存大小
	BOOL					ResizeCache( ) ;

	BOOL					MovePacket( PlayerID_t PlayerID ) ;
public :
    //向此场景发送消息
    //此接口支持数据同步，即可以在不同线程内调用
    //此接口是不同场景间通讯的唯一接口
    //注意：pPacket消息需要用g_pPacketFactoryManager创建出来，用完后不能删除
    //如果 PlayerID为INVALID_ID, 则广播此消息到整个场景
    //如果 PlayerID为INVALID_ID_EX, 则此消息会被场景执行（Player为NULL）
    BOOL SendPacket(Packet* pPacket, PlayerID_t PlayerID,
                    UINT Flag = PF_NONE);

	ScenePlayerManager*		GetScenePlayerManager(){ return m_pScenePlayerManager ; } ;
	ScenePlayerManager*		GetPlayerManager(){ return m_pScenePlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

	//读取当前场景状态
    INT GetSceneStatus() { return m_nSceneStatus; }
    //设置当前场景状态
    VOID SetSceneStatus(INT status) { m_nSceneStatus = status; }

    //读取当前场景的场景ID
    SceneID_t SceneID() { return m_SceneID; };

    //关闭当前场景
    BOOL CloseScene();

		//判断当前场景是否为副本场景 普通游戏场景 城市场景, enum SCENE_TYPE
    VOID SetSceneType(INT type) { m_SceneType = type; };
    INT GetSceneType() const { return m_SceneType; };

	BOOL BroadCast_Scene(Packet* pPacket);

protected :
    //当前场景的状态，见SCENE_STATUS
    INT m_nSceneStatus;

	//当前场景的用户群管理模块指针
	ScenePlayerManager*		m_pScenePlayerManager ;
	//当前场景等待回收的用户指针
	RecyclePlayerManager*	m_pRecyclePlayerManager;

        //当前场景的场景ID
    SceneID_t				m_SceneID;


private :
	//当前场景的消息缓存
	ASYNC_PACKET*			m_PacketQue ;
	UINT					m_QueSize ;
	UINT					m_Head ;
	UINT					m_Tail ;
	_100_PER_RANDOM_TABLE	m_Rand100 ; //每个线程唯一的随机数生成器
public:
	// 本场景的共用变量
	Packet					*m_pPacket_SysMsg; //系统广播;
	TID						m_ThreadID ;//场景的线程号
    INT m_SceneType;
    SCENE_PERFOR m_Perfor;  //死锁检测
};

#endif
