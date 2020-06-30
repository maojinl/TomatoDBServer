#include "stdafx.h"

#include "CGEnterScene.h"
#include "GCEnterScene.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"


UINT CGEnterSceneHandler::Execute( CGEnterScene* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer ;
    Obj_Human* pHuman = pGamePlayer->GetHuman();
	Assert( pGamePlayer ) ;


	if( pGamePlayer->GetPlayerStatus()==PS_SERVER_WAITING_FOR_ENTER )
	{//��ǰ����Ǹս����
		//��ǰ������ IncomingPlayerManager��ִ��

		//����߳�ִ����Դ�Ƿ���ȷ
		Assert( MyGetCurrentThreadID()==g_pIncomingPlayerManager->m_ThreadID ) ;

		WorkerID_t SceneID = 1;
                //pHuman->GetDB()->GetDBStartScene();
		Scene* pScene = g_pWorkerManager->GetScene( SceneID ) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		//�Ƿ��ĳ���ID
		if( SceneID==INVALID_ID || pScene==NULL )
		{
			pScene = g_pWorkerManager->GetScene( SceneID ) ;
			if( pScene==NULL )
			{
				SceneID = g_pWorkerManager->GetSpecialSceneIDFromCurServer( ) ;
				pScene = g_pWorkerManager->GetScene( SceneID ) ;
				if( pScene==NULL )
				{
					GCEnterScene Msg ;
					Msg.setReturn( 2 ) ;
					Msg.setSceneID( SceneID ) ; 

					pGamePlayer->SendPacket( &Msg ) ;

					return PACKET_EXE_CONTINUE ;
				}
			}
		}

		//��ǰ���û��Ȩ�޽���˳������ȼ�����������û���ţ��ȣ�
		INT nRet = pScene->CheckEnter( PlayerID ) ;
		if( nRet==0 )
		{
			GCEnterScene Msg ;
			Msg.setReturn( 1 ) ;
			Msg.setSceneID( SceneID ) ;
			pGamePlayer->SendPacket( &Msg ) ;

			return PACKET_EXE_CONTINUE ;
		}

		//�����Ҫ����ĳ����Ѿ����ڱ���״̬���򷵻ؼ��볡��ʧ����Ϣ
		if( !pScene->IsCanEnter() )
		{
			GCEnterScene Msg ;
			Msg.setReturn( 3 ) ;
			Msg.setSceneID( SceneID ) ;
			pGamePlayer->SendPacket( &Msg ) ;

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR I: CGEnterScene::pScene->IsCanEnter GUID=%x SceneID=%d PID=%d",
				pGamePlayer->PlayerID(), SceneID, pGamePlayer->PlayerID() ) ;

			return PACKET_EXE_CONTINUE ;
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
		CGEnterScene* pEnter = (CGEnterScene*)(g_pPacketFactoryManager->CreatePacket(PACKET_CG_ENTERSCENE)) ;
		pEnter->setEnterType( pPacket->getEnterType() ) ;
		pEnter->setSceneID( SceneID ) ;

		//�����״̬����ΪPS_SERVER_READY_TO_ENTER
		pGamePlayer->SetPlayerStatus( PS_SERVER_READY_TO_ENTER ) ;

		pScene->SendPacket( pEnter, PlayerID ) ;

		//**ע��**
		//���뷵��PACKET_EXE_BREAK ��
		return PACKET_EXE_BREAK ;
	}
	else if( pGamePlayer->GetPlayerStatus()==PS_SERVER_READY_TO_ENTER )
	{//�����յ���Ϣ���������
		//��ǰ������ pScene�߳���ִ��
		//�յ�ԭ�������͹�������Ϣ����Ŀ�ĳ���ִ��
		//����:
		//1.��Ӵ���ҵ���������
		//2.��ҷ���һ����Ϣ

		WorkerID_t SceneID = pPacket->getSceneID() ;
		Scene* pScene = g_pWorkerManager->GetScene( SceneID ) ;
		if( pScene==NULL )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		//����߳�ִ����Դ�Ƿ���ȷ
		Assert( MyGetCurrentThreadID()==pScene->m_ThreadID ) ;

		//���ͻ������Ӽ���Ŀ�ĳ�����ҹ�����
		BOOL ret = pScene->GetScenePlayerManager()->AddPlayer( pPlayer ) ;
		if( !ret )
		{//������볡��ʧ�ܣ����ڵ�ǰ����Ѿ���ԭ�ȵĳ��������룬
			//����ֻ�ܶϿ�����ҵ���������
			SOCKET fd = pGamePlayer->GetSocket()->getSOCKET() ;
			BOOL boo = pScene->GetScenePlayerManager()->DelPlayerSocket( fd ) ;
			boo = pGamePlayer->FreeOwn() ;

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR D: CGEnterScene::AddPlayer GUID=%X SceneID=%d Socket=%d PID:%d",
                            pGamePlayer->PlayerID(), SceneID, fd,
                            pGamePlayer->PlayerID());

			return PACKET_EXE_ERROR ;
		}

		// ��һ��Ҫ��
		//��ͻ��˷��ͽ��볡���ɹ�����Ϣ
		GCEnterScene Msg0 ;
		
		Msg0.setReturn( 2 ) ;
		Msg0.SetPacketRetFlag( 2 );
		Msg0.setSceneID( SceneID ) ;

		Msg0.setCharName(pGamePlayer->GetHuman()->GetName());
		Msg0.setSceneID(SceneID);
		Msg0.setTitleName(pHuman->GetTitle());
		Msg0.setLevel(pHuman->GetLevel());
		pGamePlayer->SendPacket( &Msg0 ) ;

		//�ɹ����볡���������״̬����Ϊ��PS_SERVER_NORMAL
		pGamePlayer->SetPlayerStatus( PS_SERVER_NORMAL ) ;

		g_pLog->FastSaveLog( LOG_FILE_1, "CGEnterScene D GUID=%X To:%d ...OK PID=%d",
			pGamePlayer->m_HumanGUID, SceneID,  pGamePlayer->PlayerID() ) ;
	}
	else
	{
		WorkerID_t SceneID = pPacket->getSceneID() ;
		Scene* pScene = g_pWorkerManager->GetScene( SceneID ) ;
		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;
		WorkerID_t DestSceneID = pPacket->getSceneID() ;
		g_pLog->FastSaveLog( LOG_FILE_1, "CGEnterScene S PID:%d GUID=%X From:%d To:%d ...StatusError:%d ",
			pGamePlayer->PlayerID(), pGamePlayer->m_HumanGUID, pScene->SceneID(), DestSceneID, pGamePlayer->GetPlayerStatus() ) ;
		Assert(FALSE) ;
	}


	return PACKET_EXE_CONTINUE ;

	__LEAVE_FUNCTION

		return PACKET_EXE_ERROR ;
}
