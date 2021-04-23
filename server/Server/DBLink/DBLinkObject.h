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
		BOOL UpdateKeyAndLinks(const string& id1, const vector<string>& id2_list, const vector<string>& exLinks);
		BOOL CreateOrOpenLink(const DatabaseOptions& dbOptions, Options options);
	public:
		DBLinkObject(string tableName1, string tableName2);
		~DBLinkObject();

		VOID CleanUp();
		BOOL Init(const DatabaseOptions& options);
		BOOL CreateLink(const DatabaseOptions& options);
		BOOL OpenLink(const DatabaseOptions& options);
		BOOL DeleteLink(const DatabaseOptions& dbOptions);
		BOOL UpdateKeysIntoLinks(const string& id1, const vector<string>& id2_list);
		BOOL RemoveReverseLinks(const string& id1, const vector<int>& removing, const vector<string>& inLinks);
		BOOL AddReverseLinks(const string& id1, const vector<int>& adding, const vector<string>& exLinks);
		BOOL DeleteKeysFromLinks(const string& id1);
		

	};

}
#endif
