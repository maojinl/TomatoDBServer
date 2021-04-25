#include "stdafx.h"
#include "DatabaseOptions.h"

namespace tomatodb
{
	const std::string DatabaseOptions::ADMIN_DATABASE_NAME = "AdminDB";
	const std::string DatabaseOptions::LINK_DATABASE_FOLDER = "Links";

	void DatabaseOptions::operator = (const DatabaseOptions& options)
	{
		readOptions = options.readOptions;
		writeOptions = options.writeOptions;
		openOptions = options.openOptions;
		createOptions = options.createOptions;
		userDBPath = options.userDBPath;
		ThreadsCount = options.ThreadsCount;
		adminDBPathName = options.adminDBPathName;
		linksDBPath = options.adminDBPathName;
	}
}