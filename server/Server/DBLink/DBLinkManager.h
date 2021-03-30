#ifndef __DATABASEMANAGER_H__
#define __DATABASEMANAGER_H__

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
	class DBLinkManager
	{
	public:
		DBLinkManager(const Config& config);
		~DBLinkManager();

		VOID CleanUp();
		BOOL Init();

	};

}
#endif