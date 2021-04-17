// stdafx.h

#pragma once


#ifdef __WINDOWS__
#define WIN32_LEAN_AND_MEAN
#include <tchar.h>
#endif


#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <malloc.h>
#include <string.h>
#include <map>
#include "stdarg.h"

#include "BaseType.h"
#include "Type.h"
#include "Config.h"
#include "FileDef.h"
#include "Ini.h"
#include "Log.h"
#include "Thread.h"
#include "File.h"
#include "TimeManager.h"
#include "Packet.h"
#include "PacketFactory.h"

#include "SocketInputStream.h"
#include "SocketOutputStream.h"

#include "ClientManager.h"
#include "WorkerManager.h"
#include "ThreadManager.h"
#include "PlayerPool.h"
#include "PacketFactoryManager.h"
#include "ServerManager.h"
#include "MachineManager.h"
#include "GUIDManager.h"
#include "Worker.h"
#include "GamePlayer.h"
#include "tinyxml.h"
#include "Obj_Human.h"