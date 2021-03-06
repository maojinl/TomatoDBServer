#ifndef __DATABASEOPTIONS_H__
#define __DATABASEOPTIONS_H__

#include <unordered_map>

#include "EnvFileAPI.h"
#include "Config.h"
#include "leveldb/options.h"

using namespace leveldb;
namespace tomatodb
{
	enum DatabaseObjectStatus {
		StatusInit = 0,
		StatusNormal,
		StatusDeletePending,
		StatusDeleted
	};

	class DatabaseOptions
	{
	private:

	public:
		ReadOptions readOptions;
		WriteOptions writeOptions;
		Options openOptions;
		Options createOptions;
		string adminDBPathName;
		string linksDBPath;
		string userDBPath;
		int ThreadsCount;
		//admin db name
		static const string ADMIN_DATABASE_NAME;
		static const string LINK_DATABASE_FOLDER;
		//end const defines

		DatabaseOptions(const Config& config) :
			readOptions(),
			writeOptions(),
			openOptions(),
			createOptions(),
			userDBPath(config.m_ConfigInfo.m_DataPath),
			ThreadsCount(config.m_WorkerInfo.m_WorkerCount) {
			adminDBPathName = EnvFileAPI::GetPathName(config.m_ConfigInfo.m_AdminDBPath, 
				DatabaseOptions::ADMIN_DATABASE_NAME);
			linksDBPath = EnvFileAPI::GetPathName(config.m_ConfigInfo.m_LinksDBPath,
				DatabaseOptions::LINK_DATABASE_FOLDER);
			openOptions.create_if_missing = false;
			createOptions.create_if_missing = true;
			createOptions.error_if_exists = true;
		};

		DatabaseOptions(const DatabaseOptions& options) {
			(*this) = options;
		};

		void operator = (const DatabaseOptions& options);

		~DatabaseOptions() {
		};

	};
}


#endif
