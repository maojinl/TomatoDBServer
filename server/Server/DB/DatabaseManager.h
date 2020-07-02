#ifndef __DATABASEMANAGER_H__
#define __DATABASEMANAGER_H__

#include <unordered_map>

#include "Type.h"
#include "leveldb/db.h"
#include "GameUtil.h"
#include "leveldb\db.h"
#include "AdminDB.h"
#include "DatabaseObject.h"
namespace tomatodb
{
	class DatabaseManager
	{
	public:
		DatabaseManager();
		~DatabaseManager();

		VOID CleanUp();
		BOOL Init();
		BOOL Tick();
		BOOL CreateDatabase(string database_name);
		BOOL DeleteDatabase(string database_name);
		static string GetDBPathName(string path, string dbname)
		{
			string fullDbName(path);
			fullDbName = EnvFileAPI::FormatDir(fullDbName);
			fullDbName.append(dbname);
			return fullDbName;
		}
	private:
		MyLock m_Lock;
		DatabaseObject* m_pDbList[MAX_DATABASE_SIZE];
		list<DatabaseObject*> m_pDbRecycleList;
		AdminDB* m_pAdmin;
		UINT m_DbCount;
		std::unordered_map<string, UINT> m_DbIndexer;
		VOID UpdateRecycleDBList();
	};

	extern DatabaseManager* g_pDatabaseManager;
}
#endif
