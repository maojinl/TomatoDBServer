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

namespace tomatodb
{
	class DatabaseManager
	{
	public:
		DatabaseManager(const Config& config);
		~DatabaseManager();

		VOID CleanUp();
		BOOL Init();
		BOOL Tick();
		BOOL CreateDatabase(const string& database_name);
		BOOL DeleteDatabase(const string& database_name);
		BOOL InsertIntoDB(const string& database_name, const string& key, const string& val, UINT threadIdx);
		BOOL DeleteFromDB(const string& database_name, const string& key, UINT threadIdx);
		BOOL GetFromDB(const string& database_name, const string& key, string* val);
		BOOL GetDatabasesList(vector<string>& database_list);
		BOOL HeartBeat();
	private:
		MyLock m_Lock;
		DatabaseObject* m_pDbList[MAX_DATABASE_SIZE];
		list<DatabaseObject*> m_pDbRecycleList;
		AdminDB* m_pAdmin;
		UINT m_DbCount;
		std::unordered_map<string, UINT> m_DbIndexer;
		const DatabaseOptions dbOptions;
		DBThreadObjectsPool* threadObjectsPool;
		VOID UpdateRecycleDBList();
		BOOL DeleteDatabaseCore(DatabaseObject* pDbObj);
		DatabaseObject* RefDatabaseHandler(string database_name);
		VOID UnrefDatabaseHandler(DatabaseObject* pDbObj);
	};

	extern DatabaseManager* g_pDatabaseManager;
}
#endif
