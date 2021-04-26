#include "stdafx.h"

#include "DBLinkManager.h"
#include "Log.h"

namespace tomatodb
{
	DBLinkManager::DBLinkManager(const DatabaseOptions& options):
		dbOptions(options)
	{
		__ENTER_FUNCTION

			__LEAVE_FUNCTION
	}

	DBLinkManager::~DBLinkManager()
	{
		__ENTER_FUNCTION

		__LEAVE_FUNCTION
	}

	VOID DBLinkManager::CleanUp()
	{
		__ENTER_FUNCTION
		__LEAVE_FUNCTION
	}

	BOOL DBLinkManager::Init()
	{
		__ENTER_FUNCTION
		m_pAdmin = AdminDB::GetInstance();
		vector<string> rhsTableList;
		if (!m_pAdmin->GetLinksList(rhsTableList))
		{
			Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetLinksList Error!");
			return FALSE;
		}

		vector<string> linksForDB;
		for (int i = 0; i < rhsTableList.size(); i++)
		{
			if (!m_pAdmin->GetDBLinksList(rhsTableList[i], linksForDB))
			{
				Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetDBLinksList Error!");
				return FALSE;
			}
			unordered_map<string, DBLinkObject*>* pDBLinksMap = new unordered_map<string, DBLinkObject*>();
			for (int j = 0; j < linksForDB.size(); j++)
			{
				std::string linkDBPathName = EnvFileAPI::GetPathName(dbOptions.linksDBPath, linksForDB[i]);
				DBLinkObject* pDBLink = new DBLinkObject(rhsTableList[i], linkDBPathName);
				if (pDBLink->OpenLink(dbOptions))
				{
					pDBLinksMap->insert(std::pair<string, DBLinkObject*>(rhsTableList[i], pDBLink));
				}
				else
				{
					Log::SaveLog(SERVER_ERRORFILE, "pDBLink->OpenLink Error!");
					return false;
				}
			}
			dbLinksTable.insert(std::pair<string, DBLinkObjectsTable*>(rhsTableList[i], pDBLinksMap));
		}
		return TRUE;
		__LEAVE_FUNCTION
			return FALSE;
	}

