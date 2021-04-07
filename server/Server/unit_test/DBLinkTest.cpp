#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include "StringArrayTable.h"
#include "unittestutils.h"
	
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

TEST_F(DBLinkTest, StringArrayTable_1Layer) {
	vector<string> vs1{"testdb1", "testdb2", "testdb3"};
	StringArrayTable sat;
	sat.InitWithArrays(&vs1);
	ASSERT_EQ(1, sat.GetLayer());
	ASSERT_EQ(161, sat.GetLength());
	vector<string> keysToFind;
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(1, sat2.GetLayer());
	ASSERT_EQ(161, sat2.GetLength());
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(3, result.size());
}

TEST_F(DBLinkTest, StringArrayTable_2Layers) {
	vector<string> vs1{ "testdb1", "testdb2", "testdb3" };
	vector<vector<string>> vvs1
	{
		{ "testdb1_1", "testdb1_2", "testdb1_3" },
		{ "testdb2_1", "testdb2_2" },
		{ "testdb3_1", "testdb3_2", "testdb3_3", "testdb3_4" },
	};

	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1);
	ASSERT_EQ(2, sat.GetLayer());
	ASSERT_EQ(275, sat.GetLength());
	vector<string> keysToFind{"testdb2"};
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(2, sat2.GetLayer());
	ASSERT_EQ(275, sat2.GetLength());
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());
	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());
}


TEST_F(DBLinkTest, StringArrayTable_3Layers) {
	vector<string> vs1{ "testdb1", "testdb2", "testdb3" };
	vector<vector<string>> vvs1
	{
		{ "testdb1_1", "testdb1_2", "testdb1_3" },
		{ "testdb2_1", "testdb2_2" },
		{ "testdb3_1", "testdb3_2", "testdb3_3", "testdb3_4" },
	};

	vector<vector<vector<string>>> vvvs1
	{
		{
			{ "testdb1_1_1", "testdb1_1_2", "testdb1_1_3" },
			{ "testdb1_2_1", "testdb1_2_2", "testdb1_2_3", "testdb1_2_4", "testdb1_2_5" },
			{ "testdb1_3_1", "testdb1_3_2", "testdb1_3_3" },
		},
		{
			{ "testdb2_1_1", "testdb2_1_2", "testdb2_1_3", "testdb2_1_4", "testdb2_1_5" },
			{ "testdb2_2_1", "testdb2_2_2", "testdb2_2_3" },
		},
		{
			{ "testdb3_1_1", "testdb3_1_2", "testdb3_1_3", "testdb3_1_4", "testdb3_1_5"},
			{ "testdb3_2_1", "testdb3_2_2", "testdb3_2_3", "testdb3_2_4" },
			{ "testdb3_3_1", "testdb3_3_2", "testdb3_3_3" },
			{ "testdb3_4_1", "testdb3_4_2"  },
		},
	};

	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1, &vvvs1);
	ASSERT_EQ(3, sat.GetLayer());

	vector<string> keysToFind{ "testdb2", "testdb2_1" };
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(3, sat2.GetLayer());

	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());
	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	keysToFind.push_back("testdb3_4");
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());
}


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
