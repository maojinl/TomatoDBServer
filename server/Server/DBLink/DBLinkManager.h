#ifndef __DBLINKMANAGER_H__
#define __DBLINKMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"
#include "GameUtil.h"
#include "AdminDB.h"
#include "DatabaseObject.h"
#include "DatabaseOptions.h"
#include "DBThreadObjectsPool.h"
#include "ReadWriteLock.h"
#include "DBLinkObject.h"

namespace tomatodb
{
	class DBLinkManager
	{
	private:
		AdminDB* m_pAdmin;
		unordered_map<string, DBLinkObject*> m_pLinkMap[MAX_DB_LINK_SIZE];
	public:
		DBLinkManager(const Config& config);
		~DBLinkManager();

		VOID CleanUp();
		BOOL Init(const DatabaseOptions& dbOptions);

	};

}
#endif
