#include "stdafx.h"

#include "DBLinkManager.h"
#include "Log.h"

namespace tomatodb
{
	DBLinkManager::DBLinkManager(const Config& config) 
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

	BOOL DBLinkManager::Init(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		m_pAdmin = AdminDB::GetInstance();
		vector<string> linksList;
		if (!m_pAdmin->GetLinksList(linksList))
		{
			Log::SaveLog(SERVER_ERRORFILE, "m_pAdmin->GetLinksList Error!");
			return FALSE;
		}

		for (int i = 0; i < linksList.size(); i++)
		{
			std::string linkDBPathName = EnvFileAPI::GetPathName(dbOptions.linksDBPath, linksList[i]);
			DbLinksMap->insert(std::pair(linksList[i], new DBLinkObject()));
			Status s = m_pDbList[i]->OpenDB(dbOptions);
			m_DbIndexer[dbList[i]] = i;
			m_DbCount++;
		}
		return TRUE;
		__LEAVE_FUNCTION
			return FALSE;
	}

	BOOL DBLinkManager::GetLinksList(vector<string>& database_list)
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
}
