#ifndef __ADMINDB_H__
#define __ADMINDB_H__

#include "Type.h"
#include "leveldb/db.h"

using namespace leveldb;
namespace tomatodb
{
	class AdminDB
	{
	private:
		friend class DatabaseManager;
		AdminDB();
		static AdminDB* m_pAdminDBObj;
		DB* m_pDb;
		BOOL InitializeAdminDB();
		BOOL GetDatabasesList(vector<string>& databases_list);
	public:
		//const defines
		//Keys in admin db
		static const string DATABASE_NAME_KEY;

		~AdminDB();
		VOID CleanUp();
		BOOL Init(string dbname);
		BOOL CreateDatabase(const string& database_name);
		BOOL DeleteDatabase(const string& database_name);

		static AdminDB* GetInstance() {
			//must be called firstly in main thread
			if (m_pAdminDBObj == nullptr) {
				m_pAdminDBObj = new AdminDB();
			}
			return m_pAdminDBObj;
		}

		static void ReleaseInstance() {
			//must be called before ends in main thread
			SAFE_DELETE(m_pAdminDBObj);
		}
	};
} 
#endif
