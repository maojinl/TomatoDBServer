#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__

#include "Type.h"
#include "Thread.h"
#include "Worker.h"

#define MAX_WORKER_PER_THREAD 128

//�����߳�
//ÿ��������һ���������߳�������ִ��
class WorkerThread : public Thread
{
public :
	WorkerThread( ) ;
	~WorkerThread( ) ;

	//�߳�ִ����ѭ��
	virtual VOID	run( ) ;

	//ִֹͣ��
	//���ô˽ӿں��������߳̾���ֹͣ����������һ��ѭ������ʱ�˳�
	virtual VOID	stop( ) { m_Active = FALSE ; } ;

	//�жϵ�ǰ�߳��Ƿ���Ч�������Ч�����˳�ѭ��
	BOOL			IsActive( ){ return m_Active ; } ;

	VOID			Quit( ) ;

	BOOL			AddWorker( Worker* pScene ) ;

private :
	Worker*		m_apWorker[MAX_WORKER_PER_THREAD] ;
	INT			m_nWorkerCount ;
	BOOL		m_Active ;



};




#endif
