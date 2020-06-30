#include "stdafx.h"

#include "Scene.h"
#include "Log.h"
#include "Config.h"
#include "RecyclePlayerManager.h"
#include "PacketFactoryManager.h"
#include "ServerManager.h"
#include "TimeManager.h"
#include "FileDef.h"
#include "WorkerManager.h"
#include "GWSystemMsg.h"
#include "Performance.h"


Scene::Scene(WorkerID_t SceneID) {
  __ENTER_FUNCTION
  m_nSceneStatus = WORKER_STATUS_SLEEP;
  m_SceneID = SceneID;
  m_pWorkerPlayerManager = new ScenePlayerManager;
  Assert(m_pWorkerPlayerManager);
  m_pWorkerPlayerManager->SetSceneID(SceneID);

  m_pRecyclePlayerManager = new RecyclePlayerManager();
  Assert(m_pRecyclePlayerManager);
  m_pRecyclePlayerManager->SetSceneID(SceneID);

  m_PacketQue = new ASYNC_PACKET[MAX_CACHE_SIZE];
  Assert(m_PacketQue);
  m_QueSize = MAX_CACHE_SIZE;
  m_Head = 0;
  m_Tail = 0;

  m_SceneType = WORKER_TYPE_DB_LOGIC;
  m_Perfor.m_WorkerID = SceneID;

  m_pPacket_SysMsg = new GWSystemMsg;

  __LEAVE_FUNCTION
}

Scene::~Scene() {
  __ENTER_FUNCTION

  SAFE_DELETE(m_pPacket_SysMsg);

  SAFE_DELETE(m_pWorkerPlayerManager);
  SAFE_DELETE(m_pRecyclePlayerManager);
  SAFE_DELETE_ARRAY(m_PacketQue);

  __LEAVE_FUNCTION
}

