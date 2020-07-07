#include "stdafx.h"

#include "CSAskCreateDB.h"
#include "SCRetCreateDB.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"'
#include "DB/DatabaseManager.h"

using namespace tomatodb;

UINT CSAskCreateDBHandler::Execute(CSAskCreateDB* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer ;
    Obj_Human* pHuman = pGamePlayer->GetHuman();
	Assert(pGamePlayer);

	Worker* pWorker = pHuman->GetWorker();
	Assert(pWorker);

	if( pGamePlayer->GetPlayerStatus() == PS_SERVER_NORMAL )
	{
		//Current session is logined
		//the code should be executed by WorkerPlayerManager

		//check thread
		Assert( MyGetCurrentThreadID()== pWorker->m_ThreadID ) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;
		CHAR	dbname[MAX_DATABASE_NAME];
		strncpy(dbname, pPacket->GetDatabaseName(), MAX_DATABASE_NAME);
		dbname[MAX_DATABASE_NAME] = '\0';
		BOOL ret = tomatodb::g_pDatabaseManager->CreateDatabase(std::string(dbname));
		SCRetCreateDB msg0;
		msg0.SetDatabaseName(dbname);
		if (ret)
		{
			msg0.SetResult(ASKCREATEDBR_SUCCESS);
		}
		else
		{
			msg0.SetResult(ASKCREATECHAR_INTERNAL_ERROR);
		}
		pGamePlayer->SendPacket(&msg0);

		g_pLog->FastSaveLog(LOG_FILE_1, "SCRetCreateDB D GUID=%X ...OK PID=%d",
			pGamePlayer->m_HumanGUID, pGamePlayer->PlayerID());

		return PACKET_EXE_CONTINUE;
	}
	else
	{
		return PACKET_EXE_ERROR;
	}

	__LEAVE_FUNCTION

	return PACKET_EXE_ERROR;
}
