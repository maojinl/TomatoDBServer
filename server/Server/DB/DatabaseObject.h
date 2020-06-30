#ifndef __DATABASEOBJECT_H__
#define __DATABASEOBJECT_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"

namespace tomatodb
{
	class DatabaseObject
	{
	private:
		friend class DatabaseManager;
		string database_name;
		string database_path_name;
		leveldb::DB* pDb;
		int refs;
		MyLock dblock;
	public:
		DatabaseObject(string dbname, string dbpathname) :
			database_name(dbname),
			database_path_name(dbpathname),
			pDb(nullptr),
			refs(0),
			dblock()
		{
		};
		~DatabaseObject(){};
		BOOL ReadyToDestroy()
		{
			return refs == 0;
		};
	};
}
#endif
