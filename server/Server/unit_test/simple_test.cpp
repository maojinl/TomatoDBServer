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
}