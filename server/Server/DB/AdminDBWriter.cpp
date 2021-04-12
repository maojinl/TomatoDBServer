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
		return j_array.dump();
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

	bool JsonAdminDBWriter::RemoveDBFromList(string& dblist, const string& database_name)
	{
		nlohmann::json j = nlohmann::json::parse(dblist);
		for (int i = 0; i < j.size(); i++)
		{
			if (j[i] == database_name)
			{
				j.erase(i);
				dblist = j.dump();
				return true;
			}
		}
		return false;
	}

	bool JsonAdminDBWriter::RemoveLinkFromList(string& dblinkList, const string& dbname, const string& rhs_dbname)
	{
		nlohmann::json j = nlohmann::json::parse(dblinkList);
		bool appended = false;
		for (int i = 0; i < j.size(); i++)
		{
			if (dbname == j[i].at(DATABASE_KEY_IN_LINK))
			{
				if (j[i].at(LINKS_KEY_IN_LINK).size() > 1)
				{
					j[i].at(LINKS_KEY_IN_LINK).erase(dbname);
				}
				else
				{
					j.erase(i);
				}

				dblinkList = j.dump();
				return true;
			}
		}
		return false;
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
		return j_array.dump();
	}

	void JsonAdminDBWriter::ReadLinkList(const string& data, const string& dbname, vector<string>& link_list)
	{
		nlohmann::json j = nlohmann::json::parse(data);
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
	}

	bool JsonAdminDBWriter::AddLinkIntoList(string& dblinkList, const string& dbname, const string& rhs_dbname)
	{
		nlohmann::json j = nlohmann::json::parse(dblinkList);
		bool appended = false;
		for (int i = 0; i < j.size(); i++)
		{
			if (dbname == j[i].at(DATABASE_KEY_IN_LINK))
			{
				j[i].at(LINKS_KEY_IN_LINK).push_back(rhs_dbname);
				appended = true;
				dblinkList = j.dump();
				break;
			}
		}
		if (!appended)
		{
			nlohmann::json links = nlohmann::json::array();
			links.push_back(rhs_dbname);
			nlohmann::json jDblinks{ { DATABASE_KEY_IN_LINK, dbname}, {LINKS_KEY_IN_LINK, links} };
			j.push_back(jDblinks);
			dblinkList = j.dump();
		}
		return true;
	}

	string ArrayTableAdminDBWriter::NewDBList()
	{
		StringArrayTable sat;
		sat.InitEmptyStruct(1);
		return sat.dump();
	}

	bool ArrayTableAdminDBWriter::AddDBIntoList(string& dblist, const string& database_name)
	{
		StringArrayTable sat;
		sat.InitWithData(dblist.size(), &dblist[0]);
		StringArrayTable sat2;
		vector<string> vs{ database_name };
		sat.InitWithArrays(&vs);
		sat.Append(sat2);
		dblist = sat.dump();
		return true;
	}

	bool ArrayTableAdminDBWriter::RemoveDBFromList(string& dblist, const string& database_name)
	{
		StringArrayTable sat;
		sat.InitWithData(dblist.size(), &dblist[0]);
		vector<string> vs, vs2;
		if (sat.GetArrayAtKeys(vs, vs2))
		{
			for (int i = 0; i < vs2.size(); i++)
			{
				if (vs2[i] == database_name)
				{
					if (i < vs2.size())
					{
						vs2[i] = vs2[vs2.size() - 1];
					}
					vs2.pop_back();
					sat.WriteArrayAtCurrentNode(vs2);
					dblist = sat.dump();
					return true;
				}
			}
		}
		return false;
	}

	void ArrayTableAdminDBWriter::ReadDBList(const string& data, vector<string>& valueList)
	{
		StringArrayTable sat;
		sat.InitWithData(data.size(), &data[0]);
		vector<string> vs, vs2;
		if (sat.GetArrayAtKeys(vs, vs2))
		{
			for (int i = 0; i < vs2.size(); i++)
			{
				valueList.push_back(vs[i]);
			}
		}
		return;
	}

	string ArrayTableAdminDBWriter::NewLinkList()
	{
		StringArrayTable sat;
		sat.InitEmptyStruct(1);
		return sat.dump();
	}

	void JsonAdminDBWriter::ReadLinkList(const string& data, const string& dbname, vector<string>& link_list)
	{
		StringArrayTable sat;
		sat.InitWithData(data.size(), &data[0]);
		vector<string> vs{ dbname };
		vector<string> vs2;
		if (sat.GetArrayAtKeys(vs, vs2))
		{
			for (int i = 0; i < vs2.size(); i++)
			{
				link_list.push_back(vs[i]);
			}
		}
		return;
	}

	bool JsonAdminDBWriter::AddLinkIntoList(string& dblinkList, const string& dbname, const string& rhs_dbname)
	{
		StringArrayTable sat;
		sat.InitWithData(dblinkList.size(), &dblinkList[0]);
		vector<string> vs{ dbname };
		vector<string> vs2;

		if (sat.GetArrayAtKeys(vs, vs2))
		{
			for (int i = 0; i < vs2.size(); i++)
			{
				if (dbname == vs2[i])
				{
					return false;
				}
			}
			vs2.push_back(rhs_dbname);
			sat.WriteArrayAtCurrentNode(vs2);
		}
		else
		{
			vs2.push_back(rhs_dbname);
			StringArrayTable sat2;
			vector<vector<string>> vvs;
			vvs.push_back(vs2);
			if (sat2.InitWithArrays(&vs, &vvs))
			{
				sat.Append(sat2);
			}
			else
			{
				return false;
			}
		}
		dblinkList = sat.dump();
		return true;
	}

	bool JsonAdminDBWriter::RemoveLinkFromList(string& dblinkList, const string& dbname, const string& rhs_dbname)
	{
		nlohmann::json j = nlohmann::json::parse(dblinkList);
		bool appended = false;
		for (int i = 0; i < j.size(); i++)
		{
			if (dbname == j[i].at(DATABASE_KEY_IN_LINK))
			{
				if (j[i].at(LINKS_KEY_IN_LINK).size() > 1)
				{
					j[i].at(LINKS_KEY_IN_LINK).erase(dbname);
				}
				else
				{
					j.erase(i);
				}

				dblinkList = j.dump();
				return true;
			}
		}
		return false;
	}
}
