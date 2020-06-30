#ifndef CACHESHARE_H
#define CACHESHARE_H

#include <windows.h>

#define MAX_TABLE_COLUMN_COUNT	1024
#define MAX_INDEX_COLUMN_COUNT	64		// 每个索引的最大列数

#define RTDB_METHOD_ITERATE	0x00	// 整体遍历 
#define RTDB_METHOD_KEY		0x01	// 键值完全匹配
#define RTDB_METHOD_MATCH	0x02	// 规则匹配	
#define RTDB_METHOD_LIKE	0x03	// like匹配
#define RTDB_METHOD_LENGTH	0x04	// 长度完全匹配

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
	HANDLE hTree;		// 多级树句柄	
	bool bEnableTop;	// 是否启动top选项
	int nTopCount;		// top 值	
	char* sIndexValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	=、 like、match、len
	bool bEnableLower[MAX_INDEX_COLUMN_COUNT];
	bool bIncludeLower[MAX_INDEX_COLUMN_COUNT];
	char* sLowerValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	>、 >= len
	bool bEnableUpper[MAX_INDEX_COLUMN_COUNT];
	char* sUpperValue[MAX_INDEX_COLUMN_COUNT];	// called by cache api	<、<= len
	bool bIncludeUpper[MAX_INDEX_COLUMN_COUNT];
	int nMethod[MAX_INDEX_COLUMN_COUNT];// 利用索引的方法: NULL、相等、范围、like、match、len
	bool bAsc[MAX_INDEX_COLUMN_COUNT];	// 指明索引遍历顺序（升序、降序）	
		
	// 过滤，回调函数处理		 
	FILTERAPI pFilterAPI;	// 过滤回调函数指针
	void* pFilterPara;		// 过滤回调函数值指针

	int nNowField;		// 当前处理索引的级别层数，运行中使用	
	int nTopCounted;	// 运行时使用，遍历有效记录数
	HANDLE hPosSet[MAX_INDEX_COLUMN_COUNT];// 当前各级树的节点	
	HANDLE hIndex;		 // 索引的句柄
	HANDLE hRecord;		 // 当前记录句柄
	FILTERAPI pExtProc;	 // 扩展过程指针，内部使用
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