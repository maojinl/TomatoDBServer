#ifndef __DATABASEOPTIONS_H__
#define __DATABASEOPTIONS_H__

#include <unordered_map>

#include "EnvFileAPI.h"
#include "Config.h"
#include "leveldb/options.h"

using namespace leveldb;
namespace tomatodb
{
	class DatabaseOptions
	{
	private:

	public:
		ReadOptions readOptions;
		WriteOptions writeOptions;
		Options openOptions;
		Options createOptions;
		string adminDBPathName;
		string userDBPath;
		int ThreadsCount;
		//admin db name
		static const string ADMIN_DATABASE_NAME;
		//end const defines

		DatabaseOptions(const Config& config) :
			readOptions(),
			writeOptions(),
			openOptions(),
			createOptions(),
			userDBPath(config.m_ConfigInfo.m_DataPath),
			ThreadsCount(config.m_WorkerInfo.m_WorkerCount) {
			adminDBPathName = EnvFileAPI::GetPathName(config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME);
			createOptions.create_if_missing = true;
		};
		~DatabaseOptions() {
		};

	};
}


#endif
