set(PROJECT_NAME ShareMemory)

################################################################################
# Source groups
################################################################################
set(Base
    "../Server/Base/Config.cpp"
    "../Server/Base/Config.h"
    "../Server/Base/Ini.cpp"
    "../Server/Base/Ini.h"
    "../Server/Base/Log.cpp"
    "../Server/Base/Log.h"
    "../Server/Base/Thread.cpp"
    "../Server/Base/Thread.h"
    "../Server/Base/TimeManager.cpp"
    "../Server/Base/TimeManager.h"
)
source_group("Base" FILES ${Base})

set(Common
    "../../Common/Assertx.cpp"
    "../../Common/Assertx.h"
    "../../Common/BaseType.h"
    "../../Common/GameDefine.h"
    "../../Common/GameUtil.cpp"
    "../../Common/GameUtil.h"
    "../../Common/KeyDog.h"
    "../../Common/Rand.cpp"
    "../../Common/Rand.h"
    "../../Common/ShareMemAPI.cpp"
    "../../Common/ShareMemAPI.h"
    "../../Common/Type.h"
)
source_group("Common" FILES ${Common})

set(Common__Database
    "../../Common/DataBase/TLBB_DBC.cpp"
    "../../Common/DataBase/TLBB_DBC.h"
)
source_group("Common\\Database" FILES ${Common__Database})

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

set(DataBase
    "DB/ShareDBManager.cpp"
    "DB/ShareDBManager.h"
)
source_group("DataBase" FILES ${DataBase})

set(Main
    "Main/CommandThread.cpp"
    "Main/CommandThread.h"
    "Main/ShareMemory.cpp"
    "Main/ShareMemory.h"
)
source_group("Main" FILES ${Main})

set(ShareData
    "../Server/SMU/ShareMemAO.cpp"
    "../Server/SMU/ShareMemAO.h"
    "../Server/SMU/SMUManager.cpp"
    "../Server/SMU/SMUManager.h"
    "ShareData/SMULogicManager.cpp"
    "ShareData/SMULogicManager.h"
)
source_group("ShareData" FILES ${ShareData})

set(StdAfx
    "stdafx.cpp"
    "stdafx.h"
)
source_group("StdAfx" FILES ${StdAfx})

set(ALL_FILES
    ${Base}
    ${Common}
    ${Common__Database}
    ${Common__Net}
    ${DataBase}
    ${Main}
    ${ShareData}
    ${StdAfx}
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
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Server/Base;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Server/SMU;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Main;"
    "${CMAKE_CURRENT_SOURCE_DIR}/DB;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Net;"
    "${CMAKE_CURRENT_SOURCE_DIR}/.;"
    "${CMAKE_CURRENT_SOURCE_DIR}/ShareData"
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
    "ws2_32"
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")