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
		//const defines
		//Keys in admin db
		static const string DATABASE_NAME_KEY;

		//admin db name
		static const string ADMIN_DATABASE_NAME;
		//end const defines

		AdminDB();
		static AdminDB* m_pObj;
		DB* m_pDb;
		BOOL InitializeAdminDB();
	public:
		~AdminDB();
		VOID CleanUp();
		BOOL Init();
		BOOL CreateDatabase(string database_name);
		BOOL DeleteDatabase(string database_name);
		BOOL GetDatabasesList(vector<string>& databases_list);

		static AdminDB* GetInstance() {
			//must be called firstly in main thread
			if (m_pObj == NULL) {
				m_pObj = new AdminDB();
			}
			return m_pObj;
		}
	};
} 
#endif