BOOL Scene::Init() {
  __ENTER_FUNCTION

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::Tick() {
  __ENTER_FUNCTION

  BOOL ret = FALSE;

  if (StatusLogic() == FALSE) {
    MySleep(1000);
    return TRUE;
  }
  m_Perfor.m_aPerfor[SPT_TICK_LOGIC]++;

  //网络处理
  _MY_TRY {
    ret = m_pWorkerPlayerManager->Select();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_SELECT]++;

  _MY_TRY {
    ret = m_pWorkerPlayerManager->ProcessExceptions();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_PROCESSEXCEPTIONS]++;

  _MY_TRY {
    ret = m_pWorkerPlayerManager->ProcessInputs();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_PROCESSINPUTS]++;

  _MY_TRY {
    ret = m_pWorkerPlayerManager->ProcessOutputs();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_PROCESSOUTPUTS]++;

  //消息处理
  _MY_TRY {
    ret = m_pWorkerPlayerManager->ProcessCommands();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_PROCESSCOMMANDS]++;

  //缓存消息处理
  _MY_TRY { ProcessCacheCommands(); }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_PROCESSCACHECOMMANDS]++;

  //逻辑处理
  _MY_TRY {
    ret = HeartBeat();
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_TICK_HEARTBEAT]++;

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::StatusLogic() {
  __ENTER_FUNCTION

  switch (m_nSceneStatus) {
    case WORKER_STATUS_SLEEP: {
      return FALSE;
    } break;
    case WORKER_STATUS_SELECT: {
      return FALSE;
    } break;
    case WORKER_STATUS_LOAD: {
      return FALSE;
    } break;
    case WORKER_STATUS_INIT: {
      return FALSE;
    } break;
    case WORKER_STATUS_RUNNING: {
      return TRUE;
    } break;
    default: {
      Assert(FALSE);
    } break;
  };

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::HeartBeat() {
  __ENTER_FUNCTION

  BOOL ret;

  UINT uTime = g_pTimeManager->CurrentTime();
  g_pTimeManager->SetTime();

  _MY_TRY {
    ret = m_pWorkerPlayerManager->HeartBeat(uTime);
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_HEARTBEAT_SCENEPLAYERMANAGER]++;

  //用户回收处理
  _MY_TRY {
    ret = m_pRecyclePlayerManager->HeartBeat(uTime);
    Assert(ret);
  }
  _MY_CATCH { SaveCodeLog(); }
  m_Perfor.m_aPerfor[SPT_HEARTBEAT_RECYCLEPLAYERMANAGER]++;

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::ProcessCacheCommands() {
  __ENTER_FUNCTION

  BOOL ret = FALSE;

  for (UINT i = 0; i < m_QueSize; i++) {
    Packet* pPacket = NULL;
    PlayerID_t PlayerID;
    UINT Flag;

    ret = RecvPacket(pPacket, PlayerID, Flag);
    if (!ret) break;

    Assert(pPacket);

    if (Flag == PF_REMOVE) {
      g_pPacketFactoryManager->RemovePacket(pPacket);
      continue;
    }

    BOOL bNeedRemove = TRUE;

    if (PlayerID == INVALID_ID_EX) {
      UINT uret;
      _MY_TRY { uret = pPacket->Execute(NULL); }
      _MY_CATCH {
        SaveCodeLog();
        uret = PACKET_EXE_ERROR;
      }
      if (uret == PACKET_EXE_ERROR) {
      } else if (uret == PACKET_EXE_BREAK) {
      } else if (uret == PACKET_EXE_CONTINUE) {
      } else if (uret == PACKET_EXE_NOTREMOVE) {
        bNeedRemove = FALSE;
      } else if (uret == PACKET_EXE_NOTREMOVE_ERROR) {
        bNeedRemove = FALSE;
      }
    } else {
      _MY_TRY {
        Player* pPlayer = g_pPlayerPool->GetPlayer(PlayerID);
        Assert(pPlayer);

        UINT uret;
        _MY_TRY { uret = pPacket->Execute(pPlayer); }
        _MY_CATCH {
          SaveCodeLog();
          uret = PACKET_EXE_ERROR;
        }
        if (uret == PACKET_EXE_ERROR) {
          GetScenePlayerManager()->RemovePlayer(pPlayer, "ERROR in executing package.", TRUE);
          MovePacket(PlayerID);
        } else if (uret == PACKET_EXE_BREAK) {
        } else if (uret == PACKET_EXE_CONTINUE) {
        } else if (uret == PACKET_EXE_NOTREMOVE) {
          bNeedRemove = FALSE;
        } else if (uret == PACKET_EXE_NOTREMOVE_ERROR) {
          bNeedRemove = FALSE;

          GetScenePlayerManager()->RemovePlayer(pPlayer,
                                                "Executed and disconnected.", TRUE);
          MovePacket(PlayerID);
        }
      }
      _MY_CATCH { SaveCodeLog(); }
    }

    if (bNeedRemove) g_pPacketFactoryManager->RemovePacket(pPacket);
  }

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::ResizeCache() {
  __ENTER_FUNCTION

  ASYNC_PACKET* pNew = new ASYNC_PACKET[m_QueSize + MAX_CACHE_SIZE];
  if (pNew == NULL) return FALSE;

  memcpy(pNew, &(m_PacketQue[m_Head]),
         sizeof(ASYNC_PACKET) * (m_QueSize - m_Head));
  if (m_Head != 0) {
    memcpy(&(pNew[m_QueSize - m_Head]), &(m_PacketQue[0]),
           sizeof(ASYNC_PACKET) * (m_Head));
  }

  memset(m_PacketQue, 0, sizeof(ASYNC_PACKET) * m_QueSize);
  SAFE_DELETE_ARRAY(m_PacketQue);
  m_PacketQue = pNew;

  m_Head = 0;
  m_Tail = m_QueSize;
  m_QueSize = m_QueSize + MAX_CACHE_SIZE;

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}

BOOL Scene::SendPacket(Packet* pPacket, PlayerID_t PlayerID, UINT Flag) {
  __ENTER_FUNCTION

  m_pWorkerPlayerManager->Lock();

  if (m_PacketQue[m_Tail].m_pPacket) {  //缓冲区满
    BOOL ret = ResizeCache();
    Assert(ret);
  }

  m_PacketQue[m_Tail].m_pPacket = pPacket;
  m_PacketQue[m_Tail].m_PlayerID = PlayerID;
  m_PacketQue[m_Tail].m_Flag = Flag;

  m_Tail++;
  if (m_Tail >= m_QueSize) m_Tail = 0;

  m_pWorkerPlayerManager->Unlock();
  return TRUE;

  __LEAVE_FUNCTION

  m_pWorkerPlayerManager->Unlock();
  return FALSE;
}

BOOL Scene::MovePacket(PlayerID_t PlayerID) {
  __ENTER_FUNCTION

  m_pWorkerPlayerManager->Lock();

  UINT Cur = m_Head;

  for (UINT i = 0; i < m_QueSize; i++) {
    if (m_PacketQue[Cur].m_pPacket == NULL) break;

    if (m_PacketQue[Cur].m_PlayerID == PlayerID) {
      m_PacketQue[Cur].m_Flag = PF_REMOVE;
    }

    Cur++;
    if (Cur >= m_QueSize) Cur = 0;
  }

  m_pWorkerPlayerManager->Unlock();
  return TRUE;

  __LEAVE_FUNCTION

  m_pWorkerPlayerManager->Unlock();
  return FALSE;
}

BOOL Scene::RecvPacket(Packet*& pPacket, PlayerID_t& PlayerID, UINT& Flag) {
  __ENTER_FUNCTION

  m_pWorkerPlayerManager->Lock();

  if (m_PacketQue[m_Head].m_pPacket == NULL) {  //no package in the buffer
    m_pWorkerPlayerManager->Unlock();
    return FALSE;
  }

  pPacket = m_PacketQue[m_Head].m_pPacket;
  PlayerID = m_PacketQue[m_Head].m_PlayerID;
  Flag = m_PacketQue[m_Head].m_Flag;

  m_PacketQue[m_Head].m_pPacket = NULL;
  m_PacketQue[m_Head].m_PlayerID = INVALID_ID;
  m_PacketQue[m_Head].m_Flag = PF_NONE;

  m_Head++;
  if (m_Head >= m_QueSize) m_Head = 0;

  m_pWorkerPlayerManager->Unlock();
  return TRUE;

  __LEAVE_FUNCTION

  m_pWorkerPlayerManager->Unlock();
  return FALSE;
}

BOOL Scene::CloseScene() {
  __ENTER_FUNCTION

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}


BOOL Scene::IsCanEnter( )
{
__ENTER_FUNCTION

	INT iCount = m_pWorkerPlayerManager->GetCount( ) ;
	if( iCount > FD_SETSIZE)
	{
		return FALSE ;
	}

	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL Scene::IsFull( )
{
__ENTER_FUNCTION

	INT iCount = m_pWorkerPlayerManager->GetCount( ) ;
	if( iCount >= FD_SETSIZE )
	{
		return TRUE ;
	}

	return FALSE ;

__LEAVE_FUNCTION

	return TRUE ;
}

INT Scene::CheckEnter( PlayerID_t PlayerID )
{
__ENTER_FUNCTION
	return 1 ;
__LEAVE_FUNCTION
	return 0 ;
}

BOOL Scene::BroadCast_Scene(Packet* pPacket) {
  __ENTER_FUNCTION

  if (m_pWorkerPlayerManager != nullptr) {
    UINT nPlayerCount = m_pWorkerPlayerManager->GetPlayerNumber();
    for (UINT i = 0; i < nPlayerCount; i++) {
      PlayerID_t* PlayerIDs = m_pWorkerPlayerManager->GetPlayers();
      if (PlayerIDs[i] == INVALID_ID) continue;
      Player* pPlayer = g_pPlayerPool->GetPlayer(PlayerIDs[i]);
      if (pPlayer)
      {
          pPlayer->SendPacket( pPacket ) ;
      }
    }  // end for
  }  // end if

  return TRUE;

  __LEAVE_FUNCTION

  return FALSE;
}



















