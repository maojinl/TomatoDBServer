#include "stdafx.h"
#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include <chrono>

using namespace tomatodb;
#define TEST_THREADS 10
#define MAX_TEST_DATABASE 10
#define MAX_TEST_KEY 10000
#define TEST_ROUNDS 10000

class DBManagerTestThread : public Thread
{
public:
	int TestType; //0 create delete database; 1 insert or delete Data; 2 get data; 3 Deamon thread;
	int TestRound;
	bool Active;
	DatabaseManager* pDBMan;
	RandGen rand;
	int Id;
	const string DBNamePrefix = "TestDB";
	int FailedCount;

	static vector<bool> DBNameIndex;
	static MyLock* pLock;
	DBManagerTestThread(int id, int type, int round, DatabaseManager* pdbman)
		:Id(id), TestType(type), TestRound(round), pDBMan(pdbman), rand(1000 + id), FailedCount(0)
	{
		Active = true;
	};

	virtual void run()
	{
		switch (TestType)
		{
		case 0:
			CreateOrDeleteDB();
			break;
		case 1:
			InsertOrDeleteData();
			break;
		case 2:
			GetKey();
			break;
		case 3:
			DaemonProcess();
			break;
		default:
			break;
		};
		Active = false;
		return;
	};

	void CreateOrDeleteDB()
	{
		bool ret;
		for (int i = 0; i < TestRound; i++)
		{
			int idx = rand.GetRand(0, MAX_TEST_DATABASE - 1);
			string dbname = DBNamePrefix + std::to_string(idx);
			if (DBNameIndex[idx])
			{
				ret = pDBMan->DeleteDatabase(dbname);
			}
			else
			{
				ret = pDBMan->CreateDatabase(dbname);
			}
			pLock->Lock();
			DBNameIndex[idx] = !DBNameIndex[idx];
			pLock->Unlock();

			if (!ret)
			{
				FailedCount++;
			}
		}

		return;
	};

	void InsertOrDeleteData()
	{
		vector<string> dblist;
		string dbname;
		string key;
		string value = "value";
		bool ret;
		for (int i = 0; i < TestRound; i++)
		{
			pDBMan->GetDatabasesList(dblist);
			int n = rand.GetRand(0, dblist.size() - 1);
			dbname = dblist[n];
			n = rand.GetRand(0, MAX_TEST_KEY);
			key = std::to_string(n);
			n = rand.GetRand(0, 4);
			if (n == 0)
			{
				ret = pDBMan->DeleteFromDB(dbname, key, Id);
			}
			else
			{
				ret = pDBMan->InsertIntoDB(dbname, key, value, Id);
			}
			if (!ret)
			{
				FailedCount++;
			}
		}
		return;
	};

	void GetKey()
	{
		vector<string> dblist;
		string dbname;
		string key;
		string value = "value";
		bool ret;
		for (int i = 0; i < TestRound; i++)
		{
			pDBMan->GetDatabasesList(dblist);
			int n = rand.GetRand(0, dblist.size() - 1);
			dbname = dblist[n];
			n = rand.GetRand(0, MAX_TEST_KEY);
			key = std::to_string(n);
			ret = pDBMan->GetFromDB(dbname, key, &value);
			if (!ret)
			{
				FailedCount++;
			}
		}
		return;
	};

	void DaemonProcess()
	{
		while (Active)
		{
			MySleep(1000);
			pDBMan->Tick();
		}
	};

};

class DatabaseManagerTest : public testing::Test {
public:
	DatabaseManager* pDBManager;
	DatabaseManagerTest()
	{

	}
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