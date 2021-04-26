#ifndef __DLINK_OBJECT_H__
#define __DLINK_OBJECT_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"
#include "GameUtil.h"
#include "DatabaseObject.h"
#include "DatabaseOptions.h"
#include "DBThreadObjectsPool.h"
#include "ReadWriteLock.h"

namespace tomatodb
{
	class DBLinkObject
	{
	private:
		string tableName;
		string linkedTableName;
		DB* pDb;
		DB* pDbR;
		ReadOptions readOptions;
		WriteOptions writeOptions;
		Options openOptions;
		Options createOptions;
		int refs;
		MyLock linklock;
		BOOL UpdateKeyAndLinks(const string& id1, const vector<string>& id2_list, const vector<string>& exLinks);
		BOOL CreateOrOpenLink(const DatabaseOptions& dbOptions, Options options);
		BOOL RemoveReverseLinks(const string& id1, const vector<int>& removing, const vector<string>& inLinks);
		BOOL AddReverseLinks(const string& id1, const vector<int>& adding, const vector<string>& exLinks);
	public:
		DBLinkObject(string tableName1, string tableName2);
		~DBLinkObject();

		VOID CleanUp();
		BOOL Init(const DatabaseOptions& options);
		BOOL NotInUse();
		void Ref();
		void Unref();
		BOOL IsNormal();
		BOOL IsDeletePending();
		BOOL CreateLink(const DatabaseOptions& options);
		BOOL OpenLink(const DatabaseOptions& options);
		BOOL DeleteLink(const DatabaseOptions& dbOptions);
		BOOL UpdateKeysIntoLinks(const string& id1, const vector<string>& id2_list);
		BOOL DeleteKeysFromLinks(const string& id1);
		
		DatabaseObjectStatus status;
	};

}
#endif
