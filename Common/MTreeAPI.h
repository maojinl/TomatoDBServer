#ifndef MTREE_API_H
#define MTREE_API_H

#include "CacheShare.h"
#include "AvlAPI.h"

typedef void* HMTREE;

#define TREE_AVL	0x01
#define TREE_TRIE	0x02
#define TREE_UTRIE	0x03

#define MTREEAPI extern "C"  __declspec(dllexport) 

#pragma pack(push)
#pragma pack(1)

typedef struct _HTREEDESC
{		
	int nLevel;
	int nDataType[MAX_INDEX_COLUMN_COUNT];	
	int nTreeType[MAX_INDEX_COLUMN_COUNT];	
	ONAVLCOMPARE OnCompare[MAX_INDEX_COLUMN_COUNT];	
	_HTREEDESC()
	{
		int i;
		for (i = 0; i < MAX_INDEX_COLUMN_COUNT; i++)
		{
			OnCompare[i] = NULL;
		}
	}
}HTREEDESC;
typedef HTREEDESC* LPHTREEDESC;

typedef void (*ONMULTIDELETE)(HANDLE hValue, HANDLE hPara);

// 压缩哈希树虚节点
MTREEAPI int HTreeCompact(HMTREE hTree);
// 生成哈希树
MTREEAPI HMTREE HTreeCreate(LPHTREEDESC pTreeDesc);
// 删除哈希树
MTREEAPI void HTreeDelete(HMTREE hTree, ONMULTIDELETE OnDelete = NULL, HANDLE hPara = NULL);
// 获取实节点数目
MTREEAPI int HTreeGetCount(HMTREE hTree);
// 功能：插入记录到指定的表
MTREEAPI bool HTreeAddKey(HMTREE hTree, char* sMultiKey[], HANDLE hValue);
// 删除指定的记录，根据记录的句柄
MTREEAPI bool HTreeRemoveKey(HMTREE hTree, char* sMultiKey[], HANDLE& hValue);
// 快速键值精确匹配
MTREEAPI bool HTreeGetKeyValue(HMTREE hTree, char* sMultiKey[], HANDLE& hValue);
// 键值精确匹配中间树节点
MTREEAPI bool HTreeGetKeyNode(HMTREE hTree, int nCount, char* sMultiKey[], HANDLE& hValue);
// 快速键值精确匹配
MTREEAPI bool HTreeGetKeyPosition(HMTREE hTree, char* sMultiKey[], POSITION hNodeSet[]);
// 快速规则匹配
MTREEAPI bool HTreeGetMatchValue(HMTREE hTree, char* sMultiKey[], bool bMax[], HANDLE& hValue);
MTREEAPI bool HTreeGetMatchPosition(HMTREE hTree, char* sMultiKey[], bool bMax[], POSITION hNodeSet[]);
// 在指定的排序的情况下，获取头节点的句柄值
MTREEAPI bool HTreeGetHead(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// 在指定的排序的情况下，获取末节点的句柄值
MTREEAPI bool HTreeGetTail(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// 在指定的排序的情况下，获取头节点
MTREEAPI bool HTreeGetHeadPosition(HMTREE hTree, bool bAsc[], POSITION hPosSet[]);
// 在指定的排序的情况下，获取尾节点
MTREEAPI bool HTreeGetTailPosition(HMTREE hTree, bool bAsc[], POSITION hPosSet[]);
// 在指定的排序的情况下，删除头节点，并返回节点句柄值
MTREEAPI bool HTreeRemoveHead(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// 在指定的排序的情况下，删除尾节点，并返回节点句柄值
MTREEAPI bool HTreeRemoveTail(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// 删除指定节点
MTREEAPI void HTreeRemoveAt(HMTREE hTree, POSITION hPosSet[]);
// 通用查询函数
MTREEAPI int HTreeSelect(LPSELECTCOND pSelectCond);
// 以下2个函数，只能在回调函数中使用
// 获取当前所遍历节点的节点句柄
MTREEAPI void HTreeGetCurrentPosition(LPSELECTCOND pSelectCond, POSITION hPosSet[]);
// 获取当前所遍历节点的节点值的句柄
MTREEAPI HANDLE HTreeGetCurrentValue(LPSELECTCOND pSelectCond);

MTREEAPI void* HTreeGetAvlPosKey(POSITION pos);
MTREEAPI HANDLE HTreeGetAvlPosValue(POSITION pos);
MTREEAPI void HTreeSetAvlPosValue(POSITION pos, HANDLE hValue);

MTREEAPI void HTreeGetTriePosKey(POSITION pos, char* sKey);
MTREEAPI HANDLE HTreeGetTriePosValue(POSITION pos);
MTREEAPI void HTreeSetTriePosValue(POSITION pos, HANDLE hValue);

MTREEAPI void HTreeGetUTriePosKey(POSITION pos, char* sKey);
MTREEAPI HANDLE HTreeGetUTriePosValue(POSITION pos);
MTREEAPI void HTreeSetUTriePosValue(POSITION pos, HANDLE hValue);

MTREEAPI HANDLE HTreeGetPosValue(HMTREE hTree, POSITION hPosSet[]);

MTREEAPI void HTreeRemoveAll(HMTREE hTree, ONMULTIDELETE OnDelete = NULL, HANDLE hPara = NULL);

MTREEAPI int HTreeGetTreeType(HMTREE hTree, int nIndex);
MTREEAPI int HTreeGetDataType(HMTREE hTree, int nIndex);

// 获取多级树的第一级树的句柄
MTREEAPI HANDLE HTreeGetRoot(HMTREE hTree);

MTREEAPI bool HTreeAddKeyR(HMTREE hTree, void* pMultiKey[], HANDLE hValue);
MTREEAPI bool HTreeRemoveKeyR(HMTREE hTree, void* pMultiKey[], HANDLE& hValue);
MTREEAPI bool HTreeGetKeyValueR(HMTREE hTree, void* pMultiKey[], HANDLE& hValue);

#pragma pack(pop)

#endif