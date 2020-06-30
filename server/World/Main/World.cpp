#include "stdafx.h"

#include "World.h"
#include "TimeManager.h"
#include "Log.h"
#include "ServerManager.h"
#include "Config.h"
#include "PlayerPool.h"
#include "PacketFactoryManager.h"
#include "SMUManager.h"
#include "ShareMemManager.h"

#if __LINUX__
#include <sys/signal.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#endif


World g_World ;


int main(int argc, char* argv[])
{
	
#if defined(__WINDOWS__)
	_CrtSetDbgFlag(_CrtSetDbgFlag(0) | _CRTDBG_LEAK_CHECK_DF);
	//Init_CrashCatch();
#endif

__ENTER_FUNCTION

	if( argc>1 )
	{
		for( int i=1; i<argc; i++ )
		{
			if( strcmp(argv[i],"-ignoreassert")==0 )
			{
				g_Command_Assert=1 ;
			}
			if( strcmp(argv[i],"-retryassert")==0 )
			{
				g_Command_Assert=2 ;
			}
			else if( strcmp(argv[i],"-ignoremessagebox")==0 )
			{
				g_Command_IgnoreMessageBox=TRUE ;
			}
		}
	}


	BOOL bRet ;

	//Time manager init first
	g_pTimeManager = new TimeManager ;
	Assert( g_pTimeManager ) ;
	g_pTimeManager->Init( ) ;

	Log::SaveLog( WORLD_LOGFILE, "(###) main..." ) ;
	Log::SaveLog( WORLD_LOGFILE, "World Start... " ) ;

	bRet = g_World.Init( ) ;
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}
	
	bRet = g_World.Loop( ) ;
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}

	bRet = g_World.Exit( ) ;
	if( bRet==FALSE )
	{
		Assert(FALSE) ;
		return 1 ;
	}

__LEAVE_FUNCTION

	return 0 ;
}


World::World( )
{
__ENTER_FUNCTION

#if defined(__WINDOWS__)
	WORD wVersionRequested;
	WSADATA wsaData;
	int err;
	wVersionRequested = MAKEWORD( 2, 2 );
	err = WSAStartup( wVersionRequested, &wsaData ); 
#endif


__LEAVE_FUNCTION
}

World::~World( )
{
__ENTER_FUNCTION

#if defined(__WINDOWS__)
	WSACleanup();
#endif

__LEAVE_FUNCTION
}

