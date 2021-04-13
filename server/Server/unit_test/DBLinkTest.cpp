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
	StringArrayTable sat;
	sat.InitWithArrays(&vs1);
	ASSERT_EQ(1, sat.GetLayer());
	ASSERT_EQ(33, sat.GetLength());
	vector<string> keysToFind;
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(1, sat2.GetLayer());
	ASSERT_EQ(33, sat2.GetLength());
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(3, result.size());
}

TEST_F(DBLinkTest, StringArrayTable_2Layers) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1);
	ASSERT_EQ(2, sat.GetLayer());
	ASSERT_EQ(147, sat.GetLength());
	vector<string> keysToFind{"testdb2"};
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(2, sat2.GetLayer());
	ASSERT_EQ(147, sat2.GetLength());
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());
	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());
}


TEST_F(DBLinkTest, StringArrayTable_3Layers) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1, &vvvs1);
	ASSERT_EQ(3, sat.GetLayer());

	vector<string> keysToFind{ "testdb2", "testdb2_1" };
	vector<string> result;
	StringArrayTable sat2;
	sat2.InitWithData(sat.GetLength(), sat.GetData());
	ASSERT_EQ(3, sat2.GetLayer());

	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(5, result.size());
	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	keysToFind.push_back("testdb3_4");
	sat2.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());
}

TEST_F(DBLinkTest, WriteStringArrayTable_1Layer) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1);

	vector<string> keysToFind;
	vector<string> result;
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(3, result.size());

	vector<string> vsWrite{ "testdb4", "testdb5", "testdb6" };
	sat.WriteArrayAtCurrentNode(vsWrite);
	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(3, result.size());

	vsWrite.push_back("testdb7");
	sat.WriteArrayAtCurrentNode(vsWrite);
	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());

	ASSERT_EQ(41, sat.GetLength());
}

TEST_F(DBLinkTest, WriteStringArrayTable_2Layer) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1);

	vector<string> keysToFind {"testdb2"};
	vector<string> result;
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());

	vector<string> vsWrite{ "testdb4", "testdb5", "testdb6", "testdb5", "testdb6" };
	sat.WriteArrayAtCurrentNode(vsWrite);
	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(5, result.size());

	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());
}

TEST_F(DBLinkTest, WriteStringArrayTable_3Layer) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1, &vvvs1);

	vector<string> keysToFind{ "testdb3", "testdb3_2" };
	vector<string> result;
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(4, result.size());

	vector<string> vsWrite{ "testdb4", "testdb5", "testdb6", "testdb7", "testdb8" };
	sat.WriteArrayAtCurrentNode(vsWrite);
	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(5, result.size());

	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	keysToFind.push_back("testdb3_4");
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());
}

TEST_F(DBLinkTest, WriteEmtyStringArrayTable_3Layer) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1, &vvs1, &vvvs1);

	vector<string> keysToFind{ "testdb2", "testdb2_2" };
	vector<string> result;
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(3, result.size());

	vector<string> vsWrite{};
	sat.WriteArrayAtCurrentNode(vsWrite);

	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(0, result.size());

	keysToFind.pop_back();
	keysToFind.push_back("testdb2_1");
	result.clear();
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(5, result.size());
	sat.WriteArrayAtCurrentNode(vsWrite);

	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb3");
	keysToFind.push_back("testdb3_4");
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(2, result.size());

	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb1");
	keysToFind.push_back("testdb1_2");
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(5, result.size());
	sat.WriteArrayAtCurrentNode(vsWrite);
	keysToFind.clear();
	result.clear();
	keysToFind.push_back("testdb2");
	keysToFind.push_back("testdb2_1");
	sat.GetArrayAtKeys(keysToFind, result);
	ASSERT_EQ(0, result.size());
}

TEST_F(DBLinkTest, AppendStringArrayTable_1Layer) {
	StringArrayTable sat;
	sat.InitWithArrays(&vs1);
	ASSERT_EQ(1, sat.GetLayer());
	ASSERT_EQ(33, sat.GetLength());
	vector<string> dataToAppend {"test4", "test5", "test6" };

	StringArrayTable sat2;
	sat2.InitWithArrays(&dataToAppend);
	sat.Append(sat2);
	ASSERT_EQ(1, sat.GetLayer());
	ASSERT_EQ(51, sat.GetLength());
	ASSERT_EQ(6, leveldb::DecodeFixed32(&sat.GetData()[1]));
	ASSERT_EQ(50, leveldb::DecodeFixed32(&sat.GetData()[5]));
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

TEST_F(DBLinkTest, JsonWriterTest) {
	JsonAdminDBWriter writer;
	int runCount = 0;
	string dataStr = writer.NewLinkList();
	while (runCount < 100)
	{
		runCount++;
		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.AddLinkIntoList(dataStr, dbname, linkname);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.RemoveLinkFromList(dataStr, dbname, linkname);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.AddLinkIntoList(dataStr, dbname, linkname);
			}
		}
		for (int i = 9; i >= 0; i--)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 19; j >= 0; j--)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.RemoveLinkFromList(dataStr, dbname, linkname);
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		string dbname = "testdb_" + std::to_string(i);
		for (int j = 0; j < 20; j++)
		{
			string linkname = dbname + "_" + std::to_string(j);
			writer.AddLinkIntoList(dataStr, dbname, linkname);
		}
	}

	vector<string> vs;
	writer.ReadLinkList(dataStr, "testdb_5", vs);
	ASSERT_EQ(20, vs.size());
	ASSERT_EQ("testdb_5_5", vs[5]);
}

TEST_F(DBLinkTest, ArrayTableWriterTest) {
	ArrayTableAdminDBWriter writer;
	int runCount = 0;
	string dataStr = writer.NewLinkList();
	while (runCount < 100)
	{
		runCount++;
		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.AddLinkIntoList(dataStr, dbname, linkname);
			}
		}
		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.RemoveLinkFromList(dataStr, dbname, linkname);
			}
		}

		for (int i = 0; i < 10; i++)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 0; j < 20; j++)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.AddLinkIntoList(dataStr, dbname, linkname);
			}
		}
		for (int i = 9; i >= 0; i--)
		{
			string dbname = "testdb_" + std::to_string(i);
			for (int j = 19; j >= 0; j--)
			{
				string linkname = dbname + "_" + std::to_string(j);
				writer.RemoveLinkFromList(dataStr, dbname, linkname);
			}
		}
	}
	for (int i = 0; i < 10; i++)
	{
		string dbname = "testdb_" + std::to_string(i);
		for (int j = 0; j < 20; j++)
		{
			string linkname = dbname + "_" + std::to_string(j);
			writer.AddLinkIntoList(dataStr, dbname, linkname);
		}
	}

	vector<string> vs;
	writer.ReadLinkList(dataStr, "testdb_5", vs);
	ASSERT_EQ(20, vs.size());
	ASSERT_EQ("testdb_5_5", vs[5]);
}