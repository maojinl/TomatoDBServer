#ifndef _RECYCLE_PLAYER_MANAGER_H_
#define _RECYCLE_PLAYER_MANAGER_H_
#include "PlayerManager.h"

class RecyclePlayerManager:public PlayerManager
{
	
public:
	RecyclePlayerManager();
	~RecyclePlayerManager();
	
public:
	virtual	BOOL	 HeartBeat(UINT uTime=0 );

	VOID			 SetWorkerID(WorkerID_t SceneID);
	//场景值也可能为invalid_id,这个时候RecyclePlayerManager是在 IncommingPlayerManager 中
	WorkerID_t		 GetWorkerID();

private:
	WorkerID_t		 m_WorkerID;
};


#endif