#ifndef CACHESHARE_H
#define CACHESHARE_H

#include <windows.h>

#define MAX_TABLE_COLUMN_COUNT	1024
#define MAX_INDEX_COLUMN_COUNT	64		// ÿ���������������

#define RTDB_METHOD_ITERATE	0x00	// ������� 
#define RTDB_METHOD_KEY		0x01	// ��ֵ��ȫƥ��
#define RTDB_METHOD_MATCH	0x02	// ����ƥ��	
#define RTDB_METHOD_LIKE	0x03	// likeƥ��
#define RTDB_METHOD_LENGTH	0x04	// ������ȫƥ��

enum CacheDataType
{
	CACHE_NONE		= 0,
	CACHE_INT8		= 1,
	CACHE_UINT8		= 2,
	CACHE_INT16		= 3,
	CACHE_UINT16	= 4,
	CACHE_INT32		= 5,
	CACHE_UINT32	= 6,
	CACHE_INT64		= 7,
	CACHE_UINT64	= 8,
	CACHE_Float		= 9,
	CACHE_Double	= 10,
	CACHE_DateTime	= 11,
	CACHE_STRING	= 12,
	CACHE_TEXT		= 13,
	CACHE_BINARY	= 14,
	CACHE_VARSTRING = 15,
	CACHE_VARBINARY = 16
};

#pragma pack(push)
#pragma pack(1)

struct _SELECTCOND;

typedef bool (*FILTERAPI)(_SELECTCOND* pCondition);

typedef struct _SELECTCOND
{		
	HANDLE hTree;		// �༶�����	
	bool bEnableTop;	// �Ƿ�����topѡ��
	int nTopCount;		// top ֵ	
	char* sIndexValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	=�� like��match��len
	bool bEnableLower[MAX_INDEX_COLUMN_COUNT];
	bool bIncludeLower[MAX_INDEX_COLUMN_COUNT];
	char* sLowerValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	>�� >= len
	bool bEnableUpper[MAX_INDEX_COLUMN_COUNT];
	char* sUpperValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	<��<= len
	bool bIncludeUpper[MAX_INDEX_COLUMN_COUNT];
	int nMethod[MAX_INDEX_COLUMN_COUNT];// ���������ķ���: NULL����ȡ���Χ��like��match��len
	bool bAsc[MAX_INDEX_COLUMN_COUNT];	// ָ����������˳�����򡢽���	
		
	// ���ˣ��ص���������		 
	FILTERAPI pFilterAPI;	// ���˻ص�����ָ��
	void* pFilterPara;		// ���˻ص�����ֵָ��

	int nNowField;		// ��ǰ���������ļ��������������ʹ��	
	int nTopCounted;	// ����ʱʹ�ã�������Ч��¼��
	HANDLE hPosSet[MAX_INDEX_COLUMN_COUNT];// ��ǰ�������Ľڵ�	
	HANDLE hIndex;		 // �����ľ��
	HANDLE hRecord;		 // ��ǰ��¼���
	FILTERAPI pExtProc;	 // ��չ����ָ�룬�ڲ�ʹ��
	_SELECTCOND()
	{		
		hTree = NULL;
		bEnableTop = false;
		nTopCount = 0x7FFFFFFF;
		nTopCounted = 0;
		nNowField = 0;
		pFilterAPI = NULL;
		pFilterPara = NULL;	
		hIndex = NULL;
		hRecord = NULL;
		pExtProc = NULL;		
	};
}SELECTCOND;
typedef SELECTCOND* LPSELECTCOND;

#pragma pack(pop)

#endif