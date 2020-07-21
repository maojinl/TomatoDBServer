#ifndef __WORKER_H__
#define __WORKER_H__

#include "Type.h"
#include "WorkerPlayerManager.h"
#include "Performance.h"
#include "Rand.h"

class CFileDataMgr;
class SceneTimer;
class Packet;
class GamePlayer ;
class RecyclePlayerManager;
class User;

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

class Worker
{
public :
/////////////////////////////////////////////////////////////////////////////////
//��ײ���Դ����������
/////////////////////////////////////////////////////////////////////////////////
	Worker( WorkerID_t SceneID ) ;
	~Worker( ) ;

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
    //��� PlayerIDΪINVALID_ID_EX, �����Ϣ�ᱻ����ִ�У�PlayerΪnullptr��
    BOOL SendPacket(Packet* pPacket, PlayerID_t PlayerID,
                    UINT Flag = PF_NONE);

	WorkerPlayerManager*		GetWorkerPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	WorkerPlayerManager*		GetPlayerManager(){ return m_pWorkerPlayerManager ; } ;
	
	RecyclePlayerManager*	GetRecyclePlayerManager(){ return m_pRecyclePlayerManager; };

	BOOL			IsCanEnter( ) ;
	BOOL			IsFull( ) ;
	INT				CheckEnter( PlayerID_t PlayerID ) ;

	//��ȡ��ǰ����״̬
    INT GetWorkerStatus() { return m_nWorkerStatus; }
    //���õ�ǰ����״̬
    VOID SetWorkerStatus(INT status) { m_nWorkerStatus = status; }

    //��ȡ��ǰ�����ĳ���ID
    WorkerID_t WorkerID() { return m_WorkerID; };

    //�رյ�ǰ����
    BOOL CloseWorker();

    VOID SetWorkerType(INT type) { m_WorkerType = type; };
    INT GetWorkerType() const { return m_WorkerType; };

	BOOL BroadCast_Worker(Packet* pPacket);
	BOOL UserEnterWorker(User* pUser);
	VOID UserLeaveWorker(User* pUser);
protected :
    //��ǰ������״̬����SCENE_STATUS
    INT m_nWorkerStatus;

	//��ǰ�������û�Ⱥ����ģ��ָ��
	WorkerPlayerManager*		m_pWorkerPlayerManager ;
	//��ǰ�����ȴ����յ��û�ָ��
	RecyclePlayerManager*	m_pRecyclePlayerManager;

        //��ǰ�����ĳ���ID
    WorkerID_t				m_WorkerID;


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
    INT m_WorkerType;
    WORKER_PERFOR m_Perfor;  //�������
};

#endif
