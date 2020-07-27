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
	Worker(WorkerID_t SceneID);
	~Worker();

	BOOL					Init( ) ;
	BOOL					Tick( ) ;
	BOOL					StatusLogic( ) ;

protected :

	BOOL					HeartBeat( ) ;

	BOOL					ProcessCacheCommands( ) ;

	BOOL					RecvPacket( Packet*& pPacket, PlayerID_t& PlayerID, UINT& Flag ) ;

	BOOL					ResizeCache( ) ;

	BOOL					MovePacket( PlayerID_t PlayerID ) ;
public :
    BOOL SendPacket(Packet* pPacket, PlayerID_t PlayerID,
                    UINT Flag = PF_NONE);

	WorkerPlayerManager*		GetWorkerPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	WorkerPlayerManager*		GetPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

    INT GetWorkerStatus() { return m_nWorkerStatus; }
    VOID SetWorkerStatus(INT status) { m_nWorkerStatus = status; }

    WorkerID_t WorkerID() { return m_WorkerID; };

    BOOL CloseWorker();

    VOID SetWorkerType(INT type) { m_WorkerType = type; };
    INT GetWorkerType() const { return m_WorkerType; };

	BOOL BroadCast_Worker(Packet* pPacket);
	BOOL UserEnterWorker(User* pUser);
	VOID UserLeaveWorker(User* pUser);
protected :
    INT m_nWorkerStatus;

	WorkerPlayerManager*		m_pWorkerPlayerManager ;

	RecyclePlayerManager*	m_pRecyclePlayerManager;

    WorkerID_t				m_WorkerID;


private :
	ASYNC_PACKET*			m_PacketQue;
	UINT					m_QueSize;
	UINT					m_Head;
	UINT					m_Tail;
	_100_PER_RANDOM_TABLE	m_Rand100; 
public:
	Packet					*m_pPacket_SysMsg;
	TID						m_ThreadID;
    INT m_WorkerType;
    WORKER_PERFOR m_Perfor;
};

#endif
