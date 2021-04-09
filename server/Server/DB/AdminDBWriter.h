#ifndef __ADMINDB_WRITER_H__
#define __ADMINDB_WRITER_H__

#include "Type.h"
#include "json.hpp"

namespace tomatodb
{
	class IAdminDBWriter
	{
	public:
		virtual string NewDBList() = 0;
		virtual bool AddDBIntoList(string& dblist, const string& dbname) = 0;
		virtual void ReadDBList(const string& dblist, vector<string>& db_list) = 0;
		virtual string NewLinkList(const vector<string>& dbList) = 0;
		virtual string ReadOneLayerStruct(const string& data, const string& key, vector<string>& valueList) = 0;
	};

	class JsonAdminDBWriter : IAdminDBWriter
	{
	private:
		static const string DATABASE_KEY_IN_LINK;
		static const string LINKS_KEY_IN_LINK;
	public:
		virtual string NewDBList();
		virtual bool AddDBIntoList(string& dblist, const string& database_name);
		virtual void ReadDBList(const string& data, vector<string>& db_list);
		virtual string NewLinkList();
		virtual bool AddLinkIntoList(string& dblinkList, string& dbname, const vector<string>& link_list);
	};
} 
#endif
