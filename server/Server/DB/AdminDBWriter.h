#ifndef __ADMINDB_WRITER_H__
#define __ADMINDB_WRITER_H__

#include "Type.h"
#include "json.hpp"
#include "StringArrayTable.h"

namespace tomatodb
{
	class IAdminDBWriter
	{
	public:
		virtual string NewDBList() = 0;
		virtual bool AddDBIntoList(string& dblist, const string& dbname) = 0;
		virtual void ReadDBList(const string& dblist, vector<string>& db_list) = 0;
		virtual string NewLinkList() = 0;
		virtual void ReadLinkList(const string& data, const string& dbname, vector<string>& link_list) = 0;
		virtual bool AddLinkIntoList(string& dblinkList, const string& dbname, const string& rhs_dbname) = 0;
		virtual bool RemoveDBFromList(string& dblist, const string& database_name) = 0;
		virtual bool RemoveLinkFromList(string& dblinkList, const string& dbname, const string& rhs_dbname) = 0;
	};

	class JsonAdminDBWriter : public IAdminDBWriter
	{
	private:
		static const string DATABASE_KEY_IN_LINK;
		static const string LINKS_KEY_IN_LINK;
	public:
		virtual string NewDBList();
		virtual bool AddDBIntoList(string& dblist, const string& database_name);
		virtual void ReadDBList(const string& data, vector<string>& db_list);
		virtual string NewLinkList();
		virtual void ReadLinkList(const string& data, const string& dbname, vector<string>& link_list);
		virtual bool AddLinkIntoList(string& dblinkList, const string& dbname, const string& rhs_dbname);
		virtual bool RemoveDBFromList(string& dblist, const string& database_name);
		virtual bool RemoveLinkFromList(string& dblinkList, const string& dbname, const string& rhs_dbname);
	};


	class ArrayTableAdminDBWriter : public IAdminDBWriter
	{
	public:
		virtual string NewDBList();
		virtual bool AddDBIntoList(string& dblist, const string& database_name);
		virtual void ReadDBList(const string& data, vector<string>& db_list);
		virtual string NewLinkList();
		virtual void ReadLinkList(const string& data, const string& dbname, vector<string>& link_list);
		virtual bool AddLinkIntoList(string& dblinkList, const string& dbname, const string& rhs_dbname);
		virtual bool RemoveDBFromList(string& dblist, const string& database_name);
		virtual bool RemoveLinkFromList(string& dblinkList, const string& dbname, const string& rhs_dbname);
	};
} 
#endif
