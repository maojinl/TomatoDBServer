#ifndef __DATABASEMANAGER_H__
#define __DATABASEMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"
#include "GameUtil.h"
#include "leveldb\db.h"
#include "AdminDB.h"
#include "DatabaseObject.h"
#include "DatabaseOptions.h"
namespace tomatodb
{
	class DatabaseManager
	{
	public:
		DatabaseManager(Config config);
		~DatabaseManager();

		VOID CleanUp();
		BOOL Init();
		BOOL Tick();
		BOOL CreateDatabase(string database_name);
		BOOL DeleteDatabase(string database_name);
		BOOL InsertIntoDB(string database_name, string key, string val);
	private:
		MyLock m_Lock;
		DatabaseObject* m_pDbList[MAX_DATABASE_SIZE];
		list<DatabaseObject*> m_pDbRecycleList;
		AdminDB* m_pAdmin;
		UINT m_DbCount;
		std::unordered_map<string, UINT> m_DbIndexer;
		const DatabaseOptions dbOptions;

		VOID UpdateRecycleDBList();
		DatabaseObject* RefDatabaseHandler(string database_name);
		DatabaseObject* UnrefDatabaseHandler(DatabaseObject* pDbObj);
	};

	extern DatabaseManager* g_pDatabaseManager;
}
#endif
