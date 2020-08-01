#include "stdafx.h"

#include "CSAskDBDefinition.h"
#include "SCRetDBDefinition.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"'
#include "DB/DatabaseManager.h"

using namespace tomatodb;

UINT CSAskDBDefinitionHandler::Execute(CSAskDBDefinition* pPacket, Player* pPlayer )
{
	__ENTER_FUNCTION

	GamePlayer* pGamePlayer = (GamePlayer*)pPlayer;
    Obj_Human* pHuman = pGamePlayer->GetHuman();
	Assert(pGamePlayer);

	Worker* pWorker = pHuman->GetWorker();
	Assert(pWorker);

	if( pGamePlayer->GetPlayerStatus() == PS_SERVER_NORMAL )
	{
		//Current session is logined
		//the code should be executed by WorkerPlayerManager

		//check thread
		Assert( MyGetCurrentThreadID() == pWorker->m_ThreadID ) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;
		CHAR	dbname[MAX_DATABASE_NAME + 1];
		strncpy(dbname, pPacket->GetDatabaseName(), MAX_DATABASE_NAME);
		dbname[MAX_DATABASE_NAME] = '\0';
		DB_OPERATION_TYPE opType = pPacket->GetOperationType();

		BOOL ret;
		switch (opType)
		{
		case DB_OPERATION_TYPE::DB_OPERATION_TYPE_CREATE:
			ret = tomatodb::g_pDatabaseManager->CreateDatabase(std::string(dbname));
			break;
		case DB_OPERATION_TYPE::DB_OPERATION_TYPE_DELETE:
			ret = tomatodb::g_pDatabaseManager->DeleteDatabase(std::string(dbname));
			break;
		default:
			ret = FALSE;
			break;
		}

		SCRetDBDefinition msg0;
		msg0.SetDatabaseName(dbname);
		if (ret)
		{
			msg0.SetResult(ASK_DB_OPERATION_R_SUCCESS);
		}
		else
		{
			msg0.SetResult(ASK_DB_OPERATION_R_INTERNAL_ERROR);
		}
		pGamePlayer->SendPacket(&msg0);

		g_pLog->FastSaveLog(LOG_FILE_1, "SCRetDBDefinition D GUID=%X ...OK PID=%d",
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
