/////////////////////////////////////////////////////////////////////////////////
//�ļ�����Scene.h
//������������Ϸ����������������Ϸ�߼����ܵ�ִ����
//			ӵ����������Ϸ�����е���Ϸ�߼����ݣ��ж�����ִ���߳�������������ִ��
//			�������������ڳ����еĿͻ����������ӣ��ܹ���������ͻ���������Ϣ
//�޸ļ�¼��2005-3-23����
//�޸ļ�¼��2005-11-8�������ļ��ṹ��֮�����жԳ������޸Ķ���Ҫ���¼�¼
//�޸ļ�¼��2005-11-14���ӳ������¼���Ӧ
//�޸ļ�¼��2005-11-15���ӳ����ĸ���ϵͳ������ݺͽӿ�
//�޸ļ�¼��2006-2-7����̯λ������
/////////////////////////////////////////////////////////////////////////////////

#ifndef __SCENE_H__
#define __SCENE_H__

#include "Type.h"
#include "ScenePlayerManager.h"
#include "Performance.h"
#include "Rand.h"

class CFileDataMgr;
class SceneTimer;
class Packet;
class GamePlayer ;
class RecyclePlayerManager;

enum SCENE_STATUS {
  SCENE_STATUS_SLEEP = 0,  //û�����õĳ���״̬����û�г������ݡ��������ߵ�״̬
  SCENE_STATUS_SELECT,   //���������������ڴ�װ��״̬
  SCENE_STATUS_LOAD,     //��Ҫ��ȡ������Դ�ļ���״̬
  SCENE_STATUS_INIT,     //��Ҫ��ʼ�������ݵ�״̬
  SCENE_STATUS_RUNNING,  //�������еĳ���״̬
};

enum SCENE_TYPE {
  SCENE_TYPE_INVALID = -1,
  SCENE_TYPE_GAMELOGIC,    // ��ͨ��Ϸ�߼�����
  SCENE_TYPE_COPY,         // ����
  SCENE_TYPE_BATTLEFIELD,  // ս��
  SCENE_TYPE_ARENA,        // ��̨
  SCENE_TYPE_CIT,          // ��ͨ���иۿ�
  SCENE_TYPE_PIRATE_CIT,   // �����ۿ�
  SCENE_TYPE_HOUSE,        // ������

  SCENE_TYPE_NUMBERS
};

class Scene
{
public :
/////////////////////////////////////////////////////////////////////////////////
//��ײ���Դ����������
/////////////////////////////////////////////////////////////////////////////////
	Scene( SceneID_t SceneID ) ;
	~Scene( ) ;

	//��ʼ��
	BOOL					Init( ) ;
	//������ִ�нӿڣ��˽ӿڻᱻ�����̶߳�ʱ����
	BOOL					Tick( ) ;
	//���Ƶ�ǰ����״̬���߼��ӿ�
	BOOL					StatusLogic( ) ;

/////////////////////////////////////////////////////////////////////////////////
//��Ϸ�߼��ײ㴦��
/////////////////////////////////////////////////////////////////////////////////
protected :
	//�������߼��ӿ�
	BOOL					HeartBeat( ) ;

	//�������Ļ�����Ϣ
	BOOL					ProcessCacheCommands( ) ;

	//��ȡ��ǰ����������Ϣ
	BOOL					RecvPacket( Packet*& pPacket, PlayerID_t& PlayerID, UINT& Flag ) ;

	//���µ��������С
	BOOL					ResizeCache( ) ;

	BOOL					MovePacket( PlayerID_t PlayerID ) ;
public :
    //��˳���������Ϣ
    //�˽ӿ�֧������ͬ�����������ڲ�ͬ�߳��ڵ���
    //�˽ӿ��ǲ�ͬ������ͨѶ��Ψһ�ӿ�
    //ע�⣺pPacket��Ϣ��Ҫ��g_pPacketFactoryManager�����������������ɾ��
    //��� PlayerIDΪINVALID_ID, ��㲥����Ϣ����������
    //��� PlayerIDΪINVALID_ID_EX, �����Ϣ�ᱻ����ִ�У�PlayerΪNULL��
    BOOL SendPacket(Packet* pPacket, PlayerID_t PlayerID,
                    UINT Flag = PF_NONE);

	ScenePlayerManager*		GetScenePlayerManager(){ return m_pScenePlayerManager ; } ;
	ScenePlayerManager*		GetPlayerManager(){ return m_pScenePlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

	//��ȡ��ǰ����״̬
    INT GetSceneStatus() { return m_nSceneStatus; }
    //���õ�ǰ����״̬
    VOID SetSceneStatus(INT status) { m_nSceneStatus = status; }

    //��ȡ��ǰ�����ĳ���ID
    SceneID_t SceneID() { return m_SceneID; };

    //�رյ�ǰ����
    BOOL CloseScene();

		//�жϵ�ǰ�����Ƿ�Ϊ�������� ��ͨ��Ϸ���� ���г���, enum SCENE_TYPE
    VOID SetSceneType(INT type) { m_SceneType = type; };
    INT GetSceneType() const { return m_SceneType; };

	BOOL BroadCast_Scene(Packet* pPacket);

protected :
    //��ǰ������״̬����SCENE_STATUS
    INT m_nSceneStatus;

	//��ǰ�������û�Ⱥ����ģ��ָ��
	ScenePlayerManager*		m_pScenePlayerManager ;
	//��ǰ�����ȴ����յ��û�ָ��
	RecyclePlayerManager*	m_pRecyclePlayerManager;

        //��ǰ�����ĳ���ID
    SceneID_t				m_SceneID;


private :
	//��ǰ��������Ϣ����
	ASYNC_PACKET*			m_PacketQue ;
	UINT					m_QueSize ;
	UINT					m_Head ;
	UINT					m_Tail ;
	_100_PER_RANDOM_TABLE	m_Rand100 ; //ÿ���߳�Ψһ�������������
public:
	// �������Ĺ��ñ���
	Packet					*m_pPacket_SysMsg; //ϵͳ�㲥;
	TID						m_ThreadID ;//�������̺߳�
    INT m_SceneType;
    SCENE_PERFOR m_Perfor;  //�������
};

#endif
