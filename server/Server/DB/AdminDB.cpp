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
	const string AdminDB::DATABASE_KEY_IN_LINK = "Database";
	const string AdminDB::LINKS_KEY_IN_LINK = "Links";
	AdminDB* AdminDB::m_pAdminDBObj;

	AdminDB::AdminDB()
		:m_pDb(nullptr)
	{
		__ENTER_FUNCTION

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
		nlohmann::json j_array = nlohmann::json::array();
		string jstr = j_array.dump();
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, jstr);
		m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, jstr);
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::GetDatabasesList(vector<string>& database_list)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j = nlohmann::json::parse(databases_string);
		for (const std::string dbname : j)
		{
			database_list.push_back(dbname);
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::CreateDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j = nlohmann::json::parse(databases_string);
		for (std::string dbname : j)
		{
			if (dbname == database_name)
			{
				return FALSE;
			}
		}
		nlohmann::json jDb(database_name);
		j.push_back(jDb);

		string jstr = j.dump();
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, jstr);

		return TRUE;
		__LEAVE_FUNCTION

		return FALSE;
	}

	BOOL AdminDB::DeleteDatabase(const string& database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j = nlohmann::json::parse(databases_string);
		nlohmann::json jDb(database_name);
		for (int i = 0; i < j.size(); i++)
		{
			if (j[i] == database_name)
			{
				j.erase(i);
				string jstr = j.dump();
				m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, jstr);
				return TRUE;
			}
		}
		return FALSE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::GetLinksList(const string& dbname, vector<string>& link_list)
	{
		__ENTER_FUNCTION
		std::string links_string;
		m_pDb->Get(ReadOptions(), DATABASE_LINK_KEY, &links_string);
		nlohmann::json j = nlohmann::json::parse(links_string);
		for (nlohmann::json::iterator ite = j.begin(); ite != j.end(); ite++)
		{
			nlohmann::json dblinks = ite.value();
			if (dbname == dblinks.at(DATABASE_KEY_IN_LINK))
			{
				nlohmann::json links = dblinks.at(LINKS_KEY_IN_LINK);
				for (string rhs_db : links)
				{
					link_list.push_back(rhs_db);
				}
			}
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::AddLink(const string& dbname, const string &rhs_dbname)
	{
		__ENTER_FUNCTION
		std::string links_string;
		m_pDb->Get(ReadOptions(), DATABASE_LINK_KEY, &links_string);
		nlohmann::json j = nlohmann::json::parse(links_string);
		bool appended = false;
		for (int i = 0; i < j.size(); i++)
		{
			if (dbname == j[i].at(DATABASE_KEY_IN_LINK))
			{
				j[i].at(LINKS_KEY_IN_LINK).push_back(rhs_dbname);
				appended = true;
				string jstr = j.dump();
				m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, jstr);
				break;
			}
		}
		if (!appended)
		{
			nlohmann::json links = nlohmann::json::array();
			links.push_back(rhs_dbname);
			nlohmann::json jDblinks{ { DATABASE_KEY_IN_LINK, dbname}, {LINKS_KEY_IN_LINK, links} };
			j.push_back(jDblinks);
			string jstr = j.dump();
			m_pDb->Put(WriteOptions(), DATABASE_LINK_KEY, jstr);
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}
}
