#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include "StringArrayTable.h"
#include "unittestutils.h"

#include "util/coding.h"
	
using namespace tomatodb;


class DBLinkTest : public testing::Test {
public:
	DatabaseManager* pDBManager = nullptr;
	string testdb1 = "testdb1";
	string testdb2 = "testdb2";

	DBLinkTest()
	{
		UpdateUnitTestPath(g_Config);
		AdminDB::ReleaseInstance();
	}

	~DBLinkTest()
	{
		SAFE_DELETE(pDBManager);
		DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
			, Options());
	}
};