BOOL World::Init( )
{
__ENTER_FUNCTION

	BOOL bRet ;

	Log::SaveLog( WORLD_LOGFILE, "Start Read Config Files..." ) ;
	bRet = g_Config.Init( ) ;
	Assert( bRet ) ;
	Log::SaveLog( WORLD_LOGFILE, "Read Config Files...OK!" ) ;

	Log::SaveLog( WORLD_LOGFILE, "Start New Managers..." ) ;
	bRet = NewStaticManager( ) ;
	Assert( bRet ) ;
	Log::SaveLog( WORLD_LOGFILE, "New Managers...OK!" ) ;

	Log::SaveLog( WORLD_LOGFILE, "Start Init Managers..." ) ;
	bRet = InitStaticManager( ) ;
	Assert( bRet ) ;
	Log::SaveLog( WORLD_LOGFILE, "Init Managers...OK!" ) ;

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL World::Loop( )
{
__ENTER_FUNCTION

	Log::SaveLog( WORLD_LOGFILE, "Loop..." ) ;
	g_pServerManager->Loop( ) ;

__LEAVE_FUNCTION

	return TRUE ;
}

BOOL World::Exit( )
{
__ENTER_FUNCTION

	BOOL bRet ;

	Log::SaveLog( WORLD_LOGFILE, "Start Exit..." ) ;
	bRet = DelStaticManager( ) ;
	Assert( bRet ) ;
	Log::SaveLog( WORLD_LOGFILE, "Exit...OK!" ) ;


__LEAVE_FUNCTION

	return TRUE ;
}

BOOL World::NewStaticManager( )
{
__ENTER_FUNCTION
	
//ShareMemory ×îÏÈ

	_WORLD_INFO& WorldInfo = g_Config.m_WorldInfo;

	//
	g_pServerManager = new ServerManager ;
	Assert( g_pServerManager ) ;
	Log::SaveLog( WORLD_LOGFILE, "new ServerManager...OK" ) ;

	//
	g_pPlayerPool = new PlayerPool ;
	Assert( g_pPlayerPool ) ;
	Log::SaveLog( WORLD_LOGFILE, "new PlayerPool...OK" ) ;

	//
	g_pPacketFactoryManager = new PacketFactoryManager ;
	Assert( g_pPacketFactoryManager ) ;
	Log::SaveLog( WORLD_LOGFILE, "new PacketFactoryManager...OK" ) ;
	
__LEAVE_FUNCTION

	return TRUE ;
}

BOOL World::InitStaticManager( )
{
__ENTER_FUNCTION

	BOOL ret ;
	INT nTemp;
    
	//ret = g_GuildSMUPool.Init(10, 111, SMPT_WORLD);

	ret = g_pServerManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( WORLD_LOGFILE, "g_pServerManager->Init()...OK" ) ;

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
	Log::SaveLog( WORLD_LOGFILE, "g_pPlayerPool->Init()...OK" ) ;

	//
	ret = g_pPacketFactoryManager->Init( ) ;
	Assert( ret ) ;
	Log::SaveLog( WORLD_LOGFILE, "g_pPacketFactoryManager->Init()...OK" ) ;

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
		nTemp = 30;
	}
	else
	{
		nTemp = MAX_WORLD_USER;
	}

	if( g_Config.m_ConfigInfo.m_SystemModel == 0 )
	{
		nTemp = 20;
	}
	else
	{
		nTemp = MAX_MAILNODE_SIZE;
	}

	return TRUE;

__LEAVE_FUNCTION

	return FALSE;
}

BOOL World::DelStaticManager( )
{
__ENTER_FUNCTION

	SAFE_DELETE( g_pPacketFactoryManager ) ;
	Log::SaveLog( WORLD_LOGFILE, "g_pPacketFactoryManager delete...OK" ) ;

	SAFE_DELETE( g_pPlayerPool ) ;
	Log::SaveLog( WORLD_LOGFILE, "g_pPlayerPool delete...OK" ) ;

	SAFE_DELETE( g_pServerManager ) ;
	Log::SaveLog( WORLD_LOGFILE, "g_pServerManager delete...OK" ) ;

__LEAVE_FUNCTION

	return TRUE ;
}

VOID INTHandler(INT)
{
	DumpStack("INT exception:\r\n");
	exit(0);
}
VOID TERMHandler(INT)
{
	DumpStack("TERM exception:\r\n");
	exit(0);

}
VOID ABORTHandler(INT)
{
	DumpStack("ABORT exception:\r\n");
	exit(0);
}

VOID ILLHandler(INT)
{
	DumpStack("ILL exception:\r\n");
	exit(0);
}

VOID FPEHandler(INT)
{
	DumpStack("FPE exception:\r\n");
	exit(0);
}

VOID SEGHandler(INT)
{
	DumpStack("SEG exception:\r\n");
	exit(0);
}
VOID XFSZHandler(INT)
{
	DumpStack("XFSZ exception:\r\n");
	exit(0);
}

WorldExceptionHandler::WorldExceptionHandler()
{
#ifdef __LINUX__
	signal(SIGSEGV, SEGHandler);
	signal(SIGFPE,  FPEHandler);
	signal(SIGILL,  ILLHandler);
	signal(SIGINT,  INTHandler);  
	signal(SIGTERM, TERMHandler); 
	signal(SIGABRT, ABORTHandler);
	signal(SIGXFSZ, XFSZHandler);
#endif
}
WorldExceptionHandler g_WorldExceptionHandler;
