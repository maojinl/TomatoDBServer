#include "stdafx.h"

#include "AdminDB.h"
#include "Log.h"
#include "json.hpp"
#include "Config.h"
#include "leveldb/env.h"

namespace tomatodb
{
	const string AdminDB::DATABASE_NAME_KEY = "DATABASE_NAME_KEY";
	const string AdminDB::ADMIN_DATABASE_NAME = "AdminDB";
	AdminDB* AdminDB::m_pObj;

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

			//SAFE_DELETE( m_pServerSocket ) ;

			__LEAVE_FUNCTION
	}

	VOID AdminDB::CleanUp()
	{
		__ENTER_FUNCTION

			__LEAVE_FUNCTION
	}

	BOOL AdminDB::Init()
	{
		__ENTER_FUNCTION
		if (m_pDb == nullptr)
		{
			std::string dbname(g_Config.m_ConfigInfo.m_AdminDBPath);
			dbname.append(ADMIN_DATABASE_NAME);
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
			assert(s.ok());
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
		//nlohmann::json j = { j_array };
		std::stringstream ss;
		ss << j_array;
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, ss.str());
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::GetDatabasesList(vector<string>& database_list)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j(databases_string);

		for (int i = 0; i < j.array().count(); i++)
		{
			database_list.push_back(j_array{});
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL AdminDB::CreateDatabase(string database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j(databases_string);
		nlohmann::json j_array = j[DATABASE_NAME_KEY];
		for (std::string dbpathname : j_array)
		{
			if (dbpathname == database_name)
			{
				return FALSE;
			}
		}
		j_array.push_back(database_name);

		std::stringstream ss;
		ss << j;
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, ss.str());

		return TRUE;
		__LEAVE_FUNCTION

		return FALSE;
	}

	BOOL AdminDB::DeleteDatabase(string database_name)
	{
		__ENTER_FUNCTION
		std::string databases_string;
		m_pDb->Get(ReadOptions(), DATABASE_NAME_KEY, &databases_string);
		nlohmann::json j(databases_string);
		nlohmann::json j_array = j[DATABASE_NAME_KEY];
		j_array.erase(database_name);
		std::stringstream ss;
		ss << j;
		m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, ss.str());
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}
}
