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
	{//当前玩家是刚接入的
		//当前代码由 IncomingPlayerManager来执行

		//检查线程执行资源是否正确
		Assert( MyGetCurrentThreadID()==g_pIncomingPlayerManager->m_ThreadID ) ;

		WorkerID_t SceneID = 1;
                //pHuman->GetDB()->GetDBStartScene();
		Scene* pScene = g_pWorkerManager->GetScene( SceneID ) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		//非法的场景ID
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

		//当前玩家没有权限进入此场景（等级不够，场景没开放，等）
		INT nRet = pScene->CheckEnter( PlayerID ) ;
		if( nRet==0 )
		{
			GCEnterScene Msg ;
			Msg.setReturn( 1 ) ;
			Msg.setSceneID( SceneID ) ;
			pGamePlayer->SendPacket( &Msg ) ;

			return PACKET_EXE_CONTINUE ;
		}

		//如果需要加入的场景已经处于饱和状态，则返回加入场景失败消息
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

		//删除接入模块中数据
		PlayerID_t pid = pGamePlayer->PlayerID() ;
		BOOL ret = g_pIncomingPlayerManager->DelPlayer( pid ) ;
		if( !ret )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		//向目的场景发送转移消息
		CGEnterScene* pEnter = (CGEnterScene*)(g_pPacketFactoryManager->CreatePacket(PACKET_CG_ENTERSCENE)) ;
		pEnter->setEnterType( pPacket->getEnterType() ) ;
		pEnter->setSceneID( SceneID ) ;

		//将玩家状态设置为PS_SERVER_READY_TO_ENTER
		pGamePlayer->SetPlayerStatus( PS_SERVER_READY_TO_ENTER ) ;

		pScene->SendPacket( pEnter, PlayerID ) ;

		//**注意**
		//必须返回PACKET_EXE_BREAK ；
		return PACKET_EXE_BREAK ;
	}
	else if( pGamePlayer->GetPlayerStatus()==PS_SERVER_READY_TO_ENTER )
	{//场景收到消息，处理添加
		//当前代码由 pScene线程来执行
		//收到原场景发送过来的消息，由目的场景执行
		//功能:
		//1.添加此玩家到本场景中
		//2.玩家发送一个消息

		WorkerID_t SceneID = pPacket->getSceneID() ;
		Scene* pScene = g_pWorkerManager->GetScene( SceneID ) ;
		if( pScene==NULL )
		{
			Assert(FALSE) ;
			return PACKET_EXE_ERROR ;
		}

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;

		//检查线程执行资源是否正确
		Assert( MyGetCurrentThreadID()==pScene->m_ThreadID ) ;

		//将客户端连接加入目的场景玩家管理器
		BOOL ret = pScene->GetScenePlayerManager()->AddPlayer( pPlayer ) ;
		if( !ret )
		{//如果加入场景失败，由于当前玩家已经从原先的场景里脱离，
			//所以只能断开此玩家的网络连接
			SOCKET fd = pGamePlayer->GetSocket()->getSOCKET() ;
			BOOL boo = pScene->GetScenePlayerManager()->DelPlayerSocket( fd ) ;
			boo = pGamePlayer->FreeOwn() ;

			g_pLog->FastSaveLog( LOG_FILE_1, "ERROR D: CGEnterScene::AddPlayer GUID=%X SceneID=%d Socket=%d PID:%d",
                            pGamePlayer->PlayerID(), SceneID, fd,
                            pGamePlayer->PlayerID());

			return PACKET_EXE_ERROR ;
		}

		// 下一版要改
		//向客户端发送进入场景成功的消息
		GCEnterScene Msg0 ;
		
		Msg0.setReturn( 2 ) ;
		Msg0.SetPacketRetFlag( 2 );
		Msg0.setSceneID( SceneID ) ;

		Msg0.setCharName(pGamePlayer->GetHuman()->GetName());
		Msg0.setSceneID(SceneID);
		Msg0.setTitleName(pHuman->GetTitle());
		Msg0.setLevel(pHuman->GetLevel());
		pGamePlayer->SendPacket( &Msg0 ) ;

		//成功进入场景，将玩家状态设置为：PS_SERVER_NORMAL
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
