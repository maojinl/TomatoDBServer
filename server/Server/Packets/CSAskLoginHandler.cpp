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

		//��ǰ���û��Ȩ�޽���˳������ȼ�����������û���ţ��ȣ�
		INT nRet = pWorker->CheckEnter( PlayerID ) ;
		if( nRet==0 )
		{
			SCRetLogin Msg;
			Msg.SetResult(LOGINR_STOP_SERVICE);
			pGamePlayer->SendPacket(&Msg);
			return PACKET_EXE_CONTINUE;
		}


		//ɾ������ģ��������
		PlayerID_t pid = pGamePlayer->PlayerID() ;
		BOOL ret = g_pIncomingPlayerManager->DelPlayer( pid ) ;
		if( !ret )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		//��Ŀ�ĳ�������ת����Ϣ
		CSAskLogin* pAskLogin = (CSAskLogin*)(g_pPacketFactoryManager->CreatePacket(PACKET_CS_ASKLOGIN));
		pAskLogin->SetWorkerID(WorkerID);
		//�����״̬����ΪPS_SERVER_READY_TO_ENTER
		pGamePlayer->SetPlayerStatus(PS_SERVER_READY_TO_ENTER);

		pWorker->SendPacket(pAskLogin, PlayerID);

		//**ע��**
		//���뷵��PACKET_EXE_BREAK ��
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

		//����߳�ִ����Դ�Ƿ���ȷ
		Assert(MyGetCurrentThreadID()== pWorker->m_ThreadID);

		//���ͻ������Ӽ���Ŀ�ĳ�����ҹ�����
		BOOL ret = pWorker->GetWorkerPlayerManager()->AddPlayer(pPlayer);
		if( !ret )
		{//������볡��ʧ�ܣ����ڵ�ǰ����Ѿ���ԭ�ȵĳ��������룬
			//����ֻ�ܶϿ�����ҵ���������
			SOCKET fd = pGamePlayer->GetSocket()->getSOCKET() ;
			BOOL boo = pWorker->GetWorkerPlayerManager()->DelPlayerSocket(fd);
			boo = pGamePlayer->FreeOwn();

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR D: CSAskLogin::AddPlayer GUID=%X SceneID=%d Socket=%d PID:%d",
                            pGamePlayer->PlayerID(), workerID, fd,
                            pGamePlayer->PlayerID());
			return PACKET_EXE_ERROR ;
		}

		// ��һ��Ҫ��
		//��ͻ��˷��ͽ��볡���ɹ�����Ϣ
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
