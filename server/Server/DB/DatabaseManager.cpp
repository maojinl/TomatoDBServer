#include "stdafx.h"

#include <filesystem>
#include "DatabaseManager.h"
#include "Log.h"

namespace tomatodb
{
	DatabaseManager* g_pDatabaseManager = nullptr;

	DatabaseManager::DatabaseManager(const Config& config) :
		m_DbCount(0),
		m_pAdmin(nullptr),
		m_pDbList(),
		dbOptions(config),
		threadObjectsPool(nullptr)
	{
		__ENTER_FUNCTION
		threadObjectsPool = DBThreadObjectsPool::GetInstance();
		threadObjectsPool->Init(config.m_WorkerInfo.m_WorkerCount);
		__LEAVE_FUNCTION
	}

	DatabaseManager::~DatabaseManager()
	{
		__ENTER_FUNCTION
		m_DbIndexer.clear();
		for (int i = 0; i < m_DbCount; i++)
		{
			SAFE_DELETE(m_pDbList[i]);
		}
		while (!m_pDbRecycleList.empty())
		{
			UpdateRecycleDBList();
		}
		AdminDB::ReleaseInstance();
		DBThreadObjectsPool::ReleaseInstance();
		__LEAVE_FUNCTION
	}

	VOID DatabaseManager::CleanUp()
	{
		__ENTER_FUNCTION

		__LEAVE_FUNCTION
	}

	BOOL DatabaseManager::Init()
	{
		__ENTER_FUNCTION
		string fullDbName = dbOptions.adminDBPathName;
		m_pAdmin = AdminDB::GetInstance();
		m_pAdmin->Init(fullDbName);
		vector<string> dblist;
		if (!m_pAdmin->GetDatabasesList(dblist))
		{
			Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetDatabasesList Error!");
			return FALSE;
		}

		for (int i = 0; i < dblist.size(); i++)
		{
			std::string dbPathName = EnvFileAPI::GetPathName(dbOptions.userDBPath, dblist[i]);
			m_pDbList[i] = new DatabaseObject(dblist[i], dbPathName);
			m_pDbList[i]->pDb = nullptr;
			Status s = DB::Open(dbOptions.openOptions, fullDbName, &(m_pDbList[i]->pDb));
			m_DbIndexer[dblist[i]] = i;
			m_DbCount++;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::Tick()
	{
		__ENTER_FUNCTION

		UpdateRecycleDBList();
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	DatabaseObject* DatabaseManager::RefDatabaseHandler(string database_name)
	{
		__ENTER_FUNCTION
		DatabaseObject* pDbObj = nullptr;
		AutoLock_T l(m_Lock);
		auto ite = m_DbIndexer.find(database_name);
		if (ite != m_DbIndexer.end())
		{
			pDbObj = m_pDbList[ite->second];
			pDbObj->Ref();
		}
		return pDbObj;
		__LEAVE_FUNCTION
		return nullptr;
	}

	VOID DatabaseManager::UnrefDatabaseHandler(DatabaseObject* pDbObj)
	{
		AutoLock_T l(pDbObj->dblock);
		pDbObj->Unref();
	}

	BOOL DatabaseManager::CreateDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		AutoLock_T l(m_Lock);
		if (m_DbCount < MAX_DATABASE_SIZE)
		{
			string fullDbName = EnvFileAPI::GetPathName(dbOptions.userDBPath, database_name);
			if (m_pAdmin->CreateDatabase(database_name))
			{
				m_pDbList[m_DbCount] = new DatabaseObject(database_name, fullDbName);
				Status s = DB::Open(dbOptions.createOptions, fullDbName, &(m_pDbList[m_DbCount]->pDb));
				if (!s.ok()) {
					Log::SaveLog(SERVER_LOGFILE, "ERROR: Open admin db. Message: %s", s.ToString().c_str());
					return FALSE;
				}
				m_DbIndexer[database_name] = m_DbCount;
				m_DbCount++;
				return TRUE;
			}
		}
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::DeleteDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		AutoLock_T l(m_Lock);
		auto ite = m_DbIndexer.find(database_name);
		if (ite != m_DbIndexer.end())
		{
			if (m_pAdmin->DeleteDatabase(database_name))
			{
				m_pDbRecycleList.push_back(m_pDbList[ite->second]);
				m_pDbList[ite->second] = m_pDbList[m_DbCount - 1];
				m_DbIndexer[m_pDbList[m_DbCount - 1]->database_name] = ite->second;
				m_DbIndexer.erase(ite);
				m_DbCount--;
				return TRUE;
			}
		}
		return FALSE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::InsertIntoDB(const string& database_name, const string& key, const string& val, UINT threadIdx)
	{
		__ENTER_FUNCTION
		DatabaseObject* dbObj = RefDatabaseHandler(database_name);
		if (dbObj != nullptr)
		{
			dbObj->InsertIntoDB(dbOptions.writeOptions, key, val, threadObjectsPool->Get(threadIdx));
			UnrefDatabaseHandler(dbObj);
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::DeleteFromDB(const string& database_name, const string& key, UINT threadIdx)
	{
		__ENTER_FUNCTION
		DatabaseObject* dbObj = RefDatabaseHandler(database_name);
		if (dbObj != nullptr)
		{
			dbObj->DeleteFromDB(dbOptions.writeOptions, key, threadObjectsPool->Get(threadIdx));
			UnrefDatabaseHandler(dbObj);
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::GetFromDB(const string& database_name, const string& key, string* val)
	{
		__ENTER_FUNCTION
		BOOL ret = FALSE;
		DatabaseObject* dbObj = RefDatabaseHandler(database_name);
		if (dbObj != nullptr)
		{
			ret = dbObj->GetFromDB(dbOptions.readOptions, key, val);
			UnrefDatabaseHandler(dbObj);
		}
		return ret;
		__LEAVE_FUNCTION
		return FALSE;
	}

	VOID DatabaseManager::UpdateRecycleDBList()
	{
		AutoLock_T l(m_Lock);
		auto ite = m_pDbRecycleList.begin();
		while (ite != m_pDbRecycleList.end())
		{
			if ((*ite)->ReadyToDestroy())
			{
				delete (*ite)->pDb;
				DestroyDB((*ite)->database_path_name, dbOptions.openOptions);
				ite = m_pDbRecycleList.erase(ite);
			}
			else
			{
				ite++;
			}
		}
	}
}
