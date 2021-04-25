#ifndef __DATABASEOBJECT_H__
#define __DATABASEOBJECT_H__

#include "Type.h"
#include "DatabaseOptions.h"
#include "leveldb/db.h"
#include "leveldb/write_batch.h"
#include "GameUtil.h"
#include "DBLink/DBLinkObject.h"


using namespace leveldb;

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
		DB* pDb;
		int refs;
		MyLock dblock;
		DatabaseObjectStatus status;
	public:
		DatabaseObject(string dbname, string dbpathname) :
			database_name(dbname),
			database_path_name(dbpathname),
			pDb(nullptr),
			refs(0),
			dblock(),
			status(DatabaseObjectStatus::StatusInit) {
		};
		~DatabaseObject() {
			CloseDB();
		};
		BOOL NotInUse();

		void Ref();

		void Unref();

		BOOL IsNormal();

		BOOL IsDeletePending();

		Status CreateDB(const DatabaseOptions& dbOptions);

		Status OpenDB(const DatabaseOptions& dbOptions);

		void CloseDB();

		Status DestroyDB(const Options& options);

		BOOL InsertIntoDB(const WriteOptions& wOpts, const string& key, const string& val, WriteBatch& wBatch, int tID);

		BOOL DeleteFromDB(const WriteOptions& wOpts, const string& key, WriteBatch& wBatch, int tID);

		BOOL GetFromDB(const ReadOptions& rOpts, const string& key, string* val);
	};
}
#endif
