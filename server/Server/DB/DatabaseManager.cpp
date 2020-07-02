#include "stdafx.h"

#include <filesystem>
#include "DatabaseManager.h"
#include "Log.h"

namespace tomatodb
{
	DatabaseManager* g_pDatabaseManager = NULL;

	DatabaseManager::DatabaseManager() :
		m_DbCount(0),
		m_pAdmin(nullptr),
		m_pDbList()
	{
		__ENTER_FUNCTION		

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
		string fullDbName = DatabaseManager::GetDBPathName(g_Config.m_ConfigInfo.m_AdminDBPath, AdminDB::ADMIN_DATABASE_NAME);
		m_pAdmin = AdminDB::GetInstance();
		m_pAdmin->Init(fullDbName);
		vector<string> dblist;
		if (!m_pAdmin->GetDatabasesList(dblist))
		{
			Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetDatabasesList Error!");
			return FALSE;
		}

		Options opts;
		Env* env = opts.env;
		opts.create_if_missing = true;
		for (int i = 0; i < dblist.size(); i++)
		{
			std::string dbPathName = DatabaseManager::GetDBPathName(g_Config.m_ConfigInfo.m_DataPath, dblist[i]);
			m_pDbList[i] = new DatabaseObject(dblist[i], dbPathName);
			m_pDbList[i]->pDb = nullptr;
			Status s = DB::Open(opts, fullDbName, &(m_pDbList[i]->pDb));
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

	BOOL DatabaseManager::CreateDatabase(string database_name)
	{
		__ENTER_FUNCTION
		AutoLock_T l(m_Lock);
		if (m_DbCount < MAX_DATABASE_SIZE)
		{
			string fullDbName = DatabaseManager::GetDBPathName(g_Config.m_ConfigInfo.m_DataPath, database_name);
			if (m_pAdmin->CreateDatabase(database_name))
			{
				m_pDbList[m_DbCount] = new DatabaseObject(database_name, fullDbName);
				Options opts;
				Env* env = opts.env;
				opts.create_if_missing = true;
				Status s = DB::Open(opts, fullDbName, &(m_pDbList[m_DbCount]->pDb));
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

	BOOL DatabaseManager::DeleteDatabase(string database_name)
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

	VOID DatabaseManager::UpdateRecycleDBList()
	{
		AutoLock_T l(m_Lock);
		auto ite = m_pDbRecycleList.begin();
		while (ite != m_pDbRecycleList.end())
		{
			if ((*ite)->ReadyToDestroy())
			{
				delete (*ite)->pDb;
				DestroyDB((*ite)->database_path_name, Options());
				ite = m_pDbRecycleList.erase(ite);
			}
			else
			{
				ite++;
			}
		}
	}
}
