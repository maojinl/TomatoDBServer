#include "stdafx.h"
// Server.cpp : Defines the entry point for the console application.
// 

#include "Server.h"
#include "Log.h"
#include "Ini.h"
#include "FileDef.h"
#include "TimeManager.h"
#include "ClientManager.h"
#include "WorkerManager.h"
#include "ThreadManager.h"
#include "PlayerPool.h"
#include "Config.h"
#include "Thread.h"
#include "PacketFactoryManager.h"
#include "ServerManager.h"
#include "MachineManager.h"
#include "GUIDManager.h"
#include "SMUManager.h"
#include "ShareMemManager.h"
#include "Performance.h"
#include "DaemonThread.h"
#include "DB/DatabaseManager.h"
#include <gtest\gtest.h>

Server g_Server;

//#define RUN_UNIT_TESTS

INT main(INT argc, CHAR* argv[])
{
#if defined(__WINDOWS__)
	_CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
#endif
	//Init_CrashCatch();
	__ENTER_FUNCTION

	if( argc>1 )
	{
		for( int i=1; i<argc; i++ )
		{
			if( strcmp(argv[i],"-ignoreassert")==0 )
			{
				g_Command_Assert=1 ;
			}
			else if( strcmp(argv[i],"-retryassert")==0 )
			{
				g_Command_Assert=2 ;
			}

			if(strcmp(argv[i],"-ignoremessagebox") == 0)
			{
				g_Command_IgnoreMessageBox=TRUE;
			}
		}
	}

	BOOL ret;

	ret = g_Server.InitConfig();
	Assert(ret);

	g_pTimeManager = new TimeManager;
	Assert(g_pTimeManager);
	ret = g_pTimeManager->Init();
	Assert(ret);

	g_pLog = new Log ;
	Assert( g_pLog ) ;
	ret = g_pLog->Init( ) ;
	Assert(ret) ;

	Log::SaveLog( SERVER_LOGFILE, "\r\n(###) main..." ) ;

	g_pTimeManager->SetTime( ) ;
	Log::SaveLog( SERVER_LOGFILE, "Server Starting... (%.10d)(%d)",
		g_pTimeManager->Time2DWORD(),
		g_pTimeManager->StartTime() ) ;

	ret = g_Server.InitServer( );
	Assert( ret ) ;

#if defined(RUN_UNIT_TESTS)
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
#endif

	ret = g_Server.Loop();
	Assert( ret ) ;

	ret = g_Server.ExitServer();
	Assert( ret ) ;

__LEAVE_FUNCTION
	
	return 0;
}

Server::Server()
{
__ENTER_FUNCTION
#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA wsaData;
	INT err;
	wVersionRequested = MAKEWORD(2, 2);
	err = WSAStartup( wVersionRequested, &wsaData ); 
#endif
	m_TimeToQuit.CleanUp();

__LEAVE_FUNCTION
}

Server::~Server()
{
__ENTER_FUNCTION

#if defined(__WINDOWS__)
	WSACleanup();
#endif

__LEAVE_FUNCTION

}

//___________________________________
BOOL Server::InitConfig()
{
__ENTER_FUNCTION
	BOOL ret = FALSE;
	ret = g_Config.Init();
	Assert(ret);
	return TRUE;
__LEAVE_FUNCTION
	return TRUE;
}
//___________________________________

BOOL Server::InitServer()
{
__ENTER_FUNCTION

	BOOL ret = FALSE;
	Log::SaveLog(SERVER_LOGFILE, "InitServer FD_SETSIZE=%d...", FD_SETSIZE);

	ret = NewStaticServer();
	Assert(ret);

	ret = InitStaticServer();
	Assert(ret);

__LEAVE_FUNCTION

	return TRUE;
}

BOOL Server::Loop()
{
__ENTER_FUNCTION
	BOOL ret = FALSE;
	Log::SaveLog(SERVER_LOGFILE, "\r\nLoop...");

	Log::SaveLog(SERVER_LOGFILE, "g_pThreadManager->Start( )...");
	ret = g_pThreadManager->Start();
	Assert(ret);

	MySleep(2000);

	Log::SaveLog(SERVER_LOGFILE, "g_pClientManager->Loop( )...");
	g_pClientManager->start();

	Log::SaveLog(SERVER_LOGFILE, "g_pDaemonThread->Loop( )...");
	g_pDaemonThread->Loop();

__LEAVE_FUNCTION

	return TRUE;
}

