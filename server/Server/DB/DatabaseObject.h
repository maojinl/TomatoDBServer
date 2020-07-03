#ifndef __DATABASEOBJECT_H__
#define __DATABASEOBJECT_H__

#include "Type.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

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

		void Ref() { ++refs; };

		void Unref() {
			//assert(refs_ >= 1);
			--refs;
		};

		BOOL InsertIntoDB(const string& key, const string& val, const WriteOptions& wOpts, WriteBatch& wBatch)
		{
			wBatch.Clear();
			wBatch.Put(key, val);
			pDb->Write(wOpts, &wBatch);
			return TRUE;
		}
	};
}
#endif
