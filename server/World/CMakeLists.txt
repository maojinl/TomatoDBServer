set(PROJECT_NAME World)

################################################################################
# Source groups
################################################################################
set(Base
    "../Server/Base/Config.cpp"
    "../Server/Base/Config.h"
    "../Server/Base/File.cpp"
    "../Server/Base/File.h"
    "../Server/Base/FileDef.h"
    "../Server/Base/IDTable.cpp"
    "../Server/Base/IDTable.h"
    "../Server/Base/Ini.cpp"
    "../Server/Base/Ini.h"
    "../Server/Base/Log.cpp"
    "../Server/Base/Log.h"
    "../Server/Base/StrTable.cpp"
    "../Server/Base/StrTable.h"
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
    "../../Common/Chain.cpp"
    "../../Common/Chain.h"
    "../../Common/GameUtil.cpp"
    "../../Common/GameUtil.h"
    "../../Common/OResultDef.h"
    "../../Common/PacketDefine.h"
    "../../Common/PacketFactory.h"
    "../../Common/PacketFactoryManager.cpp"
    "../../Common/PacketFactoryManager.h"
    "../../Common/PlayerStatus.h"
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

set(Common__Packets
    "../../Common/Packets/GWAskMail.cpp"
    "../../Common/Packets/GWAskMail.h"
    "../../Common/Packets/GWSystemMsg.cpp"
    "../../Common/Packets/GWSystemMsg.h"
    "../../Common/Packets/WGMail.cpp"
    "../../Common/Packets/WGMail.h"
    "../../Common/Packets/WGSystemMsg.cpp"
    "../../Common/Packets/WGSystemMsg.h"
)
source_group("Common\\Packets" FILES ${Common__Packets})

set(Main
    "Main/Player.cpp"
    "Main/Player.h"
    "Main/PlayerManager.cpp"
    "Main/PlayerManager.h"
    "Main/PlayerPool.cpp"
    "Main/PlayerPool.h"
    "Main/ServerManager.cpp"
    "Main/ServerManager.h"
    "Main/ServerPlayer.cpp"
    "Main/ServerPlayer.h"
    "Main/ShareMemManager.cpp"
    "Main/ShareMemManager.h"
    "Main/World.cpp"
    "Main/World.h"
)
source_group("Main" FILES ${Main})

set(Packets
    "Packets/GWAskMailHandler.cpp"
    "Packets/GWSystemMsgHandler.cpp"
    "Packets/NullHandler.cpp"
)
source_group("Packets" FILES ${Packets})

set(SMU
    "../Server/SMU/ShareMemAO.cpp"
    "../Server/SMU/ShareMemAO.h"
    "../Server/SMU/SMUManager.cpp"
    "../Server/SMU/SMUManager.h"
)
source_group("SMU" FILES ${SMU})

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
    ${Common__Packets}
    ${Main}
    ${Packets}
    ${SMU}
    ${StdAfx}
)

################################################################################
# Target
################################################################################
add_executable(${PROJECT_NAME} ${ALL_FILES})

add_precompiled_header(${PROJECT_NAME} "stdafx.h" "stdafx.cpp")

use_props(${PROJECT_NAME} "${CMAKE_CONFIGURATION_TYPES}" "${DEFAULT_CXX_PROPS}")
set(ROOT_NAMESPACE World)


################################################################################
# Include directories
################################################################################
target_include_directories(${PROJECT_NAME} PUBLIC
    "${CMAKE_CURRENT_SOURCE_DIR}/WorldData"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Packets;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Main;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Server/Base;"
    "${CMAKE_CURRENT_SOURCE_DIR}/Packets;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../Server/SMU;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/DataBase;"
    "${CMAKE_CURRENT_SOURCE_DIR}/../../Common/Net;"
    "${CMAKE_CURRENT_SOURCE_DIR}/."
)

################################################################################
# Compile definitions
################################################################################
target_compile_definitions(${PROJECT_NAME} PRIVATE
    "$<$<CONFIG:Debug>:"
        "_DEBUG;"
    ">"
    "$<$<CONFIG:Release>:"
        "NDEBUG;"
    ">"
    "_JSF_WORLD;"
    "_JSF_SERVER"
    ${COMPILE_PLATFORM_NAME}
    "_CONSOLE;"
    "_MBCS"
)

################################################################################
# Dependencies
################################################################################
set(ADDITIONAL_LIBRARY_DEPENDENCIES
    "ws2_32"
)

target_link_libraries(${PROJECT_NAME} PRIVATE "${ADDITIONAL_LIBRARY_DEPENDENCIES}")