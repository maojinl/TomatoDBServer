#include "stdafx.h"

#include "GWAskMail.h"
#include "Log.h"
#include "ServerPlayer.h"
#include "ServerManager.h"
#include "WGMail.h"


UINT GWAskMailHandler::Execute( GWAskMail* pPacket, Player* pPlayer )
{
  __ENTER_FUNCTION

  // USER* pUser = g_pOnlineUser->FindUser( pPacket->GetGUID() ) ;
  // if( pUser==NULL )
  //{
  //	Assert(FALSE) ;
  //	return PACKET_EXE_CONTINUE ;
  //}

  ID_t ServerID = 111;
  //pUser->GetServerID();
  ServerPlayer* pServerPlayer = dynamic_cast<ServerPlayer*>(pPlayer);
  //g_pServerManager->GetServerPlayer(ServerID);
	if( pServerPlayer==NULL )
	{
		Assert(FALSE) ;
		return PACKET_EXE_CONTINUE ;
	}

	WGMail Msg ;
	Msg.SetPlayerID( 111 ) ;
	Msg.SetGUID( pPacket->GetGUID() );
	UINT nPageIndex = pPacket->GetPageIndex();
	Msg.SetPageIndex( pPacket->GetPageIndex() );

	pServerPlayer->SendPacket( &Msg ) ;

	Log::SaveLog( WORLD_LOGFILE, "GWAskMailHandler...Name=%s MailCount=%d LeftCount=%d",
	 "aaa", 1, 0 );

	return PACKET_EXE_CONTINUE ;

__LEAVE_FUNCTION

	return PACKET_EXE_ERROR ;
}
