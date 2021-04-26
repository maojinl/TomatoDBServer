#ifndef __DBLINKMANAGER_H__
#define __DBLINKMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "GameDefine.h"
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
		typedef unordered_map<string, DBLinkObject*> DBLinkObjectsTable;
	private:
		AdminDB* m_pAdmin;
		unordered_map<string, DBLinkObjectsTable*> dbLinksTable;
		DatabaseOptions dbOptions;
		vector<DBLinkObject*> linkRecycleList;
		MyLock m_Lock;
		DBLinkObject* RefLinkHandler(const string& dbname, const string& rhsdbname);
		VOID UnrefLinkHandler(DBLinkObject* pDbObj);
		VOID UpdateRecycleLinkList();
	public:
		DBLinkManager(const DatabaseOptions& options);
		~DBLinkManager();

		VOID CleanUp();
		BOOL Init();
		BOOL GetLinksList(const string& dbname, vector<string>& value);
		BOOL CreateLink(const string& dbname, const string& rhsdbname);
		BOOL DeleteLink(const string& dbname, const string& rhsdbname);
		BOOL UpdateKeysIntoLinks(const string& dbname, const string& rhsdbname, const string& id1, const vector<string>& id2_list);
		BOOL DeleteKeysFromLinks(const string& dbname, const string& rhsdbname, const string& id1);
		BOOL HeartBeat();
		BOOL DeletLinkCore(DBLinkObject* pLinkObj);
	};
}
#endif
