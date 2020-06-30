#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "Type.h"
#include "GameDefine.h"

enum SERVER_TYPE
{ 
  SERVER_GAME = 0,
  SERVER_LOGIN = 1,
  SERVER_SHAREMEN = 2,
  SERVER_WORLD = 3,
  SERVER_NUMBER,
};

//Config
struct _CONFIG_INFO
{
	INT				m_SystemModel;
	ID_t			m_ServerID;
	CHAR			m_DataPath[_MAX_PATH]; //data base files folder
	CHAR			m_AdminDBPath[_MAX_PATH]; //admin data base files folder
	_CONFIG_INFO( )
	{
		m_ServerID = INVALID_ID ;
		m_SystemModel = 0;
	};
	~_CONFIG_INFO( )
	{
	};
};

    //Login
struct _LOGIN_INFO
{
	enum ASKAUTHTYPE
	{
		USE_BILLING = 0,
		USE_WEB,
	};
	ID_t			m_LoginID ;
	CHAR			m_DBIP[IP_SIZE];
	UINT			m_DBPort;
	CHAR			m_DBName[DATABASE_STR_LEN];
	CHAR			m_DBUser[DB_USE_STR_LEN];
	CHAR			m_DBPassword[DB_PASSWORD_STR_LEN];
	INT			    m_AskAuthType;
	CHAR			m_ClientMainPath[MAX_PATH];

	_LOGIN_INFO()
	{
		m_LoginID = INVALID_ID;
		m_AskAuthType = USE_BILLING;
	}
	~_LOGIN_INFO()
	{

	}
};

//World
struct _WORLD_INFO
{
	ID_t			m_WorldID ;
	SM_KEY			m_MailKey;

	BOOL			m_EnableShareMem;
	_WORLD_INFO( )
	{
		m_WorldID	= INVALID_ID ;
		m_MailKey =	0;
		m_EnableShareMem = FALSE;
	}
	~_WORLD_INFO( )
	{
	}
};

//ShareMem
enum SHAREMEM_TYPE {
  ST_INVAILD = -1,
  ST_NORMAL = 1,
};

struct _SHAREMEM_DATA
{
	SM_KEY				m_Key;
	SHAREMEM_TYPE		m_Type;

	_SHAREMEM_DATA()
	{
		m_Key	=	0;
		m_Type	=	ST_INVAILD;
	}
};

struct _SHAREMEM_INFO 
{
	UINT				m_SMUObjCount;

	_SHAREMEM_DATA*	    m_pShareData;

	CHAR			m_DBIP[IP_SIZE];
	UINT			m_DBPort;
	CHAR			m_DBName[DATABASE_STR_LEN];
	CHAR			m_DBUser[DB_USE_STR_LEN];
	CHAR			m_DBPassword[DB_PASSWORD_STR_LEN];
	INT				SMUInterval;
	INT				DATAInterval;
	_SHAREMEM_INFO()
	{
		m_pShareData	=	NULL;
		m_SMUObjCount	=	0;
		memset(m_DBIP,0,IP_SIZE);
		m_DBPort		= -1;
		memset(m_DBName,0,DATABASE_STR_LEN);
		memset(m_DBUser,0,DB_USE_STR_LEN);
		memset(m_DBPassword,0,DB_PASSWORD_STR_LEN);
		SMUInterval		= 60;
		DATAInterval	= 300000;
	}
	~_SHAREMEM_INFO()
	{
		SAFE_DELETE_ARRAY(m_pShareData);
	};
};

//Machine
struct _MACHINE_DATA
{
	ID_t			m_MachineID ;

	_MACHINE_DATA( )
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_MachineID = INVALID_ID ;
	}
};

struct _MACHINE_INFO
{
	_MACHINE_DATA*	m_pMachine ;
	UINT			m_MachineCount ;

	_MACHINE_INFO( )
	{
		m_pMachine = NULL ;
		m_MachineCount = 0 ;
	};
	~_MACHINE_INFO( )
	{
		SAFE_DELETE_ARRAY( m_pMachine ) ;
		m_MachineCount = 0 ;
	};
};

//Server
struct _SERVER_DATA
{
	ID_t			m_ServerID ;
	ID_t			m_MachineID ;
	CHAR			m_IP0[IP_SIZE] ;
	UINT			m_Port0 ;
	CHAR			m_IP1[IP_SIZE] ;
	UINT			m_Port1 ;
	INT				m_Type ;

	SM_KEY			m_HumanSMKey;
	SM_KEY			m_PlayShopSMKey;
	SM_KEY			m_ItemSerialKey;

	BOOL			m_EnableShareMem;


