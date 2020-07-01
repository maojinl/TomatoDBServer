#include "stdafx.h"
#include "gtest/gtest.h"
#include "DatabaseManager.h"

using namespace tomatodb;

class DatabaseManagerTest : public testing::Test {
public:
	DatabaseManager* pDBManager;
};

TEST_F(DatabaseManagerTest, InitFunction) {
	pDBManager = new DatabaseManager();
	pDBManager->Init();
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
}

TEST_F(DatabaseManagerTest, CreateAndDeleteDB) {
	pDBManager = new DatabaseManager();
	pDBManager->Init();
	pDBManager->CreateDatabase("TestDB");
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(1, dblist.size());
	ASSERT_EQ("TestDB", dblist[0]);
	pDBManager->DeleteDatabase("TestDB");
	pAdmin->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
}