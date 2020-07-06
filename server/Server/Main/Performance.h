/////////////////////////////////////////////////////////////////////////////////
//�ļ�����Performance.h
//���������������ͳ��ϵͳ�и���ģ��ִ��Ч�ʼ��������
//�޸ļ�¼��
/////////////////////////////////////////////////////////////////////////////////

#ifndef __PERFORMANCE_H__
#define __PERFORMANCE_H__

#include "Type.h"

#define MAX_PERFOR_SIZE 256

enum SCENE_PERFOR_TYPE
{
	SPT_TICK_LOGIC = 0 ,
	SPT_TICK_SELECT ,
	SPT_TICK_PROCESSEXCEPTIONS ,
	SPT_TICK_PROCESSINPUTS ,
	SPT_TICK_PROCESSOUTPUTS ,
	SPT_TICK_PROCESSCOMMANDS ,
	SPT_TICK_PROCESSCACHECOMMANDS ,
	SPT_TICK_HEARTBEAT ,

	SPT_HEARTBEAT_CLOSELOGIC ,
	SPT_HEARTBEAT_SCENETIMER ,
	SPT_HEARTBEAT_WORKERPLAYERMANAGER ,
	SPT_HEARTBEAT_HUMANMANAGER ,
	SPT_HEARTBEAT_MONSTERMANAGER ,
	SPT_HEARTBEAT_PETMANAGER ,
	SPT_HEARTBEAT_ITEMBOXMANAGER ,
	SPT_HEARTBEAT_SPECIALMANANGER ,
	SPT_HEARTBEAT_GROWPOINTGROUP ,
	SPT_HEARTBEAT_CHATPIPE ,
	SPT_HEARTBEAT_PLAYERSHOP, 
	SPT_HEARTBEAT_SCENETIMERS ,
	SPT_HEARTBEAT_RECYCLEPLAYERMANAGER ,
	SPT_HEARTBEAT_BATTLESTAGEMANAGER ,

	SPT_NUMBER ,
};

struct WORKER_PERFOR
{
	UINT			m_aPerfor[SPT_NUMBER];
	WorkerID_t		m_WorkerID;

	WORKER_PERFOR( )
	{
		m_WorkerID = INVALID_ID ;
		for( INT i=0; i<SPT_NUMBER; i++ )
		{
			m_aPerfor[i] = 0 ;
		}
	}
};


class PerformanceManager
{
public :
	PerformanceManager() ;
	~PerformanceManager() ;

	VOID			CleanUp( ) ;

	BOOL			Init( ) ;//��ʼ��

	BOOL			HeartBeat( UINT uTime ) ;//�����߼�����

	INT				Scene2Index( WorkerID_t sceneid ) ;//������ӳ�䵽�������ݿ�����

	VOID			CompareScenePerformance( INT index ) ;//����һ��������������Ϣ


public :
	INT				m_PerforCount ;
	WORKER_PERFOR	m_aPerforData[MAX_PERFOR_SIZE] ;
	INT				m_aHash[MAX_WORKER] ;

	CMyTimer		m_OperateTime ;

};

extern PerformanceManager* g_pPerformanceManager ;

class ShareMemoryNotifyer
{
public:
	ShareMemoryNotifyer(){};
	~ShareMemoryNotifyer(){};
	
	BOOL		HeartBeat(UINT uTime);

};

extern ShareMemoryNotifyer g_ShareMemNotifyer;

#endif
