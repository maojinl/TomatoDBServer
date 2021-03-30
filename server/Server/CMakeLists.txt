set(PROJECT_NAME Server)

################################################################################
# Unit test
################################################################################
set(TOMATODB_BUILD_TESTS ON)

################################################################################
# Source groups
################################################################################
set(Base
    "Base/Config.cpp"
    "Base/Config.h"
    "Base/File.cpp"
    "Base/File.h"
    "Base/FileDef.h"
    "Base/Ini.cpp"
    "Base/Ini.h"
    "Base/Log.cpp"
    "Base/Log.h"
    "Base/Thread.cpp"
    "Base/Thread.h"
    "Base/TimeManager.cpp"
    "Base/TimeManager.h"
)
source_group("Base" FILES ${Base})

set(Character
    "Character/Obj_Human.cpp"
    "Character/Obj_Human.h"
)
source_group("Character" FILES ${Character})

set(Common__Common
    "../../Common/Assertx.cpp"
    "../../Common/Assertx.h"
    "../../Common/BaseType.h"
    "../../Common/FileDataMgr.cpp"
    "../../Common/FileDataMgr.h"
    "../../Common/GameDefine.h"
    "../../Common/GameUtil.cpp"
    "../../Common/GameUtil.h"
    "../../Common/PacketDefine.h"
    "../../Common/PacketFactory.h"
    "../../Common/PacketFactoryManager.cpp"
    "../../Common/PacketFactoryManager.h"
    "../../Common/PlayerStatus.h"
    "../../Common/Rand.cpp"
    "../../Common/Rand.h"
    "../../Common/ReadWriteLock.h"
    "../../Common/ResultDefine.h"
    "../../Common/ShareMemAPI.cpp"
    "../../Common/ShareMemAPI.h"
    "../../Common/Type.h"
)
source_group("Common\\Common" FILES ${Common__Common})

set(Common__DataBase
    "../../Common/DataBase/DBC.cpp"
    "../../Common/DataBase/DBC.h"
)
source_group("Common\\DataBase" FILES ${Common__DataBase})

set(Common__Net
    "../../Common/Net/EnvFileAPI.cpp"
    "../../Common/Net/EnvFileAPI.h"
    "../../Common/Net/Packet.cpp"
    "../../Common/Net/Packet.h"
    "../../Common/Net/ServerSocket.cpp"
    "../../Common/Net/ServerSocket.h"
    "../../Common/Net/Socket.cpp"
    "../../Common/Net/Socket.h"
    "../../Common/Net/SocketAPI.cpp"
    "../../Common/Net/SocketAPI.h"
    "../../Common/Net/SocketInputStream.cpp"
    "../../Common/Net/SocketInputStream.h"
    "../../Common/Net/SocketOutputStream.cpp"
    "../../Common/Net/SocketOutputStream.h"
)
source_group("Common\\Net" FILES ${Common__Net})

set(Common__Packets
    "../../Common/Packets/CSAskLogin.cpp"
    "../../Common/Packets/CSAskLogin.h"
    "../../Common/Packets/SCRetLogin.cpp"
    "../../Common/Packets/SCRetLogin.h"
    "../../Common/Packets/CSAskDBDefinition.cpp"
    "../../Common/Packets/CSAskDBDefinition.h"
    "../../Common/Packets/SCRetDBDefinition.cpp"
    "../../Common/Packets/SCRetDBDefinition.h"
    "../../Common/Packets/CSAskDBManipulate.cpp"
    "../../Common/Packets/CSAskDBManipulate.h"
    "../../Common/Packets/SCRetDBManipulate.cpp"
    "../../Common/Packets/SCRetDBManipulate.h"
    "../../Common/Packets/CSAskDBQuery.cpp"
    "../../Common/Packets/CSAskDBQuery.h"
    "../../Common/Packets/SCRetDBQuery.cpp"
    "../../Common/Packets/SCRetDBQuery.h"
    "../../Common/Packets/GCSystemMsg.cpp"
    "../../Common/Packets/GCSystemMsg.h"
    "../../Common/Packets/GWAskMail.cpp"
    "../../Common/Packets/GWAskMail.h"
    "../../Common/Packets/GWSystemMsg.cpp"
    "../../Common/Packets/GWSystemMsg.h"
    "../../Common/Packets/SSConnect.cpp"
    "../../Common/Packets/SSConnect.h"
    "../../Common/Packets/WGMail.cpp"
    "../../Common/Packets/WGMail.h"
    "../../Common/Packets/WGSystemMsg.cpp"
    "../../Common/Packets/WGSystemMsg.h"
)
source_group("Common\\Packets" FILES ${Common__Packets})

set(Main
    "Main/ClientManager.cpp"
    "Main/ClientManager.h"
    "Main/DaemonThread.cpp"
    "Main/DaemonThread.h"
    "Main/GUIDManager.cpp"
    "Main/GUIDManager.h"
    "Main/MachineManager.cpp"
    "Main/MachineManager.h"
    "Main/Performance.cpp"
    "Main/Performance.h"
    "Main/Server.cpp"
    "Main/Server.h"
    "Main/ServerManager.cpp"
    "Main/ServerManager.h"
    "Main/ServerThread.cpp"
    "Main/ServerThread.h"
    "Main/ShareMemManager.cpp"
    "Main/ShareMemManager.h"
    "Main/ThreadManager.cpp"
    "Main/ThreadManager.h"
    "Main/ThreadPool.cpp"
    "Main/ThreadPool.h"
)
source_group("Main" FILES ${Main})

