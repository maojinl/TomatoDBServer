#include "stdafx.h"

#include "CSAskLogin.h"
#include "SCRetLogin.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"


UINT CSAskLoginHandler::Execute(CSAskLogin* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer ;
    Obj_Human* pHuman = pGamePlayer->GetHuman();
	Assert( pGamePlayer ) ;

	if( pGamePlayer->GetPlayerStatus() == PS_SERVER_WAITING_FOR_ENTER )
	{
		//Current session is just connected
		//the code should be executed by IncomingPlayerManager

		//check thread
		Assert( MyGetCurrentThreadID()==g_pIncomingPlayerManager->m_ThreadID ) ;

		WorkerID_t WorkerID = 1;
		Worker* pWorker = g_pWorkerManager->GetWorker(WorkerID) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		CHAR	Account[MAX_ACCOUNT + 1];
		strncpy(Account, pPacket->GetAccount(), MAX_ACCOUNT + 1);
		Account[MAX_ACCOUNT] = '\0';

		CHAR    PassKey[MAX_ACCOUNT + 1];
		INT     iAccountLen = strlen(Account);
		memset(PassKey, 0, sizeof(CHAR) * (MAX_ACCOUNT + 1));
		strncpy(PassKey, pPacket->GetPassKey(), MAX_ACCOUNT + 1);
		ENCRYPT(PassKey, iAccountLen, USER_ACCOUNT_KEY, 0);

		/* compare password and account
		if (strcmp(Account, PassKey) != 0)
		{
			return PACKET_EXE_ERROR;
		}
		*/

		//Illegal worker
		if( WorkerID==INVALID_ID || pWorker==NULL )
		{
			pWorker = g_pWorkerManager->GetWorker(0) ;
			if(pWorker ==NULL )
			{
				SCRetLogin Msg ;
				Msg.SetResult(LOGINR_STOP_SERVICE);
				pGamePlayer->SendPacket(&Msg);
				return PACKET_EXE_CONTINUE;
			}
		}

		//当前玩家没有权限进入此场景（等级不够，场景没开放，等）
		INT nRet = pWorker->CheckEnter( PlayerID ) ;
		if( nRet==0 )
		{
			SCRetLogin Msg;
			Msg.SetResult(LOGINR_STOP_SERVICE);
			pGamePlayer->SendPacket(&Msg);
			return PACKET_EXE_CONTINUE;
		}


		//删除接入模块中数据
		PlayerID_t pid = pGamePlayer->PlayerID() ;
		BOOL ret = g_pIncomingPlayerManager->DelPlayer( pid ) ;
		if( !ret )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		//向目的场景发送转移消息
		CSAskLogin* pAskLogin = (CSAskLogin*)(g_pPacketFactoryManager->CreatePacket(PACKET_CS_ASKLOGIN));
		pAskLogin->SetWorkerID(WorkerID);
		//将玩家状态设置为PS_SERVER_READY_TO_ENTER
		pGamePlayer->SetPlayerStatus(PS_SERVER_READY_TO_ENTER);

		pWorker->SendPacket(pAskLogin, PlayerID);

		//**注意**
		//必须返回PACKET_EXE_BREAK ；
		return PACKET_EXE_BREAK ;
	}
	else if( pGamePlayer->GetPlayerStatus()==PS_SERVER_READY_TO_ENTER )
	{
		WorkerID_t workerID = pPacket->GetWorkerID() ;
		Worker* pWorker = g_pWorkerManager->GetWorker(workerID) ;
		if(pWorker ==NULL )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		//检查线程执行资源是否正确
		Assert(MyGetCurrentThreadID()== pWorker->m_ThreadID);

		//将客户端连接加入目的场景玩家管理器
		BOOL ret = pWorker->GetWorkerPlayerManager()->AddPlayer(pPlayer);
		if( !ret )
		{//如果加入场景失败，由于当前玩家已经从原先的场景里脱离，
			//所以只能断开此玩家的网络连接
			SOCKET fd = pGamePlayer->GetSocket()->getSOCKET() ;
			BOOL boo = pWorker->GetWorkerPlayerManager()->DelPlayerSocket(fd);
			boo = pGamePlayer->FreeOwn();

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR D: CSAskLogin::AddPlayer GUID=%X SceneID=%d Socket=%d PID:%d",
                            pGamePlayer->PlayerID(), workerID, fd,
                            pGamePlayer->PlayerID());
			return PACKET_EXE_ERROR ;
		}

		// 下一版要改
		//向客户端发送进入场景成功的消息
		SCRetLogin Msg0 ;
		
		Msg0.SetResult(LOGIN_RESULT::LOGINR_SUCCESS);
		Msg0.SetCharName(pGamePlayer->GetHuman()->GetName());
		Msg0.SetTitleName(pHuman->GetTitle());
		Msg0.SetLevel(pHuman->GetLevel());
		pGamePlayer->SendPacket( &Msg0 );

		//set user session to PS_SERVER_NORMAL
		pGamePlayer->SetPlayerStatus( PS_SERVER_NORMAL ) ;

		g_pLog->FastSaveLog( LOG_FILE_1, "CGEnterScene D GUID=%X To:%d ...OK PID=%d",
			pGamePlayer->m_HumanGUID, workerID,  pGamePlayer->PlayerID() ) ;
	}

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
