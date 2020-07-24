#ifndef __DATABASEOBJECT_H__
#define __DATABASEOBJECT_H__

#include "Type.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"

namespace tomatodb
{
	enum DatabaseStatus	{
		DatabaseStatusNormal = 0,
		DatabaseStatusDeletePending
	};

	class DatabaseObject
	{
	private:
		friend class DatabaseManager;
		string database_name;
		string database_path_name;
		leveldb::DB* pDb;
		int refs;
		MyLock dblock;
		DatabaseStatus status;
	public:
		DatabaseObject(string dbname, string dbpathname) :
			database_name(dbname),
			database_path_name(dbpathname),
			pDb(nullptr),
			refs(0),
			dblock(),
			status(DatabaseStatusNormal) {
		};
		~DatabaseObject() {
			CloseDB();
		};
		BOOL ReadyToDestroy()
		{
			return refs == 0;
		};

		void Ref() { 
			AutoLock_T l(dblock); 
			++refs; 
		};

		void Unref() {
			//assert(refs_ >= 1);
			AutoLock_T l(dblock);
			--refs;
		};

		BOOL IsNormal()
		{
			return status == DatabaseStatusNormal;
		}

		BOOL IsDeletePending()
		{
			return status == DatabaseStatusDeletePending;
		}

		Status OpenDB(const Options& options)
		{
			return leveldb::DB::Open(options, database_path_name, &pDb);
		}

		void CloseDB()
		{
			SAFE_DELETE(pDb);
		}

		Status DestroyDB(const Options& options)
		{
			CloseDB();
			return leveldb::DestroyDB(database_path_name, options);
		}

		BOOL InsertIntoDB(const WriteOptions& wOpts, const string& key, const string& val, WriteBatch& wBatch)
		{
			wBatch.Clear();
			wBatch.Put(key, val);
			pDb->Write(wOpts, &wBatch);
			return TRUE;
		}

		BOOL DeleteFromDB(const WriteOptions& wOpts, const string& key, WriteBatch& wBatch)
		{
			wBatch.Clear();
			wBatch.Delete(key);
			pDb->Write(wOpts, &wBatch);
			return TRUE;
		}

		BOOL GetFromDB(const ReadOptions& rOpts, const string& key, string* val)
		{
			Status s = pDb->Get(rOpts, key, val);
			if (s.IsNotFound())
			{
				return FALSE;
			}
			return TRUE;
		}
	};
}
#endif
