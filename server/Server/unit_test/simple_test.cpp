#include "stdafx.h"
#include "gtest/gtest.h"
#include "DatabaseManager.h"

using namespace tomatodb;

class DatabaseManagerTest : public testing::Test {
public:
	DatabaseManager* pDBManager;
};

TEST_F(DatabaseManagerTest, InitFunction) {
	pDBManager = new DatabaseManager(g_Config);
	pDBManager->Init();
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
		, Options());
}

TEST_F(DatabaseManagerTest, CreateAndDeleteDB) {
	pDBManager = new DatabaseManager(g_Config);
	pDBManager->Init();
	pDBManager->CreateDatabase("TestDB");
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(1, dblist.size());
	ASSERT_EQ("TestDB", dblist[0]);
	pDBManager->DeleteDatabase("TestDB");
	dblist.clear();
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
		, Options());
}