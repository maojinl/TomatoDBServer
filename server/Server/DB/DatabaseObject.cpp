#include "stdafx.h"

#include "Type.h"
#include "DatabaseOptions.h"
#include "DatabaseObject.h"

#include "leveldb/db.h"
#include "leveldb/write_batch.h"

namespace tomatodb 
{
	BOOL DatabaseObject::NotInUse()
	{
		AutoLock_T l(dblock);
		return refs == 0;
	};

	void DatabaseObject::Ref() {
		AutoLock_T l(dblock); 
		++refs; 
	};

	void DatabaseObject::Unref() {
		assert(refs >= 1);
		AutoLock_T l(dblock);
		--refs;
	};

	BOOL DatabaseObject::IsNormal()
	{
		return status == DatabaseObjectStatus::StatusNormal;
	}

	BOOL DatabaseObject::IsDeletePending()
	{
		return status == DatabaseObjectStatus::StatusDeletePending;
	}

	Status DatabaseObject::CreateDB(const DatabaseOptions& dbOptions)
	{
		Status s = DB::OpenTmt(dbOptions.ThreadsCount, dbOptions.createOptions, database_path_name, &pDb);
		if (s.ok())
		{
			status = DatabaseObjectStatus::StatusNormal;
		}
		return s;
	}

	Status DatabaseObject::OpenDB(const DatabaseOptions& dbOptions)
	{
		Status s = DB::OpenTmt(dbOptions.ThreadsCount, dbOptions.openOptions, database_path_name, &pDb);
		if (s.ok())
		{
			status = DatabaseObjectStatus::StatusNormal;
		}
		return s;
	}

	void DatabaseObject::CloseDB()
	{
		SAFE_DELETE(pDb);
	}

	Status DatabaseObject::DestroyDB(const Options& options)
	{
		CloseDB();
		Status s = leveldb::DestroyDB(database_path_name, options);
		if (s.ok())
		{
			status = DatabaseObjectStatus::StatusDeleted;
		}
		return s;
	}

	BOOL DatabaseObject::InsertIntoDB(const WriteOptions& wOpts, const string& key, const string& val, WriteBatch& wBatch, int tID)
	{
		wBatch.Clear();
		wBatch.Put(key, val);
		pDb->WriteEx(wOpts, &wBatch, tID);
		return TRUE;
	}

	BOOL DatabaseObject::DeleteFromDB(const WriteOptions& wOpts, const string& key, WriteBatch& wBatch, int tID)
	{
		wBatch.Clear();
		wBatch.Delete(key);
		pDb->WriteEx(wOpts, &wBatch, tID);
		return TRUE;
	}

	BOOL DatabaseObject::GetFromDB(const ReadOptions& rOpts, const string& key, string* val)
	{
		Status s = pDb->Get(rOpts, key, val);
		if (s.IsNotFound())
		{
			return FALSE;
		}
		return TRUE;
	}
}
