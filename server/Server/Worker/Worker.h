#ifndef __WORKER_H__
#define __WORKER_H__

#include "Type.h"
#include "WorkerPlayerManager.h"
#include "Performance.h"
#include "Rand.h"

class CFileDataMgr;
class SceneTimer;
class Packet;
class GamePlayer ;
class RecyclePlayerManager;
class User;

enum WORKER_STATUS {
	WORKER_STATUS_SLEEP = 0,	//sleep status
	WORKER_STATUS_SELECT,		//waiting for load
	WORKER_STATUS_LOAD,			//loading
	WORKER_STATUS_INIT,			//init status
	WORKER_STATUS_RUNNING,		//running
};

enum WORKER_TYPE {
	WORKER_TYPE_INVALID = -1,
	WORKER_TYPE_DB_LOGIC,    // DB Logic worker
	WORKER_TYPE_NUMBERS
};

class Worker
{
public :
/////////////////////////////////////////////////////////////////////////////////
//最底层资源及操作处理
/////////////////////////////////////////////////////////////////////////////////
	Worker( WorkerID_t SceneID ) ;
	~Worker( ) ;

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
    //如果 PlayerID为INVALID_ID_EX, 则此消息会被场景执行（Player为nullptr）
    BOOL SendPacket(Packet* pPacket, PlayerID_t PlayerID,
                    UINT Flag = PF_NONE);

	WorkerPlayerManager*		GetWorkerPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	WorkerPlayerManager*		GetPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

	//读取当前场景状态
    INT GetWorkerStatus() { return m_nWorkerStatus; }
    //设置当前场景状态
    VOID SetWorkerStatus(INT status) { m_nWorkerStatus = status; }

    //读取当前场景的场景ID
    WorkerID_t WorkerID() { return m_WorkerID; };

    //关闭当前场景
    BOOL CloseWorker();

    VOID SetWorkerType(INT type) { m_WorkerType = type; };
    INT GetWorkerType() const { return m_WorkerType; };

	BOOL BroadCast_Worker(Packet* pPacket);
	BOOL UserEnterWorker(User* pUser);
	VOID UserLeaveWorker(User* pUser);
protected :
    //当前场景的状态，见SCENE_STATUS
    INT m_nWorkerStatus;

	//当前场景的用户群管理模块指针
	WorkerPlayerManager*		m_pWorkerPlayerManager ;
	//当前场景等待回收的用户指针
	RecyclePlayerManager*	m_pRecyclePlayerManager;

        //当前场景的场景ID
    WorkerID_t				m_WorkerID;


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
    INT m_WorkerType;
    WORKER_PERFOR m_Perfor;  //死锁检测
};

#endif
