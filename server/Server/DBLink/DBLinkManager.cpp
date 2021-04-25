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
		if (ite == dbLinksTable.end())
		{
			return FALSE;
		}
		else
		{
			dblinks = ite->second;
		}

		DBLinkObjectsTable::const_iterator iteLinkObj = dblinks->find(rhsdbname);
		if (iteLinkObj != dblinks->end())
		{
			iteLinkObj->second->status = DatabaseObjectStatus::StatusDeletePending;
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
		}

		__LEAVE_FUNCTION
		return FALSE;
	}
}
