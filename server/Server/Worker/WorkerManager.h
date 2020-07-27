#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Worker.h"

/////////////////////////////////////////////////////////////////////////////////
// WorkerManager
/////////////////////////////////////////////////////////////////////////////////
class WorkerManager
{
public :
	WorkerManager( ) ;
	~WorkerManager( ) ;

	BOOL			Init( UINT MaxSceneCount = MAX_WORKER);
	WorkerID_t		GetNextWorkerID();
	Worker*			GetWorker( WorkerID_t WorkerID ) ;
	_WORKER_DATA* GetWorkerInfo( WorkerID_t WorkerID) ;
	BOOL			IsInCurServer( WorkerID_t WorkerID) ;
	BOOL			IsInCurMachine( WorkerID_t WorkerID) ;

	BOOL			AddWorker(Worker* pScene ) ;
	BOOL			DelWorker( WorkerID_t WorkerID) ;

	VOID			SetScenePlayerCount( WorkerID_t WorkerID, INT count ){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return ;
		m_aWorkerPlayerCount[WorkerID] = count ;
	};

	INT				GetScenePlayerCount( WorkerID_t WorkerID){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return 0 ;
		return m_aWorkerPlayerCount[WorkerID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;

    BOOL BroadCast_Worker(Packet* pMsg);

private :
	Worker*			m_pWorker[MAX_WORKER];
	INT				m_aWorkerPlayerCount[MAX_WORKER];
	UINT			m_Count;
	INT				m_nTotalPlayerCount;
	INT				m_NextWorkerID;
};

extern WorkerManager* g_pWorkerManager;


#endif
