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
		Options options;
		string adminDBPathName;
		string userDBPath;
		//admin db name
		static const string ADMIN_DATABASE_NAME;
		//end const defines

		DatabaseOptions(Config config) :
			readOptions(),
			writeOptions(),
			options(),
			userDBPath(config.m_ConfigInfo.m_DataPath)
		{
			adminDBPathName = EnvFileAPI::GetPathName(config.m_ConfigInfo.m_AdminDBPath, DatabaseOptions::ADMIN_DATABASE_NAME);
			
		};
		~DatabaseOptions() {};

	};
}


#endif
