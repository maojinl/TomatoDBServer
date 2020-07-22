#include "stdafx.h"
#include "leveldb\env.h"

void UpdateUnitTestPath(Config& config)
{
	char* admindb = "./unittestdata";
	int sz = std::strlen(admindb);
	std::strncpy(config.m_ConfigInfo.m_AdminDBPath, admindb, sz);
	config.m_ConfigInfo.m_AdminDBPath[sz] = '\0';

	char* userdb = "./unittestdata/data";
	sz = std::strlen(userdb);
	std::strncpy(config.m_ConfigInfo.m_DataPath, userdb, sz);
	config.m_ConfigInfo.m_AdminDBPath[sz] = '\0';
	leveldb::Env* env = leveldb::Env::Default();
	if (!env->FileExists(admindb))
	{
		env->CreateDir(admindb);
	}
	if (!env->FileExists(userdb))
	{
		env->CreateDir(userdb);
	}
	return;
}