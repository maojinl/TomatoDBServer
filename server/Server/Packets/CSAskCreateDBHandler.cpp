#include "stdafx.h"

#include "CSAskCreateDB.h"
#include "SCRetCreateDB.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"'

UINT CSAskCreateDBHandler::Execute(CSAskCreateDB* pPacket, Player* pPlayer )
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

		//should check full or not
		INT nRet = pWorker->CheckEnter( PlayerID ) ;
		if( nRet==0 )
		{
			SCRetLogin Msg;
			Msg.SetResult(LOGINR_STOP_SERVICE);
			pGamePlayer->SendPacket(&Msg);
			return PACKET_EXE_CONTINUE;
		}

		//delete the session from the connecting module
		PlayerID_t pid = pGamePlayer->PlayerID() ;
		BOOL ret = g_pIncomingPlayerManager->DelPlayer( pid ) ;
		if( !ret )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		//send login to the worker thread
		CSAskLogin* pAskLogin = (CSAskLogin*)(g_pPacketFactoryManager->CreatePacket(PACKET_CS_ASKLOGIN));
		pAskLogin->SetWorkerID(WorkerID);
		//ÎªPS_SERVER_READY_TO_ENTER
		pGamePlayer->SetPlayerStatus(PS_SERVER_READY_TO_ENTER);

		pWorker->SendPacket(pAskLogin, PlayerID);

		//
		//must return PACKET_EXE_BREAK £»
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

		//check thread
		Assert(MyGetCurrentThreadID()== pWorker->m_ThreadID);

		//add the session into the workers manager
		BOOL ret = pWorker->GetWorkerPlayerManager()->AddPlayer(pPlayer);
		if( !ret )
		{
			SOCKET fd = pGamePlayer->GetSocket()->getSOCKET() ;
			BOOL boo = pWorker->GetWorkerPlayerManager()->DelPlayerSocket(fd);
			boo = pGamePlayer->FreeOwn();

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR D: CSAskLogin::AddPlayer GUID=%X SceneID=%d Socket=%d PID:%d",
                            pGamePlayer->PlayerID(), workerID, fd,
                            pGamePlayer->PlayerID());
			return PACKET_EXE_ERROR ;
		}

		//reply the client with login success
		SCRetLogin Msg0 ;
		
		Msg0.SetResult(LOGIN_RESULT::LOGINR_SUCCESS);
		Msg0.SetCharName(pGamePlayer->GetHuman()->GetName());
		Msg0.SetTitleName(pHuman->GetTitle());
		Msg0.SetLevel(pHuman->GetLevel());
		pGamePlayer->SendPacket( &Msg0 );

		//set user session to PS_SERVER_NORMAL
		pGamePlayer->SetPlayerStatus( PS_SERVER_NORMAL ) ;

		g_pLog->FastSaveLog( LOG_FILE_1, "SCRetLogin D GUID=%X To:%d ...OK PID=%d",
			pGamePlayer->m_HumanGUID, workerID,  pGamePlayer->PlayerID() ) ;
	}

	return PACKET_EXE_CONTINUE;

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
