#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include "unittestutils.h"
	
using namespace tomatodb;


class DBLinkTest : public testing::Test {
public:
	DatabaseManager* pDBManager;
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

TEST_F(DBLinkTest, AddLinks) {
	pDBManager = new DatabaseManager(g_Config);
	pDBManager->Init();
	AdminDB* pAdmin = AdminDB::GetInstance();
	pAdmin->AddLink(testdb1, testdb2);
	pAdmin->AddLink(testdb1, "testdb3");
	vector<string> links_list;
	pAdmin->GetLinksList(testdb1, links_list);
	ASSERT_EQ(2, links_list.size());
	SAFE_DELETE(pDBManager);
	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
		, Options());
}
