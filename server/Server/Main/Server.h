#ifndef __SERVER_H__
#define __SERVER_H__

#include "Type.h"

class Server
{
public :
	Server( ) ;
	~Server( ) ;

	BOOL	InitConfig();

	BOOL	InitServer( ) ;
	BOOL	Loop( ) ;
	BOOL	ExitServer( ) ;

	BOOL	NewStaticServer( ) ;
	BOOL	InitStaticServer( ) ;

	VOID	Stop( ) ;

	VOID	WaitForAllThreadQuit( ) ;


public :
	CMyTimer m_TimeToQuit ;
};

extern Server g_Server ;



class ServerSystemSignalHandler
{
public:
#ifdef __LINUX__
	#include <signal.h>
	static VOID INTHandler(INT)
	{
		DumpStack("INT exception:\r\n");
		g_Server.Stop();
	}

	static VOID TERMHandler(INT)
	{
		DumpStack("TERM exception:\r\n");
		g_Server.Stop();
	}

	static VOID ABORTHandler(INT)
	{
		DumpStack("ABORT exception:\r\n");
		g_Server.Stop();
	}

	static VOID ILLHandler(INT)
	{
		DumpStack("ILL exception:\r\n");
		g_Server.Stop();
	}

	static VOID FPEHandler(INT)
	{
		DumpStack("FPE exception:\r\n");
		g_Server.Stop();
	}

	static VOID SEGHandler(INT)
	{
		DumpStack("SEG exception:\r\n");
		g_Server.Stop();
	}
	static VOID XFSZHandler(INT)
	{
		DumpStack("XFSZ exception:\r\n");
		g_Server.Stop();
	}

	ServerSystemSignalHandler() {
		signal(SIGSEGV, SEGHandler);
		signal(SIGFPE, FPEHandler);
		signal(SIGILL, ILLHandler);
		signal(SIGINT, INTHandler);
		signal(SIGTERM, TERMHandler);
		signal(SIGABRT, ABORTHandler);
		signal(SIGXFSZ, XFSZHandler);
	};
#elif __WINDOWS__ 
	static BOOL CtrlHandler(DWORD fdwctrltype)
	{
		switch (fdwctrltype)
		{
			// handle the ctrl-c signal.
			case CTRL_C_EVENT:
			case CTRL_CLOSE_EVENT:
			case CTRL_BREAK_EVENT:
			case CTRL_LOGOFF_EVENT:
			case CTRL_SHUTDOWN_EVENT:
				g_Server.Stop();
				return TRUE;
			default:
				return TRUE;
		};
	};

	ServerSystemSignalHandler() {
		bool ret = SetConsoleCtrlHandler((PHANDLER_ROUTINE)CtrlHandler, true);
		Assert(ret);
	};
#endif
};

extern ServerSystemSignalHandler g_ServerSystemSignalHandler;

#endif
