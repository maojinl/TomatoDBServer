#include "stdafx.h"

#include <iostream>

#include "gtest/gtest.h"
#include "DatabaseManager.h"
#include "unittestutils.h"
	
using namespace tomatodb;
#define TEST_THREADS 10
#define MAX_TEST_DATABASE 20
#define MAX_TEST_KEY 10000
#define TEST_ROUNDS 1000

class DBManagerTestThread : public Thread
{
public:
	int TestType; //0 create delete database; 1 insert or delete Data; 2 get data; 3 Deamon thread;
	int TestRound;
	bool Active;
	DatabaseManager* pDBMan;
	RandGen rand;
	int Id;
	int FailedCount;

	static vector<bool> DBNameIndex;
	static MyLock* pLock;
	static string DBNamePrefix;

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
		bool ret = false;
		for (int i = 0; i < TestRound; i++)
		{
			
			int idx = rand.GetRand(0, MAX_TEST_DATABASE - 1);
			string dbname = DBNamePrefix + std::to_string(idx);
			if (DBNameIndex[idx])
			{
				if (idx > 3)
				{
					ret = pDBMan->DeleteDatabase(dbname);
				}
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
		bool ret = false;
		for (int i = 0; i < TestRound; i++)
		{
			pDBMan->GetDatabasesList(dblist);
			if (!dblist.empty())
			{
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
			else
			{
				i--;
			}
		}
		return;
	};

	void GetKey()
	{
		vector<string> dblist;
		string dbname;
		string key;
		string value = "";
		bool ret = false;
		for (int i = 0; i < TestRound; i++)
		{
			pDBMan->GetDatabasesList(dblist);
			int n = rand.GetRand(0, dblist.size() - 1);
			if (!dblist.empty())
			{
				dbname = dblist[n];
				n = rand.GetRand(0, MAX_TEST_KEY);
				key = std::to_string(n);
				ret = pDBMan->GetFromDB(dbname, key, &value);
				if (!ret)
				{
					FailedCount++;
				}
			}
			else
			{
				i--;
			}
		}
		return;
	};

	void DaemonProcess()
	{
		while (Active)
		{
			MySleep(10);
			pDBMan->HeartBeat();
		}
		Active = false;
	};

};

vector<bool> DBManagerTestThread::DBNameIndex;
MyLock* DBManagerTestThread::pLock;
string DBManagerTestThread::DBNamePrefix = "TestDB";

class DatabaseManagerTest : public testing::Test {
public:
	DatabaseManager* pDBManager;
	DatabaseManagerTest()
	{
		UpdateUnitTestPath(g_Config);
		AdminDB::ReleaseInstance();
		g_Config.m_WorkerInfo.m_WorkerCount = TEST_THREADS;
	}

	~DatabaseManagerTest()
	{
		SAFE_DELETE(pDBManager);
		DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
			, Options());
	}
};

TEST_F(DatabaseManagerTest, InitFunction) {
	pDBManager = new DatabaseManager(g_Config);
	pDBManager->Init();
	
	AdminDB* pAdmin = AdminDB::GetInstance();
	vector<string> dblist;
	pDBManager->GetDatabasesList(dblist);
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
	pDBManager->GetDatabasesList(dblist);
	ASSERT_EQ(1, dblist.size());
	ASSERT_EQ("TestDB", dblist[0]);
	pDBManager->DeleteDatabase("TestDB");
	dblist.clear();
	pDBManager->GetDatabasesList(dblist);
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
	pDBManager->GetDatabasesList(dblist);
	ASSERT_EQ(true, dblist.empty());
	SAFE_DELETE(pDBManager);
	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
		, Options());
}
//
//TEST_F(DatabaseManagerTest, MultiThread) {
//	pDBManager = new DatabaseManager(g_Config);
//	pDBManager->Init();
//	
//	DBManagerTestThread::pLock = new MyLock();
//
//	for (int i = 0; i < MAX_TEST_DATABASE; i++)
//	{
//		DBManagerTestThread::DBNameIndex.push_back(false);
//	}
//
//	DBManagerTestThread* testThread[TEST_THREADS];
//	for (int i = 0; i < TEST_THREADS; i++)
//	{
//		if (i < TEST_THREADS / 5)
//		{
//			testThread[i] = new DBManagerTestThread(i, 0, TEST_ROUNDS, pDBManager);
//		}
//		else if (i < TEST_THREADS / 3 * 2)
//		{
//			testThread[i] = new DBManagerTestThread(i, 1, TEST_ROUNDS, pDBManager);
//		}
//		else if (i < TEST_THREADS - 1)
//		{
//			testThread[i] = new DBManagerTestThread(i, 2, TEST_ROUNDS, pDBManager);
//		}
//		else
//		{
//			testThread[i] = new DBManagerTestThread(i, 3, TEST_ROUNDS, pDBManager);
//		}
//	}
//
//	for (int i = 0; i < TEST_THREADS; i++)
//	{
//		testThread[i]->start();
//	}
//
//	while (true)
//	{
//		MySleep(2000);
//		bool allDone = true;
//		for (int i = 0; i < TEST_THREADS - 1; i++)
//		{
//			if (testThread[i]->Active)
//			{
//				allDone = false;
//				break;
//			}
//		}
//		if (allDone)
//		{
//			testThread[TEST_THREADS - 1]->Active = false;
//			MySleep(2000);
//			break;
//		}
//	}
//
//	for (int i = 0; i < TEST_THREADS - 1; i++)
//	{
//		//EXPECT_TRUE(false) << "Failed Count is " << testThread[i]->FailedCount;
//		std::cout << "Thread "<< i << "Failed Count is "<< testThread[i]->FailedCount << std::endl;
//		SAFE_DELETE(testThread[i]);
//	}
//	SAFE_DELETE(testThread[TEST_THREADS - 1]);
//	SAFE_DELETE(pDBManager);
//
//	for (int i = 0; i < MAX_TEST_DATABASE; i++)
//	{
//		string dbname = DBManagerTestThread::DBNamePrefix + std::to_string(i);
//		DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_DataPath, dbname)
//			, Options());
//	}	
//	DestroyDB(EnvFileAPI::GetPathName(g_Config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME)
//		, Options());
//}