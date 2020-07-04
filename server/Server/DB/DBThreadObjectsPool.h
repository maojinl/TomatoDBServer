#ifndef __DBTHREADOBJECTSPOOL_H__
#define __DBTHREADOBJECTSPOOL_H__

#include "Type.h"
#include "leveldb/write_batch.h"

using namespace leveldb;

namespace tomatodb
{
	class DBThreadObjectsPool
	{
	private:
		UINT threadsCount;
		WriteBatch* writeBatchs;
		static DBThreadObjectsPool* m_pDBThreadObjPool;

		DBThreadObjectsPool() :
			threadsCount(0),
			writeBatchs(nullptr)
		{
		};

		~DBThreadObjectsPool()
		{
			SAFE_DELETE_ARRAY(writeBatchs);
		};

	public:
		BOOL Init(UINT threads)
		{
			threadsCount = threads;
			writeBatchs = new WriteBatch[threadsCount];
			return TRUE;
		};

		WriteBatch& Get(UINT threadIndex)
		{
			assert(threadIndex < threadsCount);
			return writeBatchs[threadIndex];
		}

		static DBThreadObjectsPool* GetInstance() {
			//must be called firstly in main thread
			if (m_pDBThreadObjPool == NULL) {
				m_pDBThreadObjPool = new DBThreadObjectsPool();
			}
			return m_pDBThreadObjPool;
		}

		static void ReleaseInstance() {
			//must be called before ends in main thread
			SAFE_DELETE(m_pDBThreadObjPool);
		}
	};
}
#endif
