#include "stdafx.h"
#include "ShareDBManager.h"
#include "Config.h"
#include "TimeManager.h"
#include "Log.h"

ShareDBManager* g_pDBManager = NULL;

BOOL	ShareDBManager::Init()
{
	__ENTER_FUNCTION

	UINT	Port							=	g_Config.m_ShareMemInfo.m_DBPort;	//连接对端端口
	CHAR	Database[DATABASE_STR_LEN];
	strncpy(Database,g_Config.m_ShareMemInfo.m_DBName,DATABASE_STR_LEN);			//数据库名称
	Database[DATABASE_STR_LEN-1] = '\0';

	CHAR	User[DB_USE_STR_LEN];												//用户名称
	strncpy(User,g_Config.m_ShareMemInfo.m_DBUser,DB_USE_STR_LEN);
	User[DB_USE_STR_LEN-1] = '\0';

	CHAR	Password[DB_PASSWORD_STR_LEN];										//密码
	strncpy(Password,g_Config.m_ShareMemInfo.m_DBPassword,DB_PASSWORD_STR_LEN);
	Password[DB_PASSWORD_STR_LEN-1] = '\0';


	return TRUE;

	__LEAVE_FUNCTION

		return FALSE;
}

VOID ShareDBManager::run()
{
	__ENTER_FUNCTION

		
	__LEAVE_FUNCTION
}