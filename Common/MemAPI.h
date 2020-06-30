#ifndef MEM_API_H
#define MEM_API_H

#define MEMAPI extern "C"  __declspec(dllexport) 

#pragma pack(push)
#pragma pack(1)

typedef struct _MEMINITINFO
{
	int nMaxSize;
	int nSysMaxIdleCount;// 缺省每个系统MemPool最大空闲缓冲数量
	int nSysMaxIdleTime; // 缺省每个系统MemPool最大空闲时间, 单位: 毫秒	
	_MEMINITINFO()
	{
		nMaxSize = 1024*8;
		nSysMaxIdleCount = 128;
		nSysMaxIdleTime = 60000;		
	}
}MEMINITINFO;
typedef MEMINITINFO* LPMEMINITINFO;

typedef struct _POOLINFO
{	
	bool bNull;
	int nMaxIdleCount;		// 最大空闲数量	
	int nMaxIdleTime;		// 最大空闲时间
	int nUsing;				// 当前正在使用数量
	int nIdle;				// 当前的空闲数量
	int nApplyCount;		// 申请缓冲次数
	int nReleaseCount;		// 释放缓冲次数	
	int nNewCount;			// 释放物理内存的次数   	
	int nDeleteCount;		// 申请物理内存的次数
	int nIdleTimeCount;		// 空闲超时数量
}POOLINFO;
typedef POOLINFO* LPPOOLINFO;

typedef struct _MEMBUFINFO
{
	int m_nNewSize;	    // 申请的物理内存数量（单位字节）	
	int m_nApplyCount;	// 申请缓冲的次数
	int m_nReleaseCount;// 释放缓冲的数量
	int m_nNewCount;	// 申请分配物理内存的次数
	int m_nDeleteCount; // 释放分配物理内存的次数	
	int m_nIdleTimeOutCount;// MemPool超过最大空闲超时的次数
}MEMBUFINFO;
typedef MEMBUFINFO* LPMEMBUFINFO;

// 初始化内存缓冲结构
MEMAPI int MMSysInit(LPMEMINITINFO pMemInitInfo);
// 周期性调用，优化内存缓冲
MEMAPI void MMSysCheck();	
// 关闭实时内存数据库
MEMAPI int MMSysDestroy();

// 设置缓冲
MEMAPI int MMSetPool(int nItem, int nMaxIdleCount, int nMaxIdleTime);
MEMAPI bool MMGetPoolInfo(int nItem, LPPOOLINFO pPoolInfo);
MEMAPI int MMReleasePoolIdle(int nItem, int nReleaseIdle);
MEMAPI void MMGetMngInfo(LPMEMBUFINFO pMemBufInfo);

MEMAPI void* MMAlloc(int nSize);
MEMAPI void MMFree(void* pAddr, int nSize);

#pragma pack(pop)

#endif