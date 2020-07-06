#include "stdafx.h"
#include "RecyclePlayerManager.h"
#include "GamePlayer.h"
#include "PlayerPool.h"
#include "Log.h"
#include "Obj_Human.h"


RecyclePlayerManager::RecyclePlayerManager()
{
	__ENTER_FUNCTION
	
		m_WorkerID = INVALID_ID;

	__LEAVE_FUNCTION
}

RecyclePlayerManager::~RecyclePlayerManager()
{
	__ENTER_FUNCTION
		
		AssertEx(GetPlayerNumber() == 0,"场景中还有玩家存在,强制回收玩家管理器!");

	__LEAVE_FUNCTION
}


BOOL	RecyclePlayerManager::HeartBeat(UINT uTime)
{
	__ENTER_FUNCTION
		
	
		for(UINT i =0;i<GetPlayerNumber();i++)
		{
			_MY_TRY
			{
				GamePlayer* pPlayer = g_pPlayerPool->GetPlayer(m_pPlayers[i]) ;
				Assert( pPlayer ) ;
				
				if(!pPlayer)
					continue;
			}
			_MY_CATCH
			{
				SaveCodeLog( ) ;
			}
		}
	
		return TRUE;

	__LEAVE_FUNCTION

	return FALSE;
}

VOID	RecyclePlayerManager::SetWorkerID(WorkerID_t workerID)
{
	m_WorkerID  = workerID;
}

WorkerID_t	RecyclePlayerManager::GetWorkerID()
{
	return m_WorkerID;
}