set(PROJECT_NAME Server)

################################################################################
# Source groups
################################################################################
set(Base
    "Base/Config.cpp"
    "Base/Config.h"
    "Base/File.cpp"
    "Base/File.h"
    "Base/FileDef.h"
    "Base/IDTable.cpp"
    "Base/IDTable.h"
    "Base/Ini.cpp"
    "Base/Ini.h"
    "Base/Log.cpp"
    "Base/Log.h"
    "Base/StrTable.cpp"
    "Base/StrTable.h"
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
    "../../Common/CrashCatch.h"
    "../../Common/FileDataMgr.cpp"
    "../../Common/FileDataMgr.h"
    "../../Common/GameDefine.h"
    "../../Common/GameUtil.cpp"
    "../../Common/GameUtil.h"
    "../../Common/KeyDog.h"
    "../../Common/OResultDef.h"
    "../../Common/PacketDefine.h"
    "../../Common/PacketFactory.h"
    "../../Common/PacketFactoryManager.cpp"
    "../../Common/PacketFactoryManager.h"
    "../../Common/PlayerStatus.h"
    "../../Common/Rand.cpp"
    "../../Common/Rand.h"
    "../../Common/ResultDefine.h"
    "../../Common/ShareMemAPI.cpp"
    "../../Common/ShareMemAPI.h"
    "../../Common/Type.h"
)
source_group("Common\\Common" FILES ${Common__Common})

set(Common__DataBase
    "../../Common/DataBase/TLBB_DBC.cpp"
    "../../Common/DataBase/TLBB_DBC.h"
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
    "../../Common/Packets/CGEnterScene.cpp"
    "../../Common/Packets/CGEnterScene.h"
    "../../Common/Packets/GCEnterScene.cpp"
    "../../Common/Packets/GCEnterScene.h"
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
    "Main/WorldManager.cpp"
    "Main/WorldManager.h"
)
source_group("Main" FILES ${Main})

set(Packets
    "Packets/CGEnterSceneHandler.cpp"
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
    "Worker/Scene.cpp"
    "Worker/Scene.h"
    "Worker/WorkerManager.cpp"
    "Worker/WorkerManager.h"
    "Worker/ScenePlayerManager.cpp"
    "Worker/ScenePlayerManager.h"
    "Worker/SceneThread.cpp"
    "Worker/SceneThread.h"
)
source_group("Worker" FILES ${Worker})

set(DB
	"DB/AdminDB.cpp"
    "DB/AdminDB.h"
    "DB/DataBaseManager.cpp"
    "DB/DataBaseManager.h"
    "DB/DataBaseObject.h"
)
source_group("DB" FILES ${DB})

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
    ${StdAfx}
    ${tinyxml}
)

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
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/include"
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/third_party/json/single_include/nlohmann"
	"${CMAKE_CURRENT_SOURCE_DIR}/../engine/util"
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
	"_JSF_SERVER;"
	"_JSF_CLIENT;"
	"_JSF_WORLD;"
	"TIXML_USE_STL;"
	"_MBCS"
)

################################################################################
# Compile and link options
################################################################################


################################################################################
# Dependencies
################################################################################

set(ADDITIONAL_LIBRARY_DEPENDENCIES
	"$<$<CONFIG:Debug>:"
		"CrashCatch"
	">"
	"ws2_32;"
	"leveldb"
)
target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")
target_link_directories(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../engine/build/debug/"
    ">"
    "$<$<CONFIG:Release>:"
        "${CMAKE_CURRENT_SOURCE_DIR}/../engine/build/release/"
    ">"
)