	_SERVER_DATA( )
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_ServerID = INVALID_ID ;
		m_MachineID = INVALID_ID ;
		memset( m_IP0, 0, IP_SIZE ) ;
		m_Port0 = 0 ;
		memset( m_IP1, 0, IP_SIZE ) ;
		m_Port1 = 0 ;
		m_Type = -1 ;
		m_EnableShareMem = FALSE;
	}
};
struct _SERVER_WORLD
{
	CHAR			m_IP[IP_SIZE] ;
	UINT			m_Port ;

	_SERVER_WORLD( )
	{
		Init( ) ;
	}
	VOID Init( )
	{
		memset( m_IP, 0, IP_SIZE ) ;
		m_Port = 0 ;
	}
};



#define OVER_MAX_SERVER 256
struct _SERVER_INFO
{
	_SERVER_DATA*	m_pServer ;	
	UINT			m_ServerCount ;
	INT				m_HashServer[OVER_MAX_SERVER] ;
	_SERVER_WORLD	m_World ;

	_SERVER_INFO( )
	{
		m_pServer = NULL ;
		m_ServerCount = 0 ;
		for( INT i=0; i<OVER_MAX_SERVER; i++ )
		{
			m_HashServer[i] = -1 ;
		}
	}
	~_SERVER_INFO( )
	{
		SAFE_DELETE_ARRAY( m_pServer ) ;
		m_ServerCount = 0 ; 
	}
};


//Worker
struct _WORKER_DATA
{
	WorkerID_t		m_WorkerID ;
	ID_t			m_ServerID ;
	ID_t			m_Type ;
	ID_t			m_ThreadIndex ;

	_WORKER_DATA()
	{
		Init( ) ;
	};
	VOID Init( )
	{
		m_WorkerID = INVALID_ID ;
		m_ServerID = INVALID_ID ;
		m_Type = INVALID_ID ;
		m_ThreadIndex = INVALID_INDEX ;
	}
};


struct _WORKER_INFO
{
	_WORKER_DATA*	m_pWorker ;
	WorkerID_t		m_WorkerCount ;
	INT				m_HashWorker[MAX_WORKER] ;

	_WORKER_INFO(){
		m_pWorker = NULL ;
		m_WorkerCount = 0 ;
		for( INT i=0; i< MAX_WORKER; i++ )
		{
			m_HashWorker[i] = INVALID_ID ;
		}
	};
	~_WORKER_INFO(){
		SAFE_DELETE_ARRAY(m_pWorker) ;
		m_WorkerCount = 0 ;
	};
};


struct _STRING_INFO
{
	_STRING_INFO()
	{
		memset(m_String,0,sizeof(CHAR)*MAX_STRING );
	}
	CHAR  m_String[MAX_STRING];

};

class Config
{
public :
	Config( ) ;
	~Config( ) ;

	BOOL					Init( ) ;
	VOID					ReLoad( ) ;

	VOID					LoadConfigInfo( ) ;
	VOID					LoadConfigInfo_Only( ) ;
	VOID					LoadConfigInfo_ReLoad( ) ;

	VOID					LoadLoginInfo( );
	VOID					LoadLoginInfo_Only( );
	VOID					LoadLoginInfo_Reload( );

	VOID					LoadWorldInfo( ) ;
	VOID					LoadWorldInfo_Only( ) ;
	VOID					LoadWorldInfo_ReLoad( ) ;

	VOID					LoadShareMemInfo();
	VOID					LoadShareMemInfo_Only();
	VOID					LoadShareMemInfo_ReLoad();
	
	VOID					LoadMachineInfo( ) ;
	VOID					LoadMachineInfo_Only( ) ;
	VOID					LoadMachineInfo_ReLoad( ) ;
	
	VOID					LoadServerInfo( ) ;
	VOID					LoadServerInfo_Only( ) ;
	VOID					LoadServerInfo_ReLoad( ) ;
	
	VOID					LoadWorkersInfo( ) ;
	VOID					LoadWorkersInfo_Only( ) ;
	VOID					LoadWorkersInfo_ReLoad( );

	ID_t					SceneID2ServerID(WorkerID_t sID) const;

	ID_t					Key2ServerID(SM_KEY key)	const;

	VOID                    LoadStringInfo();
	VOID                    LoadStringInfo_Only();

public :
	_CONFIG_INFO			m_ConfigInfo ;
	_LOGIN_INFO				m_LoginInfo;
	_WORLD_INFO				m_WorldInfo ;
	_MACHINE_INFO			m_MachineInfo ;
	_SERVER_INFO			m_ServerInfo ;
	_WORKER_INFO			m_WorkerInfo ;
	_SHAREMEM_INFO			m_ShareMemInfo;
	_STRING_INFO            m_StringInfo[MAX_STRING_INFO_COUNT];

public:
	const CHAR* GetString( UINT iIndex)const { return  m_StringInfo[iIndex].m_String;}

};


extern Config g_Config ;

#endif
