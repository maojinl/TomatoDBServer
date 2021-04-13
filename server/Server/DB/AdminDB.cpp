#include "stdafx.h"

#include "AdminDB.h"
#include "Log.h"
#include "json.hpp"
#include "Config.h"
#include "leveldb/env.h"

namespace tomatodb
{
	const string AdminDB::DATABASE_NAME_KEY = "DATABASE_NAME_KEY";
	const string AdminDB::DATABASE_LINK_KEY = "DATABASE_LINK_KEY";
	AdminDB* AdminDB::m_pAdminDBObj;

	AdminDB::AdminDB()
		:m_pDb(nullptr)
	{
		__ENTER_FUNCTION
		m_pWriter = new ArrayTableAdminDBWriter();
		CleanUp();

		__LEAVE_FUNCTION
	}


	AdminDB::~AdminDB()
	{
		__ENTER_FUNCTION

		SAFE_DELETE(m_pDb) ;

		__LEAVE_FUNCTION
	}

	VOID AdminDB::CleanUp()
	{
		__ENTER_FUNCTION

		__LEAVE_FUNCTION
	}

	BOOL AdminDB::Init(string dbname)
	{
		__ENTER_FUNCTION
		if (m_pDb == nullptr)
		{
			Options opts;
			Env* env = opts.env;
			bool needInit = false;
			if (!env->FileExists(dbname))
			{
				needInit = true;
			}
			opts.create_if_missing = true;
			Status s = DB::Open(opts, dbname, &m_pDb);
			if (!s.ok()) {
				Log::SaveLog(SERVER_LOGFILE, "ERROR: Open admin db. Message: %s", s.ToString().c_str());
			}
			if (needInit) {
				InitializeAdminDB();
			}
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::InitializeAdminDB()
	{ 
		__ENTER_FUNCTION
		string dblist = m_pWriter->NewDBList();
		string linklist = m_pWriter->NewLinkList();
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, dblist);
		m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, linklist);
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::GetDatabasesList(vector<string>& database_list)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		m_pWriter->ReadDBList(databases_string, database_list);
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::CreateDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		if (m_pWriter->AddDBIntoList(databases_string, database_name))
		{
			m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, databases_string);
		}
		else
		{
			return FALSE;
		}

		return TRUE;
		__LEAVE_FUNCTION

		return FALSE;
	}

	BOOL AdminDB::DeleteDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		if (m_pWriter->RemoveDBFromList(databases_string, database_name))
		{
			m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, databases_string);
		}
		else
		{
			return FALSE;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::GetLinksList(const string& dbname, vector<string>& link_list)
	{
		__ENTER_FUNCTION
		std::string links_string;
		m_pDb->Get(ReadOptions(), DATABASE_LINK_KEY, &links_string);
		m_pWriter->ReadLinkList(links_string, dbname, link_list);
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::AddLink(const string& dbname, const string& rhs_dbname)
	{
		__ENTER_FUNCTION
		std::string links_string;
		m_pDb->Get(ReadOptions(), DATABASE_LINK_KEY, &links_string);
		
		if (m_pWriter->AddLinkIntoList(links_string, dbname, rhs_dbname))
		{
			m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, links_string);
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::RemoveLink(const string& dbname, const string& rhs_dbname)
	{
		__ENTER_FUNCTION
			std::string links_string;
		m_pDb->Get(ReadOptions(), DATABASE_LINK_KEY, &links_string);

		if (m_pWriter->RemoveLinkFromList(links_string, dbname, rhs_dbname))
		{
			m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, links_string);
			return TRUE;
		}
		else
		{
			return FALSE;
		}

		__LEAVE_FUNCTION
			return FALSE;
	}

	VOID AdminDB::SetDBWriter(IAdminDBWriter* pWriter)
	{
		SAFE_DELETE(m_pWriter);
		m_pWriter = pWriter;
	}
}
