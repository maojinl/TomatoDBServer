#include "stdafx.h"

#include "DBLinkObject.h"
#include "Log.h"
#include "StringArrayTable.h"
#include "util/trietree.h"

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
		SAFE_DELETE(pDb);
		SAFE_DELETE(pDbR);
		__LEAVE_FUNCTION
	}

	BOOL DBLinkObject::Init(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::CreateLink(const DatabaseOptions& dbOptions)
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

		db_name = linkedTableName + "_" + tableName;
		db_path_name = EnvFileAPI::GetPathName(db_name, dbOptions.LINK_DATABASE_FOLDER);
		s = DB::Open(openOptions, db_path_name, &pDbR);
		if (!s.ok()) {
			leveldb::DestroyDB(db_path_name, openOptions);
			Log::SaveLog(SERVER_LOGFILE, "ERROR: Create link reverse database. Message: %s", s.ToString().c_str());
			return TRUE;
		}
		return TRUE;
		__LEAVE_FUNCTION
			return FALSE;
	}

	BOOL DBLinkObject::DeleteLink(const DatabaseOptions& dbOptions)
	{
		__ENTER_FUNCTION
		SAFE_DELETE(pDb);
		string db_name = tableName + "_" + linkedTableName;
		string db_path_name = EnvFileAPI::GetPathName(db_name, dbOptions.LINK_DATABASE_FOLDER);
		Status s = leveldb::DestroyDB(db_path_name, openOptions);
		if (!s.ok()) {
			Log::SaveLog(SERVER_LOGFILE, "ERROR:  link database. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		SAFE_DELETE(pDbR);
		db_name = linkedTableName + "_" + tableName;
		db_path_name = EnvFileAPI::GetPathName(db_name, dbOptions.LINK_DATABASE_FOLDER);
		s = leveldb::DestroyDB(db_path_name, openOptions);
		if (!s.ok()) {
			Log::SaveLog(SERVER_LOGFILE, "ERROR:  link database. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::UpdateKeysIntoLinks(const string& id1, const vector<string>& id2_list)
	{
		__ENTER_FUNCTION
		string* exLinks;
		Status s = pDb->Get(readOptions, id1, exLinks);

		if (s.IsNotFound())
		{
			StringArrayTable sat;
			sat.InitWithArrays(&id2_list);
			s = pDb->Put(writeOptions, id1, sat.dump());
			if (!s.ok()) {
				Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeysIntoLinks. Message: %s", s.ToString().c_str());
				return FALSE;
			}
		} else if (!s.ok()) {
			Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeysIntoLinks. Message: %s", s.ToString().c_str());
			return FALSE;
		}
		else
		{

		}
		return TRUE;
		__LEAVE_FUNCTION
		return FALSE;
	}

	BOOL DBLinkObject::UpdateKeyAndLinks(const string& id1, const vector<string>& id2_list, const vector<string>& exLinks)
	{
		TrieTree exLinksTree;
		map<TrieTree*, int> treeNodeMap;
		for (int i = 0; i < exLinks.size(); i++)
		{
			TrieTree* t = exLinksTree.AddWord(Slice(exLinks[i]));
			treeNodeMap.insert(std::pair<TrieTree*, char>(t, i));
		}
		vector<int> removing;
		vector<int> adding;
		for (int i = 0; i < id2_list.size(); i++)
		{
			TrieTree* t = exLinksTree.FindWord(Slice(id2_list[i]));
			if (t == nullptr)
			{
				adding.push_back(i);
			}
			else
			{
				std::map<TrieTree*, int>::iterator ite = treeNodeMap.find(t);
				ite->second = -1;
			}
		}

		for (std::map<TrieTree*, int>::iterator ite = treeNodeMap.begin(); ite != treeNodeMap.end(); ite++)
		{
			if (ite->second >= 0)
			{
				removing.push_back(ite->second);
			}
		}

		vector<string> keys{id1};
		for (int i = 0; i < removing.size(); i++)
		{
			string val;
			Status s = pDbR->Get(readOptions, exLinks[removing[i]], &val);

			if (s.IsNotFound())
			{
				Log::SaveLog(SERVER_LOGFILE, "Warning: UpdateKeyAndLinks remove keys not found. Message: %s", s.ToString().c_str());
			}
			else if (!s.ok())
			{
				Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeyAndLinks remove keys. Message: %s", s.ToString().c_str());
				return FALSE;
			}
			else
			{
				StringArrayTable sat;
				sat.InitWithData(val.length(), val.c_str());
				if (sat.FindNodeAtKeys(keys))
				{
					sat.DeleteArrayAtCurrentNode();
					val = sat.dump();
					s = pDbR->Put(writeOptions, Slice(exLinks[removing[i]]), Slice(val));
					if (!s.ok())
					{
						Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeyAndLinks remove keys. Message: %s", s.ToString().c_str());
						return FALSE;
					}
				}
			}
		}

		for (int i = 0; i < adding.size(); i++)
		{
			string val;
			Status s = pDbR->Get(readOptions, id2_list[adding[i]], &val);

			if (s.IsNotFound())
			{
				Log::SaveLog(SERVER_LOGFILE, "Warning: UpdateKeyAndLinks add keys not found. Message: %s", s.ToString().c_str());
			}
			else if (!s.ok())
			{
				Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeyAndLinks add keys. Message: %s", s.ToString().c_str());
				return FALSE;
			}
			else
			{
				StringArrayTable sat;
				sat.InitWithData(val.length(), val.c_str());
				if (!sat.FindNodeAtKeys(keys))
				{
					StringArrayTable sat2;
					sat2.InitWithArrays(&keys);
					sat.Append(sat2);
					val = sat.dump();
					s = pDbR->Put(writeOptions, Slice(id2_list[adding[i]]), Slice(val));
					if (!s.ok())
					{
						Log::SaveLog(SERVER_LOGFILE, "ERROR: UpdateKeyAndLinks remove keys. Message: %s", s.ToString().c_str());
						return FALSE;
					}
				}
			}
		}
	}
}