	BOOL DBLinkManager::GetLinksList(const string& dbname, vector<string>& values)
	{
		__ENTER_FUNCTION
		unordered_map<string, DBLinkObjectsTable*>::const_iterator ite = dbLinksTable.find(dbname);
		if (ite != dbLinksTable.end())
		{
			DBLinkObjectsTable* p = ite->second;
			for (DBLinkObjectsTable::const_iterator iteLinkObj = p->begin(); iteLinkObj != p->end(); iteLinkObj++)
			{
				values.push_back(iteLinkObj->first);
			}
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	DBLinkObject* DBLinkManager::RefLinkHandler(const string& dbname, const string& rhsdbname)
	{
		__ENTER_FUNCTION
		DBLinkObject* pDbObj = nullptr;
		AutoLock_T l(m_Lock);
		unordered_map<string, DBLinkObjectsTable*>::const_iterator ite = dbLinksTable.find(dbname);
		DBLinkObjectsTable* dblinks;
		if (ite != dbLinksTable.end())
		{
			dblinks = ite->second;

			DBLinkObjectsTable::const_iterator iteLink = dblinks->find(rhsdbname);
			if (iteLink != dblinks->end())
			{
				iteLink->second->Ref();
				return iteLink->second;
			}
		}
		__LEAVE_FUNCTION
		return nullptr;
	}

	VOID DBLinkManager::UnrefLinkHandler(DBLinkObject* pLinkObj)
	{
		pLinkObj->Unref();
	}

	BOOL DBLinkManager::CreateLink(const string& dbname, const string& rhsdbname)
	{
		__ENTER_FUNCTION
		unordered_map<string, DBLinkObjectsTable*>::const_iterator ite = dbLinksTable.find(dbname);
		DBLinkObjectsTable* dblinks;
		if (ite == dbLinksTable.end())
		{
			dblinks = new DBLinkObjectsTable();
			dbLinksTable.insert(std::pair<string, DBLinkObjectsTable*>(dbname, dblinks));
		}
		else
		{
			dblinks = ite->second;
		}

		DBLinkObjectsTable::const_iterator iteLinkObj = dblinks->find(rhsdbname);
		if (iteLinkObj == dblinks->end())
		{
			if (m_pAdmin->AddLink(dbname, rhsdbname))
			{
				DBLinkObject* linkObj = new DBLinkObject(dbname, rhsdbname);
				if (!linkObj->CreateLink(dbOptions))
				{
					m_pAdmin->RemoveLink(dbname, rhsdbname);
				}
				dblinks->insert(std::pair<string, DBLinkObject*>(rhsdbname, linkObj));
				return TRUE;
			}
			else
			{
				Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->AddLink Error!");
			}
		}

		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkManager::DeleteLink(const string& dbname, const string& rhsdbname)
	{
		__ENTER_FUNCTION
		unordered_map<string, DBLinkObjectsTable*>::const_iterator ite = dbLinksTable.find(dbname);
		DBLinkObjectsTable* dblinks;
		if (ite != dbLinksTable.end())
		{
			dblinks = ite->second;

			DBLinkObjectsTable::const_iterator iteLink = dblinks->find(rhsdbname);
			if (iteLink != dblinks->end())
			{
				iteLink->second->status = DatabaseObjectStatus::StatusDeletePending;
				linkRecycleList.push_back(iteLink->second);
				return TRUE;
			}
		}

			/*if (m_pAdmin->RemoveLink(dbname, rhsdbname))
			{
				DBLinkObject* linkObj = new DBLinkObject(dbname, rhsdbname);
				if (!linkObj->CreateLink(dbOptions))
				{
					m_pAdmin->AddLink(dbname, rhsdbname);
				}
				dblinks->insert(std::pair<string, DBLinkObject*>(rhsdbname, linkObj));
				return TRUE;
			}
			else
			{
				Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->AddLink Error!");
			}*/

		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkManager::UpdateKeysIntoLinks(const string& dbname, const string& rhsdbname, const string& id1, const vector<string>& id2_list)
	{
		__ENTER_FUNCTION
		DBLinkObject* linkObj = RefLinkHandler(dbname, rhsdbname);
		if (linkObj != nullptr)
		{
			linkObj->UpdateKeysIntoLinks(id1, id2_list);
			UnrefLinkHandler(linkObj);
			return TRUE;
		}
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkManager::DeleteKeysFromLinks(const string& dbname, const string& rhsdbname, const string& id1)
	{
		__ENTER_FUNCTION
		DBLinkObject* linkObj = RefLinkHandler(dbname, rhsdbname);
		if (linkObj != nullptr)
		{
			linkObj->DeleteKeysFromLinks(id1);
			UnrefLinkHandler(linkObj);
			return TRUE;
		}
		__LEAVE_FUNCTION
		return FALSE;
	}

	VOID DBLinkManager::UpdateRecycleLinkList()
	{
		AutoLock_T l(m_Lock);
		auto ite = linkRecycleList.begin();
		while (ite != linkRecycleList.end()) {
			DBLinkObject* pLinkObj = (*ite);
			if (pLinkObj->NotInUse()) {
				if (DeleteLinkCore(pLinkObj)) {
					ite = linkRecycleList.erase(ite);
					delete pLinkObj;
					continue;
				}
			}
			ite++;
		}
	}

	BOOL DBLinkManager::DeletLinkCore(DBLinkObject* pLinkObj)
	{
		if (m_pAdmin->DeleteDatabase(pLinkObj->database_name))
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

	BOOL DBLinkManager::HeartBeat()
	{
		__ENTER_FUNCTION
		UpdateRecycleLinkList();
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}
}
