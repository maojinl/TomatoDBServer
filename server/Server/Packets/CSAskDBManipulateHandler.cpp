#include "stdafx.h"

#include "CSAskDBManipulate.h"
#include "SCRetDBManipulate.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"'
#include "DB/DatabaseManager.h"

using namespace tomatodb;

UINT CSAskDBManipulateHandler::Execute(CSAskDBManipulate* pPacket, Player* pPlayer )
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
		Assert( MyGetCurrentThreadID() == pWorker->m_ThreadID ) ;

		PlayerID_t PlayerID = pGamePlayer->PlayerID() ;
		CHAR	dbname[MAX_DATABASE_NAME + 1];
		strncpy(dbname, pPacket->GetDatabaseName(), MAX_DATABASE_NAME);
		dbname[MAX_DATABASE_NAME] = '\0';
		DB_MANIPULATE_TYPE manType = pPacket->GetManipulateType();

		BOOL ret;
		switch (manType)
		{
		case DB_MANIPULATE_TYPE::DB_MANIPULATE_TYPE_INSERT:
			ret = tomatodb::g_pDatabaseManager->InsertIntoDB(
				std::string(dbname),
				std::string(pPacket->GetDatabaseKey()),
				std::string(pPacket->GetDatabaseValue()),
				pWorker->WorkerID()
			);
			break;
		case DB_MANIPULATE_TYPE::DB_MANIPULATE_TYPE_DELETE:
			ret = tomatodb::g_pDatabaseManager->DeleteFromDB(
				std::string(dbname),
				std::string(pPacket->GetDatabaseKey()),
				pWorker->WorkerID()
			);
			break;
		default:
			ret = FALSE;
			break;
		}

		SCRetDBManipulate msg0;
		msg0.SetManipulateType(manType);
		if (ret)
		{
			msg0.SetResult(ASK_DB_OPERATION_R_SUCCESS);
		}
		else
		{
			msg0.SetResult(ASK_DB_OPERATION_R_INTERNAL_ERROR);
		}
		pGamePlayer->SendPacket(&msg0);

		g_pLog->FastSaveLog(LOG_FILE_1, "CSAskInsertIntoDB D GUID=%X ...OK PID=%d",
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
