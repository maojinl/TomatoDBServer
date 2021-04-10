#include "stdafx.h"

#include "AdminDBWriter.h"
#include "json.hpp"

namespace tomatodb
{
	const string JsonAdminDBWriter::DATABASE_KEY_IN_LINK = "Database";
	const string JsonAdminDBWriter::LINKS_KEY_IN_LINK = "Links";

	string JsonAdminDBWriter::NewDBList()
	{
		nlohmann::json j_array = nlohmann::json::array();
		string jstr = j_array.dump();
	}

	bool JsonAdminDBWriter::AddDBIntoList(string& dblist, const string& database_name)
	{
		nlohmann::json j = nlohmann::json::parse(dblist);
		for (std::string dbname : j)
		{
			if (dbname == database_name)
			{
				return false;
			}
		}
		nlohmann::json jDb(database_name);
		j.push_back(jDb);
		dblist = j.dump();
		return true;
	}

	bool JsonAdminDBWriter::RemoveDBIntoList(string& dblist, const string& database_name)
	{
		nlohmann::json j = nlohmann::json::parse(dblist);
		for (int i = 0; i < j.size(); i++)
		{
			if (j[i] == database_name)
			{
				j.erase(i);
				string jstr = j.dump();
				m_pDb->Put(WriteOptions(), DATABASE_NAME_KEY, jstr);
				return true;
			}
		}
		return false;
	}

	bool JsonAdminDBWriter::RemoveLinkFromList(string& dblist, const string& database_name)
	{
		nlohmann::json j = nlohmann::json::parse(dblist);
		for (std::string dbname : j)
		{
			if (dbname == database_name)
			{
				return false;
			}
		}
		nlohmann::json jDb(database_name);
		j.push_back(jDb);
		dblist = j.dump();
		return true;
	}


	void JsonAdminDBWriter::ReadDBList(const string& data, vector<string>& valueList)
	{
		nlohmann::json j = nlohmann::json::parse(data);
		for (std::string item : j)
		{
			valueList.push_back(item);
		}
	}

	string JsonAdminDBWriter::NewLinkList()
	{
		nlohmann::json j_array = nlohmann::json::array();
		string jstr = j_array.dump();
	}

	bool JsonAdminDBWriter::AddLinkIntoList(string& dblinkList, string& dbname, const vector<string>& link_list)
	{
		nlohmann::json j = nlohmann::json::parse(dblinkList);
		bool appended = false;
		for (int i = 0; i < j.size(); i++)
		{
			if (dbname == j[i].at(DATABASE_KEY_IN_LINK))
			{
				j[i].at(LINKS_KEY_IN_LINK).push_back(dbname);
				appended = true;
				dblinkList = j.dump();
				break;
			}
		}
		if (!appended)
		{
			nlohmann::json links = nlohmann::json::array();
			links.push_back(dbname);
			nlohmann::json jDblinks{ { DATABASE_KEY_IN_LINK, dbname}, {LINKS_KEY_IN_LINK, links} };
			j.push_back(jDblinks);
			dblinkList = j.dump();
		}
	}
}
