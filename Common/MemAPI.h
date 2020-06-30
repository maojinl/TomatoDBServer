#ifndef MEM_API_H
#define MEM_API_H

#define MEMAPI extern "C"  __declspec(dllexport) 

#pragma pack(push)
#pragma pack(1)

typedef struct _MEMINITINFO
{
	int nMaxSize;
	int nSysMaxIdleCount;// ȱʡÿ��ϵͳMemPool�����л�������
	int nSysMaxIdleTime; // ȱʡÿ��ϵͳMemPool������ʱ��, ��λ: ����	
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
	int nMaxIdleCount;		// ����������	
	int nMaxIdleTime;		// ������ʱ��
	int nUsing;				// ��ǰ����ʹ������
	int nIdle;				// ��ǰ�Ŀ�������
	int nApplyCount;		// ���뻺�����
	int nReleaseCount;		// �ͷŻ������	
	int nNewCount;			// �ͷ������ڴ�Ĵ���   	
	int nDeleteCount;		// ���������ڴ�Ĵ���
	int nIdleTimeCount;		// ���г�ʱ����
}POOLINFO;
typedef POOLINFO* LPPOOLINFO;

typedef struct _MEMBUFINFO
{
	int m_nNewSize;	    // ����������ڴ���������λ�ֽڣ�	
	int m_nApplyCount;	// ���뻺��Ĵ���
	int m_nReleaseCount;// �ͷŻ��������
	int m_nNewCount;	// ������������ڴ�Ĵ���
	int m_nDeleteCount; // �ͷŷ��������ڴ�Ĵ���	
	int m_nIdleTimeOutCount;// MemPool���������г�ʱ�Ĵ���
}MEMBUFINFO;
typedef MEMBUFINFO* LPMEMBUFINFO;

// ��ʼ���ڴ滺��ṹ
MEMAPI int MMSysInit(LPMEMINITINFO pMemInitInfo);
// �����Ե��ã��Ż��ڴ滺��
MEMAPI void MMSysCheck();	
// �ر�ʵʱ�ڴ����ݿ�
MEMAPI int MMSysDestroy();

// ���û���
MEMAPI int MMSetPool(int nItem, int nMaxIdleCount, int nMaxIdleTime);
MEMAPI bool MMGetPoolInfo(int nItem, LPPOOLINFO pPoolInfo);
MEMAPI int MMReleasePoolIdle(int nItem, int nReleaseIdle);
MEMAPI void MMGetMngInfo(LPMEMBUFINFO pMemBufInfo);

MEMAPI void* MMAlloc(int nSize);
MEMAPI void MMFree(void* pAddr, int nSize);

#pragma pack(pop)

#endif