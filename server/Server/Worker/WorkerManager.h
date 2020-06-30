#ifndef __WORKERMANAGER_H__
#define __WORKERMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Scene.h"

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
	Scene*			GetScene( WorkerID_t WorkerID ) ;
	//���ݳ�����ȡ�ó���������Ϣ
	_WORKER_DATA* GetWorkerInfo( WorkerID_t WorkerID) ;
	//���ݳ������жϴ˳����Ƿ��ڵ�ǰ�������˳�����
	BOOL			IsInCurServer( WorkerID_t WorkerID) ;
	//���ݳ������жϴ˳����Ƿ񱻵�ǰ�������ϵ�ĳ���������˳�����
	BOOL			IsInCurMachine( WorkerID_t WorkerID) ;

	//��ϵͳ�����һ������
	BOOL			AddScene( Scene* pScene ) ;
	//��һ��������ϵͳ��ɾ��
	BOOL			DelScene( WorkerID_t WorkerID) ;

	//����ĳ�������е�����
	VOID			SetScenePlayerCount( WorkerID_t WorkerID, INT count ){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return ;
		m_aScenePlayerCount[WorkerID] = count ;
	};
	//��ȡĳ�������е�����
	INT				GetScenePlayerCount( WorkerID_t WorkerID){
		if(WorkerID < 0 && WorkerID >= MAX_WORKER) return 0 ;
		return m_aScenePlayerCount[WorkerID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;
	WorkerID_t		GetSpecialSceneIDFromCurServer( ) ;//ȡ��һ���ڵ�ǰServer�ϵ���Ϸ�߼�����
    BOOL BroadCast_Scene(Packet* pMsg);

private :
	Scene*			m_pWorker[MAX_WORKER] ;			//��������ָ��
	INT				m_aScenePlayerCount[MAX_WORKER] ;//����������
	UINT			m_Count ;//��ǰϵͳ�еĳ�������

	INT				m_nTotalPlayerCount ;//������Ϸ����������ܺ�
};

extern WorkerManager* g_pWorkerManager ;


#endif
