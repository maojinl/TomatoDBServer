#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Worker.h"

/////////////////////////////////////////////////////////////////////////////////
// WorkerManager
/////////////////////////////////////////////////////////////////////////////////
class WorkerManager
{
public :
	WorkerManager( ) ;
	~WorkerManager( ) ;

	//��ʼ���ӿ�
	BOOL			Init( UINT MaxSceneCount = MAX_WORKER) ;

	//���ݳ�����ȡ�ó�������ָ��
	Worker*			GetWorker( WorkerID_t WorkerID ) ;
	//���ݳ�����ȡ�ó���������Ϣ
	_WORKER_DATA* GetWorkerInfo( WorkerID_t WorkerID) ;
	//���ݳ������жϴ˳����Ƿ��ڵ�ǰ�������˳�����
	BOOL			IsInCurServer( WorkerID_t WorkerID) ;
	//���ݳ������жϴ˳����Ƿ񱻵�ǰ�������ϵ�ĳ���������˳�����
	BOOL			IsInCurMachine( WorkerID_t WorkerID) ;

	//��ϵͳ�����һ������
	BOOL			AddWorker(Worker* pScene ) ;
	//��һ��������ϵͳ��ɾ��
	BOOL			DelWorker( WorkerID_t WorkerID) ;

	//����ĳ�������е�����
	VOID			SetScenePlayerCount( WorkerID_t WorkerID, INT count ){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return ;
		m_aWorkerPlayerCount[WorkerID] = count ;
	};
	//��ȡĳ�������е�����
	INT				GetScenePlayerCount( WorkerID_t WorkerID){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return 0 ;
		return m_aWorkerPlayerCount[WorkerID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;

    BOOL BroadCast_Worker(Packet* pMsg);

private :
	Worker*			m_pWorker[MAX_WORKER] ;			//��������ָ��
	INT				m_aWorkerPlayerCount[MAX_WORKER] ;//����������
	UINT			m_Count ;//��ǰϵͳ�еĳ�������

	INT				m_nTotalPlayerCount ;//������Ϸ����������ܺ�
};

extern WorkerManager* g_pWorkerManager ;


#endif
