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

TEST_F(DatabaseManagerTest, AccessDataDB) {
	pDBManager = new DatabaseManager(g_Config);
	pDBManager->Init();
	pDBManager->CreateDatabase("TestDB");
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	string retVal;
	pDBManager->InsertIntoDB("TestDB", "key1", "val1", 0);
	pDBManager->GetFromDB("TestDB", "key1", &retVal);
	ASSERT_EQ("val1", retVal);
	pDBManager->InsertIntoDB("TestDB", "key1", "val2", 0);
	pDBManager->GetFromDB("TestDB", "key1", &retVal);
	ASSERT_EQ("val2", retVal);
	pDBManager->InsertIntoDB("TestDB", "key2", "val3", 0);
	pDBManager->GetFromDB("TestDB", "key2", &retVal);
	ASSERT_EQ("val3", retVal);
	pDBManager->DeleteFromDB("TestDB", "key1", 0);
	BOOL ret = pDBManager->GetFromDB("TestDB", "key1", &retVal);
	ASSERT_EQ(FALSE, ret);
	pDBManager->DeleteDatabase("TestDB");
	dblist.clear();
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
		, Options());
}