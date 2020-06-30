#include "stdafx.h"

#include "Config.h"
#include "Ini.h"
#include "Log.h"
#include "FileDef.h"
#include "DataBase/TLBB_DBC.h"
using namespace DBC;
Config g_Config ;

Config::Config( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

Config::~Config( )
{
__ENTER_FUNCTION

__LEAVE_FUNCTION
}

BOOL Config::Init( )
{
__ENTER_FUNCTION
	LoadConfigInfo( ) ;
	LoadStringInfo();
	LoadLoginInfo();
	LoadWorldInfo( ) ;
	LoadShareMemInfo();
	LoadMachineInfo( ) ;
	LoadServerInfo( ) ;
	LoadWorkersInfo( ) ;
	return TRUE ;
__LEAVE_FUNCTION
	return FALSE ;
}

VOID Config::ReLoad( )
{
	LoadConfigInfo_ReLoad();
	LoadLoginInfo_Reload();
	LoadWorldInfo_ReLoad();
	LoadShareMemInfo_ReLoad();
	LoadMachineInfo_ReLoad();
	LoadServerInfo_ReLoad();
	LoadWorkersInfo_ReLoad();
}

VOID Config::LoadConfigInfo( )
{
__ENTER_FUNCTION
	LoadConfigInfo_Only( ) ;
	LoadConfigInfo_ReLoad( ) ;
__LEAVE_FUNCTION
}

VOID Config::LoadConfigInfo_Only()
{
	//static data
__ENTER_FUNCTION
	Ini ini(FILE_CONFIG_INFO);
	m_ConfigInfo.m_SystemModel = ini.ReadInt( "SystemModel", "SystemModel");
	m_ConfigInfo.m_ServerID = (ID_t)(ini.ReadInt( "System", "ServerId" ));
	ini.ReadText("Global", "DataPath", m_ConfigInfo.m_DataPath, _MAX_PATH);
	ini.ReadText("Global", "AdminDBPath", m_ConfigInfo.m_AdminDBPath, _MAX_PATH);
	Log::SaveLog(CONFIG_LOGFILE, "Load ConfigInfo.ini ...Only OK!") ;
__LEAVE_FUNCTION
}

VOID Config::LoadConfigInfo_ReLoad( )
{
__ENTER_FUNCTION
	Ini ini( FILE_CONFIG_INFO ) ;
	CHAR szText[32];
	Log::SaveLog( CONFIG_LOGFILE, "Load ConfigInfo.ini ...ReLoad OK! " ) ;
__LEAVE_FUNCTION
}

VOID Config::LoadLoginInfo( )
{
	__ENTER_FUNCTION

	LoadLoginInfo_Only( ) ;
	LoadLoginInfo_Reload( ) ;

	__LEAVE_FUNCTION
}
VOID Config::LoadLoginInfo_Only( )
{
	__ENTER_FUNCTION

	Ini ini( FILE_LOGIN_INFO ) ;

	m_LoginInfo.m_LoginID = (ID_t)(ini.ReadInt( "System", "LoginId" )) ;

	ini.ReadText( "System", "DBIP", m_LoginInfo.m_DBIP, IP_SIZE ) ;
	m_LoginInfo.m_DBPort	=	(UINT)(ini.ReadInt("System","DBPort"));
	ini.ReadText( "System", "DBName", m_LoginInfo.m_DBName, DATABASE_STR_LEN ) ;
	ini.ReadText( "System", "DBUser", m_LoginInfo.m_DBUser, DB_USE_STR_LEN ) ;
	ini.ReadText( "System", "DBPassword", m_LoginInfo.m_DBPassword, DB_PASSWORD_STR_LEN ) ;
	m_LoginInfo.m_AskAuthType	=	(BYTE)(ini.ReadInt("System","AskAuthType"));

	Log::SaveLog( CONFIG_LOGFILE, "Load LoginInfo.ini ...Only OK! " ) ;

	__LEAVE_FUNCTION
}
VOID Config::LoadLoginInfo_Reload( )
{//可以重复读取的数据
	__ENTER_FUNCTION
		Log::SaveLog( CONFIG_LOGFILE, "Load LoginInfo.ini ...ReLoad OK! " ) ;
	__LEAVE_FUNCTION
}

VOID Config::LoadWorldInfo( )
{
__ENTER_FUNCTION

	LoadWorldInfo_Only( ) ;
	LoadWorldInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadWorldInfo_Only( )
{
__ENTER_FUNCTION

	Ini ini( FILE_WORLD_INFO ) ;
	m_WorldInfo.m_WorldID	=		(ID_t)(ini.ReadInt( "System", "WorldId" )) ;
	m_WorldInfo.m_MailKey =		(SM_KEY)ini.ReadInt( "System","MailSMKey");
	m_WorldInfo.m_EnableShareMem	=    (BOOL)ini.ReadInt("System","EnableShareMem");

	Log::SaveLog( CONFIG_LOGFILE, "Load WorldInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadWorldInfo_ReLoad( )
{
__ENTER_FUNCTION

	Log::SaveLog( CONFIG_LOGFILE, "Load WorldInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadShareMemInfo()
{
	__ENTER_FUNCTION
	
		LoadShareMemInfo_Only();
		LoadShareMemInfo_ReLoad();

	__LEAVE_FUNCTION
}

VOID	Config::LoadShareMemInfo_Only()
{
	__ENTER_FUNCTION

		Ini ini( FILE_SHARE_MEM_INFO );
		m_ShareMemInfo.m_SMUObjCount=(UINT)ini.ReadInt( "ShareMem", "KeyCount" );
		//m_ShareMemInfo.m_SMUObjCount++; //添加ItemSerial固定Key
		m_ShareMemInfo.m_pShareData	= new _SHAREMEM_DATA[m_ShareMemInfo.m_SMUObjCount];
		

		UINT i;
		for(i=0;i<m_ShareMemInfo.m_SMUObjCount;i++)
		{
			CHAR szKeyID[256] ;
			CHAR szTypeID[256];
			memset( szKeyID,	0,	256 );
			memset( szTypeID,	0,	256);
			sprintf( szKeyID, "Key%d" ,	i) ;
			sprintf(szTypeID, "Type%d",	i);
			m_ShareMemInfo.m_pShareData[i].m_Key	=	(SM_KEY)ini.ReadInt( "ShareMem", szKeyID );
			m_ShareMemInfo.m_pShareData[i].m_Type	=	(SHAREMEM_TYPE)ini.ReadInt( "ShareMem", szTypeID );
		}

		ini.ReadText( "System", "DBIP", m_ShareMemInfo.m_DBIP, IP_SIZE ) ;
		m_ShareMemInfo.m_DBPort	=	(UINT)(ini.ReadInt("System","DBPort"));
		ini.ReadText( "System", "DBName", m_ShareMemInfo.m_DBName, DATABASE_STR_LEN ) ;
		ini.ReadText( "System", "DBUser", m_ShareMemInfo.m_DBUser, DB_USE_STR_LEN ) ;
		ini.ReadText( "System", "DBPassword", m_ShareMemInfo.m_DBPassword, DB_PASSWORD_STR_LEN ) ;
		
		m_ShareMemInfo.SMUInterval	=	ini.ReadInt("System","SMUInterval");
		m_ShareMemInfo.DATAInterval	=	ini.ReadInt("System","DATAInterval");
		
		
		Log::SaveLog( CONFIG_LOGFILE, "Load ShareMemInfo.ini ...Only OK! " ) ;

	__LEAVE_FUNCTION
}

VOID	Config::LoadShareMemInfo_ReLoad()
{
	__ENTER_FUNCTION

	__LEAVE_FUNCTION
}


VOID Config::LoadMachineInfo( )
{
__ENTER_FUNCTION

	LoadMachineInfo_Only( ) ;
	LoadMachineInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadMachineInfo_Only( )
{
__ENTER_FUNCTION

	Ini ini( FILE_MACHINE_INFO ) ;
	m_MachineInfo.m_MachineCount = ini.ReadInt( "System", "MachineNumber" ) ;

	m_MachineInfo.m_pMachine = new _MACHINE_DATA[m_MachineInfo.m_MachineCount] ;
	memset( m_MachineInfo.m_pMachine, 0, sizeof(_MACHINE_DATA)*m_MachineInfo.m_MachineCount ) ;

	for( UINT i=0; i<m_MachineInfo.m_MachineCount; i++ )
	{
		CHAR szSection[256] ;
		memset( szSection, 0, 256 ) ;

		//初始化数据
		m_MachineInfo.m_pMachine[i].Init( ) ;

		//读取场景“i”
		sprintf( szSection, "Machine%d", i ) ;
		m_MachineInfo.m_pMachine[i].m_MachineID = (ID_t)(ini.ReadInt( szSection, "MachineId" )) ;
	}

	Log::SaveLog( CONFIG_LOGFILE, "Load MachineInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadMachineInfo_ReLoad( )
{
__ENTER_FUNCTION

	Log::SaveLog( CONFIG_LOGFILE, "Load MachineInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}

VOID Config::LoadServerInfo( )
{
__ENTER_FUNCTION

	LoadServerInfo_Only( ) ;
	LoadServerInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadServerInfo_Only( )
{
__ENTER_FUNCTION

	Ini ini( FILE_SERVER_INFO ) ;
	m_ServerInfo.m_ServerCount = ini.ReadInt( "System", "ServerNumber" ) ;

	m_ServerInfo.m_pServer = new _SERVER_DATA[m_ServerInfo.m_ServerCount] ;
	memset( m_ServerInfo.m_pServer, 0, sizeof(_SERVER_DATA)*m_ServerInfo.m_ServerCount ) ;

	for( UINT i=0; i<m_ServerInfo.m_ServerCount; i++ )
	{
		CHAR szSection[256] ;
		memset( szSection, 0, 256 ) ;

		//初始化数据
		m_ServerInfo.m_pServer[i].Init( ) ;

		//读取场景“i”
		sprintf( szSection, "Server%d", i ) ;
		m_ServerInfo.m_pServer[i].m_ServerID = (ID_t)(ini.ReadInt( szSection, "ServerId" )) ;
		m_ServerInfo.m_pServer[i].m_MachineID = (ID_t)(ini.ReadInt( szSection, "MachineId" )) ;
		ini.ReadText( szSection, "IP0", m_ServerInfo.m_pServer[i].m_IP0, IP_SIZE ) ;
		m_ServerInfo.m_pServer[i].m_Port0 = (UINT)(ini.ReadInt( szSection, "Port0" )) ;
		ini.ReadText( szSection, "IP1", m_ServerInfo.m_pServer[i].m_IP1, IP_SIZE ) ;
		m_ServerInfo.m_pServer[i].m_Port1 = (UINT)(ini.ReadInt( szSection, "Port1" )) ;
		//enum SERVER_TYPE
		m_ServerInfo.m_pServer[i].m_Type = (UINT)(ini.ReadInt( szSection, "Type" )) ;
		m_ServerInfo.m_pServer[i].m_HumanSMKey	=	(SM_KEY)(ini.ReadInt(szSection,"HumanSMKey"));
		m_ServerInfo.m_pServer[i].m_PlayShopSMKey = (SM_KEY)(ini.ReadInt(szSection,"PlayShopSMKey"));
		m_ServerInfo.m_pServer[i].m_ItemSerialKey = (SM_KEY)(ini.ReadInt(szSection,"ItemSerialKey"));

        //排行榜相关
		//m_ServerInfo.m_pServer[i].m_RangeDataSMKey  = (SM_KEY)(ini.ReadInt(szSection,"RangeDataSMKey"));

		m_ServerInfo.m_pServer[i].m_EnableShareMem = (BOOL)(ini.ReadInt(szSection,"EnableShareMem"));


	}

	ini.ReadText( "World", "IP", m_ServerInfo.m_World.m_IP, IP_SIZE ) ;
	m_ServerInfo.m_World.m_Port = (UINT)(ini.ReadInt( "World", "Port" )) ;


	//
	for(UINT i=0; i<m_ServerInfo.m_ServerCount; i++ )
	{
		ID_t ServerID = m_ServerInfo.m_pServer[i].m_ServerID ;

		Assert( ServerID != INVALID_ID && ServerID < OVER_MAX_SERVER ) ;

		Assert( m_ServerInfo.m_HashServer[ServerID] == -1 ) ;

		m_ServerInfo.m_HashServer[ServerID] = i ;
	}

	Log::SaveLog( CONFIG_LOGFILE, "Load ServerInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadServerInfo_ReLoad( )
{
__ENTER_FUNCTION

	Log::SaveLog( CONFIG_LOGFILE, "Load ServerInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}

VOID Config::LoadWorkersInfo( )
{
__ENTER_FUNCTION

	LoadWorkersInfo_Only( ) ;
	LoadWorkersInfo_ReLoad( ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadWorkersInfo_Only( )
{
__ENTER_FUNCTION

	Ini ini( FILE_SCENE_INFO ) ;

	//workers thread info
	m_WorkerInfo.m_WorkerCount = (UINT)(ini.ReadInt( "system", "workersnumber" )) ;

	m_WorkerInfo.m_pWorker = new _WORKER_DATA[m_WorkerInfo.m_WorkerCount] ;
	memset( m_WorkerInfo.m_pWorker, 0, sizeof(_WORKER_DATA)*m_WorkerInfo.m_WorkerCount ) ;


	for( WorkerID_t i=0; i<m_WorkerInfo.m_WorkerCount; i++ )
	{
		CHAR szSection[256] ;
		memset( szSection, 0, 256 ) ;
		sprintf( szSection, "worker%d", i ) ;
		m_WorkerInfo.m_pWorker[i].m_WorkerID = i ;
		m_WorkerInfo.m_pWorker[i].m_ServerID = (ID_t)(ini.ReadInt( szSection, "serverId" )) ;
		m_WorkerInfo.m_pWorker[i].m_Type = (ID_t)(ini.ReadInt( szSection, "type" )) ;
		m_WorkerInfo.m_pWorker[i].m_ThreadIndex = (ID_t)(ini.ReadInt( szSection, "threadindex" )) ;
	}

	//
	for(WorkerID_t i=0; i<m_WorkerInfo.m_WorkerCount; i++ )
	{
		WorkerID_t SceneID = m_WorkerInfo.m_pWorker[i].m_WorkerID ;

		Assert( SceneID!=INVALID_ID && SceneID<MAX_WORKER ) ;

		Assert( m_WorkerInfo.m_HashWorker[SceneID]==-1 ) ;

		m_WorkerInfo.m_HashWorker[SceneID] = i ;
	}

	Log::SaveLog( CONFIG_LOGFILE, "Load SceneInfo.ini ...Only OK! " ) ;

__LEAVE_FUNCTION
}
VOID Config::LoadWorkersInfo_ReLoad( )
{
__ENTER_FUNCTION

	Log::SaveLog( CONFIG_LOGFILE, "Load SceneInfo.ini ...ReLoad OK! " ) ;

__LEAVE_FUNCTION
}

ID_t Config::Key2ServerID(SM_KEY key) const
{
	__ENTER_FUNCTION
	
		Assert(key>0);
		
			for( UINT i=0; i<m_ServerInfo.m_ServerCount; i++ )
			{

				if(m_ServerInfo.m_pServer[i].m_EnableShareMem)
				{
					if(m_ServerInfo.m_pServer[i].m_ItemSerialKey == key)
					{
						return	m_ServerInfo.m_pServer[i].m_ServerID;
					}
				}
				
			}

	return -1;
		
	__LEAVE_FUNCTION

	return -1;	
}

VOID    Config::LoadStringInfo()
{
	__ENTER_FUNCTION

		LoadStringInfo_Only();

	__LEAVE_FUNCTION
}
VOID Config::LoadStringInfo_Only( )
{
	__ENTER_FUNCTION

	DBCFile ThirdFile(0);
	BOOL ret = ThirdFile.OpenFromTXT( FILE_STRING_INFO );

	INT iTableCount = ThirdFile.GetRecordsNum();

	AssertEx(iTableCount==MAX_STRING_INFO_COUNT,"请检查字符定义和配置文件数目是否一致！");

	for(INT i = 0;	i<MAX_STRING_INFO_COUNT;i++)
		strncpy(m_StringInfo[i].m_String , ThirdFile.Search_Posistion(i,1)->pString,	sizeof(CHAR)*MAX_STRING);
	
	
	Log::SaveLog( CONFIG_LOGFILE, "Load StringInfo.txt ...OK! " ) ;

	__LEAVE_FUNCTION
}