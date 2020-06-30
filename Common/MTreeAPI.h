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

// ѹ����ϣ����ڵ�
MTREEAPI int HTreeCompact(HMTREE hTree);
// ���ɹ�ϣ��
MTREEAPI HMTREE HTreeCreate(LPHTREEDESC pTreeDesc);
// ɾ����ϣ��
MTREEAPI void HTreeDelete(HMTREE hTree, ONMULTIDELETE OnDelete = NULL, HANDLE hPara = NULL);
// ��ȡʵ�ڵ���Ŀ
MTREEAPI int HTreeGetCount(HMTREE hTree);
// ���ܣ������¼��ָ���ı�
MTREEAPI bool HTreeAddKey(HMTREE hTree, char* sMultiKey[], HANDLE hValue);
// ɾ��ָ���ļ�¼�����ݼ�¼�ľ��
MTREEAPI bool HTreeRemoveKey(HMTREE hTree, char* sMultiKey[], HANDLE& hValue);
// ���ټ�ֵ��ȷƥ��
MTREEAPI bool HTreeGetKeyValue(HMTREE hTree, char* sMultiKey[], HANDLE& hValue);
// ��ֵ��ȷƥ���м����ڵ�
MTREEAPI bool HTreeGetKeyNode(HMTREE hTree, int nCount, char* sMultiKey[], HANDLE& hValue);
// ���ټ�ֵ��ȷƥ��
MTREEAPI bool HTreeGetKeyPosition(HMTREE hTree, char* sMultiKey[], POSITION hNodeSet[]);
// ���ٹ���ƥ��
MTREEAPI bool HTreeGetMatchValue(HMTREE hTree, char* sMultiKey[], bool bMax[], HANDLE& hValue);
MTREEAPI bool HTreeGetMatchPosition(HMTREE hTree, char* sMultiKey[], bool bMax[], POSITION hNodeSet[]);
// ��ָ�������������£���ȡͷ�ڵ�ľ��ֵ
MTREEAPI bool HTreeGetHead(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// ��ָ�������������£���ȡĩ�ڵ�ľ��ֵ
MTREEAPI bool HTreeGetTail(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// ��ָ�������������£���ȡͷ�ڵ�
MTREEAPI bool HTreeGetHeadPosition(HMTREE hTree, bool bAsc[], POSITION hPosSet[]);
// ��ָ�������������£���ȡβ�ڵ�
MTREEAPI bool HTreeGetTailPosition(HMTREE hTree, bool bAsc[], POSITION hPosSet[]);
// ��ָ�������������£�ɾ��ͷ�ڵ㣬�����ؽڵ���ֵ
MTREEAPI bool HTreeRemoveHead(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// ��ָ�������������£�ɾ��β�ڵ㣬�����ؽڵ���ֵ
MTREEAPI bool HTreeRemoveTail(HMTREE hTree, bool bAsc[], HANDLE& hValue);
// ɾ��ָ���ڵ�
MTREEAPI void HTreeRemoveAt(HMTREE hTree, POSITION hPosSet[]);
// ͨ�ò�ѯ����
MTREEAPI int HTreeSelect(LPSELECTCOND pSelectCond);
// ����2��������ֻ���ڻص�������ʹ��
// ��ȡ��ǰ�������ڵ�Ľڵ���
MTREEAPI void HTreeGetCurrentPosition(LPSELECTCOND pSelectCond, POSITION hPosSet[]);
// ��ȡ��ǰ�������ڵ�Ľڵ�ֵ�ľ��
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

// ��ȡ�༶���ĵ�һ�����ľ��
MTREEAPI HANDLE HTreeGetRoot(HMTREE hTree);

MTREEAPI bool HTreeAddKeyR(HMTREE hTree, void* pMultiKey[], HANDLE hValue);
MTREEAPI bool HTreeRemoveKeyR(HMTREE hTree, void* pMultiKey[], HANDLE& hValue);
MTREEAPI bool HTreeGetKeyValueR(HMTREE hTree, void* pMultiKey[], HANDLE& hValue);

#pragma pack(pop)

#endif