set(Packets
    "Packets/CSAskLoginHandler.cpp"
    "Packets/CSAskDBDefinitionHandler.cpp"
    "Packets/CSAskDBManipulateHandler.cpp"
    "Packets/CSAskDBQueryHandler.cpp"
    "Packets/NullHandler.cpp"
    "Packets/SSConnectHandler.cpp"
    "Packets/WGMailHandler.cpp"
    "Packets/WGSystemMsgHandler.cpp"
)
source_group("Packets" FILES ${Packets})

set(Player
    "Player/GamePlayer.cpp"
    "Player/GamePlayer.h"
    "Player/IncomingPlayerManager.cpp"
    "Player/IncomingPlayerManager.h"
    "Player/Player.cpp"
    "Player/Player.h"
    "Player/PlayerManager.cpp"
    "Player/PlayerManager.h"
    "Player/PlayerPool.cpp"
    "Player/PlayerPool.h"
    "Player/RecyclePlayerManager.cpp"
    "Player/RecyclePlayerManager.h"
    "Player/ServerPlayer.cpp"
    "Player/ServerPlayer.h"
)
source_group("Player" FILES ${Player})

set(SMU
    "SMU/ShareMemAO.cpp"
    "SMU/ShareMemAO.h"
    "SMU/SMUManager.cpp"
    "SMU/SMUManager.h"
)
source_group("SMU" FILES ${SMU})

set(Worker
    "Worker/Worker.cpp"
    "Worker/Worker.h"
    "Worker/WorkerManager.cpp"
    "Worker/WorkerManager.h"
    "Worker/WorkerPlayerManager.cpp"
    "Worker/WorkerPlayerManager.h"
    "Worker/WorkerThread.cpp"
    "Worker/WorkerThread.h"
)
source_group("Worker" FILES ${Worker})

set(DB
	"DB/AdminDB.cpp"
    "DB/AdminDB.h"
    "DB/DataBaseManager.cpp"
    "DB/DataBaseManager.h"
    "DB/DataBaseObject.h"
    "DB/DataBaseObject.cpp"
    "DB/DataBaseOptions.h"
    "DB/DataBaseOptions.cpp"
    "DB/DBThreadObjectsPool.h"
    "DB/DBThreadObjectsPool.cpp"
)
source_group("DB" FILES ${DB})

set(DBLink
    "DBLink/DBLinkManager.cpp"
    "DBLink/DBLinkManager.h"
    "DBLink/DBLinkObject.cpp"
    "DBLink/DBLinkObject.h"
)
source_group("DBLink" FILES ${DBLink})

set(StdAfx
    "stdafx.cpp"
    "stdafx.h"
)
source_group("StdAfx" FILES ${StdAfx})

set(tinyxml
    "tinyxml/tinyxml.cpp"
    "tinyxml/tinyxml.h"
)
source_group("tinyxml" FILES ${tinyxml})

set(unittest
    "unit_test/unittestutils.h"
    "unit_test/DatabaseManagerTest.cpp"
)
source_group("unittest" FILES ${unittest})

if (WIN32)
	set(util
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/env.cc"
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/env_windows.cc"
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/windows_logger.h"
	)
else (WIN32)
	set(util
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/env.cc"
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/env_posix.cc"
		"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util/posix_logger.h"
	)
endif (WIN32)
source_group("util" FILES ${util})

if (TOMATODB_BUILD_TESTS)
    set(ALL_FILES
        ${Base}
        ${Character}
        ${Common__Common}
        ${Common__DataBase}
        ${Common__Net}
        ${Common__Packets}
        ${Main}
        ${Packets}
        ${Player}
        ${SMU}
        ${Worker}
        ${DB}
        ${DBLink}
        ${StdAfx}
        ${tinyxml}
        ${unittest}
    )
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ws2_32;"
        "leveldb"
        "gmock"
        "gtest"
    )
else (TOMATODB_BUILD_TESTS)
    set(ALL_FILES
        ${Base}
        ${Character}
        ${Common__Common}
        ${Common__DataBase}
        ${Common__Net}
        ${Common__Packets}
        ${Main}
        ${Packets}
        ${Player}
        ${SMU}
        ${Worker}
        ${DB}
        ${DBLink}
        ${StdAfx}
        ${tinyxml}
    )
    set(ADDITIONAL_LIBRARY_DEPENDENCIES
        "ws2_32;"
        "leveldb"
    )
endif()


################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "stdafx.h" "stdafx.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE Server)

################################################################################
# Include directories
################################################################################

target_include_directories(${PROJECT_NAME} PUBLIC
	"${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Packets;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Net;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Character;"
	"${CMAKE_CURRENT_SOURCE_DIR}/."
	"${CMAKE_CURRENT_SOURCE_DIR}/DB"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../Common;"
	"${CMAKE_CURRENT_SOURCE_DIR}/tinyxml;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Packets;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Main;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Base;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Worker;"
	"${CMAKE_CURRENT_SOURCE_DIR}/Player;"
	"${CMAKE_CURRENT_SOURCE_DIR}/SMU;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../../Common/DataBase;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/include;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/third_party/json/single_include/nlohmann;"
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util;"
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
	"$<$<CONFIG:Debug>:"
		"_DEBUG"
	">"
	"$<$<CONFIG:Release>:"
		"_NDEBUG"
	">"
	"_CONSOLE;"
	${COMPILE_PLATFORM_NAME}
	"_TMT_SERVER;"
	"_TMT_CLIENT;"
	"_TMT_WORLD;"
	"TIXML_USE_STL;"
	"_MBCS"
)

################################################################################
# Dependencies
################################################################################

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_directories(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/build/engine/debug/"
    ">"
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/build/engine/release/"
    ">"
)