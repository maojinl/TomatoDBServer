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

enum WORKER_STATUS {
	WORKER_STATUS_SLEEP = 0,	//sleep status
	WORKER_STATUS_SELECT,		//waiting for load
	WORKER_STATUS_LOAD,			//loading
	WORKER_STATUS_INIT,			//init status
	WORKER_STATUS_RUNNING,		//running
};

enum WORKER_TYPE {
	WORKER_TYPE_INVALID = -1,
	WORKER_TYPE_DB_LOGIC,    // DB Logic worker
	WORKER_TYPE_NUMBERS
};

class Scene
{
public :
/////////////////////////////////////////////////////////////////////////////////
//��ײ���Դ����������
/////////////////////////////////////////////////////////////////////////////////
	Scene( WorkerID_t SceneID ) ;
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

	ScenePlayerManager*		GetScenePlayerManager(){ return m_pWorkerPlayerManager ; } ;
	ScenePlayerManager*		GetPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

	//��ȡ��ǰ����״̬
    INT GetSceneStatus() { return m_nSceneStatus; }
    //���õ�ǰ����״̬
    VOID SetSceneStatus(INT status) { m_nSceneStatus = status; }

    //��ȡ��ǰ�����ĳ���ID
    WorkerID_t SceneID() { return m_SceneID; };

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
	ScenePlayerManager*		m_pWorkerPlayerManager ;
	//��ǰ�����ȴ����յ��û�ָ��
	RecyclePlayerManager*	m_pRecyclePlayerManager;

        //��ǰ�����ĳ���ID
    WorkerID_t				m_SceneID;


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