BOOL Server::ExitServer()
{
__ENTER_FUNCTION

	Log::SaveLog(SERVER_LOGFILE, "\r\nExitServer...");

	WaitForAllThreadQuit() ;

	Log::SaveLog(SERVER_LOGFILE, "Begin delete...");

	SAFE_DELETE(g_pClientManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pClientManager delete...OK");
	SAFE_DELETE(g_pThreadManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pThreadManager delete...OK");

	SAFE_DELETE(g_pWorkerManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pWorkerManager delete...OK");
	SAFE_DELETE(g_pPlayerPool);
	Log::SaveLog(SERVER_LOGFILE, "g_pPlayerPool delete...OK");
	SAFE_DELETE(g_pPacketFactoryManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pPacketFactoryManager delete...OK");
	SAFE_DELETE(g_pServerManager ) ;
	Log::SaveLog(SERVER_LOGFILE, "g_pServerManager delete...OK");
	SAFE_DELETE(g_pMachineManager ) ;
	Log::SaveLog(SERVER_LOGFILE, "g_pMachineManager delete...OK");
	SAFE_DELETE(g_pGUIDManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pGUIDManager delete...OK");

	SAFE_DELETE(g_pPerformanceManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pPerformanceManager delete...OK");
	SAFE_DELETE(g_pDaemonThread);
	Log::SaveLog(SERVER_LOGFILE, "g_pDaemonThread delete...OK");
	SAFE_DELETE(g_pTimeManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pTimeManager delete...OK");
	SAFE_DELETE(g_pLog);
	Log::SaveLog(SERVER_LOGFILE, "g_pLog delete...OK");

	SAFE_DELETE(tomatodb::g_pDatabaseManager);
	Log::SaveLog(SERVER_LOGFILE, "g_pDatabaseManager delete...OK");
__LEAVE_FUNCTION

	return TRUE;
}

VOID Server::WaitForAllThreadQuit()
{
__ENTER_FUNCTION

#define MAX_WAIT_QUIT 300

	INT iQuit;
	for(INT i=0; i < MAX_WAIT_QUIT; i++)
	{
		iQuit = g_QuitThreadCount;
		printf("Quit Thread:%d", iQuit);
		MySleep(1000);
		if(iQuit == g_pThreadManager->GetTotalThreads() + 1)
			break;
	}

__LEAVE_FUNCTION
}

BOOL Server::NewStaticServer()
{
__ENTER_FUNCTION
	BOOL ret = FALSE;
	Log::SaveLog(SERVER_LOGFILE, "\r\nNewStaticServer( )...OK");

	g_pWorkerManager = new WorkerManager;
	Assert(g_pWorkerManager);
	Log::SaveLog(SERVER_LOGFILE, "new SceneManager...OK");

	g_pPlayerPool = new PlayerPool;
	Assert(g_pPlayerPool);
	Log::SaveLog( SERVER_LOGFILE, "new PlayerPool...OK" );

	g_pPacketFactoryManager = new PacketFactoryManager;
	Assert(g_pPacketFactoryManager);
	Log::SaveLog(SERVER_LOGFILE, "new PacketFactoryManager...OK");

	g_pServerManager = new ServerManager;
	Assert(g_pServerManager);
	Log::SaveLog(SERVER_LOGFILE, "new ServerManager...OK");

	g_pMachineManager = new MachineManager;
	Assert(g_pMachineManager);
	Log::SaveLog( SERVER_LOGFILE, "new MachineManager...OK");

	g_pGUIDManager = new GUIDManager;
	Assert(g_pGUIDManager);
        Log::SaveLog(SERVER_LOGFILE, "new GUIDManager...OK");

	g_pDaemonThread = new DaemonThread;
	Assert(g_pDaemonThread);
	Log::SaveLog(SERVER_LOGFILE, "new DaemonThread...OK");

	g_pPerformanceManager = new PerformanceManager;
	Assert(g_pPerformanceManager);
	Log::SaveLog(SERVER_LOGFILE, "new PerformanceManager...OK");

	g_pThreadManager = new ThreadManager;
	Assert(g_pThreadManager);
	Log::SaveLog(SERVER_LOGFILE, "new pThreadManager...OK");

	g_pClientManager = new ClientManager;
	Assert(g_pClientManager);
	Log::SaveLog(SERVER_LOGFILE, "new ClientManager...OK");

	tomatodb::g_pDatabaseManager = new tomatodb::DatabaseManager(g_Config);
	Assert(tomatodb::g_pDatabaseManager);
	Log::SaveLog(SERVER_LOGFILE, "new g_pDatabaseManager...OK");
	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

VOID Server::Stop()
{
__ENTER_FUNCTION

	if(g_pThreadManager)
	{
		g_pThreadManager->Stop();
	}

	if(g_pClientManager)
	{
		g_pClientManager->stop();
	}

	if( g_pDaemonThread )
	{
		g_pDaemonThread->Stop();
	}

__LEAVE_FUNCTION
}

BOOL Server::InitStaticServer( )
{
__ENTER_FUNCTION

	BOOL ret = FALSE ;
	INT nTemp = 0;

	Log::SaveLog( SERVER_LOGFILE, "\r\nInitStaticServer( )...OK" ) ;

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
        nTemp = (g_Config.m_WorkerInfo.m_WorkerCount<10) ? g_Config.m_WorkerInfo.m_WorkerCount : 10;
	}
	else
	{
		nTemp = MAX_POOL_SIZE;
	}
	
	const _SERVER_DATA*	pCurrentSData =	g_pServerManager->GetCurrentServerInfo();
	
	if(pCurrentSData->m_EnableShareMem)
	{
		ret = g_HumanSMUPool.Init(/*g_pPlayerPool->GetPlayerPoolMaxCount()*//*________________*/nTemp,pCurrentSData->m_HumanSMKey,SMPT_SERVER);
		AssertEx(ret,"ShareMemory error");

		if(g_HumanSMUPool.GetHeadVer()!=0)
		{
			AssertEx(ret,"ShareMemory Server");
		}
	}

	//
	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
		nTemp = 10;
	}
	else
	{
		nTemp = MAX_POOL_SIZE;
	}
	ret = g_pPlayerPool->Init( nTemp ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pPlayerPool->Init()...OK" ) ;

	//
	ret = g_pPacketFactoryManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pPacketFactoryManager->Init()...OK" ) ;

	//
	ret = g_pMachineManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pMachineManager->Init()...OK" ) ;

	//
	ret = g_pGUIDManager->Init( ) ;
	Assert( ret );
	Log::SaveLog( SERVER_LOGFILE, "g_pGUIDManager->Init()...OK" ) ;

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
		nTemp = 1000;
	}
	else
	{
		nTemp = 1; // MAX_ITEM_BOX_POOL;
	}

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
        nTemp = (g_Config.m_WorkerInfo.m_WorkerCount<10) ? g_Config.m_WorkerInfo.m_WorkerCount : 10;
    }
	else
	{
		nTemp = g_Config.m_WorkerInfo.m_WorkerCount;
	}
	ret = g_pWorkerManager->Init( nTemp ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_SceneManager->Init()...OK" ) ;

	ret = g_pPerformanceManager->Init( );
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pPerformanceManager->Init()...OK" ) ;

	ret = g_pServerManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pServerManager->Init()...OK" ) ;

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
        nTemp = (g_Config.m_WorkerInfo.m_WorkerCount<10) ? g_Config.m_WorkerInfo.m_WorkerCount : 10;
    }
	else
	{
		nTemp = g_Config.m_WorkerInfo.m_WorkerCount;
	}
	ret = g_pThreadManager->Init( nTemp ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pThreadManager->Init()...OK" ) ;

	//
	ret = g_pClientManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pClientManager->Init()...OK" ) ;

	//
	ret = g_pDaemonThread->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( SERVER_LOGFILE, "g_pDaemonThread->Init()...OK" ) ;

	ret = tomatodb::g_pDatabaseManager->Init();
	Assert(ret);
	Log::SaveLog(SERVER_LOGFILE, "g_pDatabaseManager->Init()...OK");

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

ServerSystemSignalHandler g_ServerSystemSignalHandler;

