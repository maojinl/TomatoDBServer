#ifndef __DLINK_OBJECT_H__
#define __DLINK_OBJECT_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"
#include "GameUtil.h"
#include "AdminDB.h"
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
	public:
		DBLinkObject(const Config& config, string tableName1, string tableName2);
		~DBLinkObject();

		VOID CleanUp();
		BOOL Init(const Options& options);

	};

}
#endif
