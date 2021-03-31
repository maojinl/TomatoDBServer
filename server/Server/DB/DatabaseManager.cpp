#include "stdafx.h"

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
		while (!m_pDbRecycleList.empty())
		{
			UpdateRecycleDBList();
			MySleep(1000);
		}

		for (int i = 0; i < m_DbCount; i++)
		{
			SAFE_DELETE(m_pDbList[i]);
		}
		m_DbIndexer.clear();

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
		vector<string> dbList;
		if (!m_pAdmin->GetDatabasesList(dbList))
		{
			Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetDatabasesList Error!");
			return FALSE;
		}

		for (int i = 0; i < dbList.size(); i++)
		{
			std::string dbPathName = EnvFileAPI::GetPathName(dbOptions.userDBPath, dbList[i]);
			m_pDbList[i] = new DatabaseObject(dbList[i], dbPathName);
			Status s = m_pDbList[i]->OpenDB(dbOptions);
			m_DbIndexer[dbList[i]] = i;
			m_DbCount++;
		}
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
			if (pDbObj->IsNormal())
			{
				pDbObj->Ref();
				return pDbObj;
			}
		}
		__LEAVE_FUNCTION
		return nullptr;
	}

	VOID DatabaseManager::UnrefDatabaseHandler(DatabaseObject* pDbObj)
	{
		pDbObj->Unref();
	}

	BOOL DatabaseManager::CreateDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		AutoLock_T l(m_Lock);
		auto ite = m_DbIndexer.find(database_name);
		if (ite != m_DbIndexer.end())
		{
			return FALSE;
		}
		if (m_DbCount < MAX_DATABASE_SIZE)
		{
			string fullDbName = EnvFileAPI::GetPathName(dbOptions.userDBPath, database_name);
			if (m_pAdmin->CreateDatabase(database_name))
			{
				DatabaseObject* pDbObj = new DatabaseObject(database_name, fullDbName);
				Status s = pDbObj->CreateDB(dbOptions);
				if (!s.ok()) {
					m_pAdmin->DeleteDatabase(database_name);
					pDbObj->DestroyDB(dbOptions.openOptions);
					Log::SaveLog(SERVER_LOGFILE, "ERROR: Create database in admin db. Message: %s", s.ToString().c_str());
					return FALSE;
				}
				m_pDbList[m_DbCount] = pDbObj;
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
			if (m_pDbList[ite->second]->IsNormal())
			{
				m_pDbRecycleList.push_back(m_pDbList[ite->second]);
				m_pDbList[ite->second]->status = DatabaseStatusDeletePending;
			}
			return TRUE;
		}
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::InsertIntoDB(const string& database_name, const string& key, const string& val, UINT threadIdx)
	{
		__ENTER_FUNCTION
		DatabaseObject* dbObj = RefDatabaseHandler(database_name);
		if (dbObj != nullptr)
		{
			dbObj->InsertIntoDB(dbOptions.writeOptions, key, val, threadObjectsPool->Get(threadIdx), threadIdx);
			UnrefDatabaseHandler(dbObj);
			return TRUE;
		}
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::DeleteFromDB(const string& database_name, const string& key, UINT threadIdx)
	{
		__ENTER_FUNCTION
		DatabaseObject* dbObj = RefDatabaseHandler(database_name);
		if (dbObj != nullptr)
		{
			dbObj->DeleteFromDB(dbOptions.writeOptions, key, threadObjectsPool->Get(threadIdx), threadIdx);
			UnrefDatabaseHandler(dbObj);
			return TRUE;
		}
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

	BOOL DatabaseManager::GetDatabasesList(vector<string>& database_list)
	{
		__ENTER_FUNCTION
		database_list.clear();
		m_DbListLock.ReadLock();
		for (int i = 0; i < m_DbCount; i++)
		{
			if (m_pDbList[i]->IsNormal())
			{
				database_list.push_back(m_pDbList[i]->database_name);
			}
		}
		m_DbListLock.ReadUnlock();
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DatabaseManager::HeartBeat()
	{
		__ENTER_FUNCTION
		UpdateRecycleDBList();
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	VOID DatabaseManager::UpdateRecycleDBList()
	{
		AutoLock_T l(m_Lock);
		auto ite = m_pDbRecycleList.begin();
		while (ite != m_pDbRecycleList.end()) {
			DatabaseObject* pDbObj = (*ite);
			if (pDbObj->ReadyToDestroy()) {
				if (DeleteDatabaseCore(pDbObj)) {
					ite = m_pDbRecycleList.erase(ite);
					delete pDbObj;
					continue;
				}
			}
			ite++;
		}	
	}

	BOOL DatabaseManager::DeleteDatabaseCore(DatabaseObject* pDbObj)
	{
		if (m_pAdmin->DeleteDatabase(pDbObj->database_name))
		{
			Status s = pDbObj->DestroyDB(dbOptions.openOptions);
			if (!s.ok()) {
				m_pAdmin->CreateDatabase(pDbObj->database_name);
				Log::SaveLog(SERVER_LOGFILE, "ERROR: DeleteDatabaseCore. Message: %s", s.ToString().c_str());
				return FALSE;
			}

			auto ite = m_DbIndexer.find(pDbObj->database_name);
			if (ite != m_DbIndexer.end() && m_pDbList[ite->second]->IsDeletePending())
			{
				m_DbListLock.WriteLock();
				m_DbCount--;
				m_pDbList[ite->second] = m_pDbList[m_DbCount];
				m_DbIndexer[m_pDbList[m_DbCount]->database_name] = ite->second;
				m_pDbList[m_DbCount] = nullptr;
				m_DbIndexer.erase(ite);
				m_DbListLock.WriteUnlock();
			}
			return TRUE;
		}
		else {
			Log::SaveLog(SERVER_LOGFILE, "ERROR: Delete Database from Admin DB error!");
			return FALSE;
		}
	}
}
