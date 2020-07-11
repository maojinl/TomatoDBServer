#include "stdafx.h"

#include "CSAskDBQuery.h"
#include "SCRetDBQuery.h"
#include "GamePlayer.h"
#include "IncomingPlayerManager.h"
#include "PacketFactoryManager.h"
#include "WorkerManager.h"
#include "Log.h"
#include "ServerManager.h"'
#include "DB/DatabaseManager.h"

using namespace tomatodb;

UINT CSAskDBQueryHandler::Execute(CSAskDBQuery* pPacket, Player* pPlayer )
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
		DB_QUERY_TYPE qrType = pPacket->GetQueryType();
		SCRetDBQuery msg0;
		BOOL ret;
		vector<string>& values = msg0.GetValues();
		string s;
		switch (qrType)
		{
		case DB_QUERY_TYPE::DB_QUERY_TYPE_DB_LIST:
			ret = g_pDatabaseManager->GetDatabasesList(values);
			break;
		case DB_QUERY_TYPE::DB_QUERY_TYPE_KEY_VALUE:
			ret = tomatodb::g_pDatabaseManager->GetFromDB(std::string(dbname), std::string(pPacket->GetDatabaseKey()), &s);
			values.push_back(s);
			break;
		default:
			ret = FALSE;
			break;
		}

		if (ret)
		{
			msg0.SetResult(ASK_DB_OPERATION_R_SUCCESS);
		}
		else
		{
			msg0.SetResult(ASK_DB_OPERATION_R_INTERNAL_ERROR);
		}
		pGamePlayer->SendPacket(&msg0);

		g_pLog->FastSaveLog(LOG_FILE_1, "SCRetDBQuery D GUID=%X ...OK PID=%d",
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
