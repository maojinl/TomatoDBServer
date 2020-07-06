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
	//����ֵҲ����Ϊinvalid_id,���ʱ��RecyclePlayerManager���� IncommingPlayerManager ��
	WorkerID_t		 GetWorkerID();

private:
	WorkerID_t		 m_WorkerID;
};


#endif