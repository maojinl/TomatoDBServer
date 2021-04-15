#include "stdafx.h"

#include "DBLinkObject.h"
#include "Log.h"

namespace tomatodb
{
	DBLinkObject::DBLinkObject(const Config& config, string tableName1, string tableName2):
		tableName(tableName1), linkedTableName(tableName2), pDb(nullptr), 
		readOptions(), writeOptions(), openOptions(), createOptions()
	{
		openOptions.create_if_missing = false;
		createOptions.create_if_missing = true;
		createOptions.error_if_exists = true;
		return;
	}

	DBLinkObject::~DBLinkObject()
	{
	}

	VOID DBLinkObject::CleanUp()
	{
		__ENTER_FUNCTION
		__LEAVE_FUNCTION
	}

	BOOL DBLinkObject::Init(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		string db_name = tableName + "_" + linkedTableName;
		string db_path_name = EnvFileAPI::GetPathName(db_name, dbOptions.LINK_DATABASE_FOLDER);
		Status s = DB::Open(openOptions, db_path_name, &pDb);
		if (!s.ok()) {
			leveldb::DestroyDB(db_path_name, openOptions);
			Log::SaveLog(SERVER_LOGFILE, "ERROR: Create link database. Message: %s", s.ToString().c_str());
			return TRUE;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::CreateLink(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		string db_path_name = EnvFileAPI::GetPathName(tableName, dbOptions.LINK_DATABASE_FOLDER);
		Status s = DB::Open(createOptions, db_path_name, &pDb);
		if (!s.ok()) {
			leveldb::DestroyDB(db_path_name, createOptions);
			Log::SaveLog(SERVER_LOGFILE, "ERROR: Create link database. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::DeleteLink(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		SAFE_DELETE(pDb);
		string db_path_name = EnvFileAPI::GetPathName(tableName, dbOptions.LINK_DATABASE_FOLDER);
		Status s = leveldb::DestroyDB(db_path_name, openOptions);
		if (!s.ok()) {
			//m_pAdmin->CreateDatabase(pDbObj->database_name);
			Log::SaveLog(SERVER_LOGFILE, "ERROR:  link database. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::InsertKeysIntoLinks(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
			string db_path_name = EnvFileAPI::GetPathName(tableName, dbOptions.LINK_DATABASE_FOLDER);
		Status s = DB::Open(createOptions, db_path_name, &pDb);
		if (!s.ok()) {
			leveldb::DestroyDB(db_path_name, createOptions);
			Log::SaveLog(SERVER_LOGFILE, "ERROR: Create link database. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		return TRUE;
		__LEAVE_FUNCTION
			return FALSE;
	}
}
