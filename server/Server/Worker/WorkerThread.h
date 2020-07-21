#ifndef __WORKERTHREAD_H__
#define __WORKERTHREAD_H__

#include "Type.h"
#include "Thread.h"
#include "Worker.h"

#define MAX_WORKER_PER_THREAD 4

class WorkerThread : public Thread
{
public:
	WorkerThread();
	~WorkerThread();

	virtual VOID	run();

	virtual VOID	stop() { m_Active = FALSE; };

	BOOL			IsActive(){ return m_Active; };

	VOID			Quit();

	BOOL			AddWorker(Worker* pWorker);

private:
	Worker*		m_apWorker[MAX_WORKER_PER_THREAD];
	INT			m_nWorkerCount;
	BOOL		m_Active;
};
#endif
