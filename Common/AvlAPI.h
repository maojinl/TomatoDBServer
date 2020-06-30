#ifndef AVLAPI_H
#define AVLAPI_H

typedef void* HANDLE;
typedef void* POSITION;
typedef void* HAVLTREE;

typedef int (* ONAVLCOMPARE)(void* pNodeKey, void* pOutKey);
typedef bool (* ONAVLDELETE)(POSITION pos, void* pInputPara);

#define AVLAPI extern "C"  __declspec(dllexport) 

AVLAPI HAVLTREE AvlCreateTree(ONAVLCOMPARE OnCompare);
AVLAPI void AvlDeleteTree(HAVLTREE hTree, ONAVLDELETE OnDelete = NULL, void* pInputPara = NULL);
AVLAPI void AvlRemoveAll(HAVLTREE hTree, ONAVLDELETE OnDelete = NULL, void* pInputPara = NULL);
AVLAPI bool AvlAddKey(HAVLTREE hTree, void* pKey, HANDLE hValue, POSITION& pos);
AVLAPI bool AvlRemoveKey(HAVLTREE hTree, void* pKey, HANDLE& hValue);
AVLAPI bool AvlRemoveKeyEx(HAVLTREE hTree, void* pKey, HANDLE& hValue, void*& pPosKey);
AVLAPI bool AvlGetKeyValue(HAVLTREE hTree, void* pKey, HANDLE& hValue);
AVLAPI bool AvlGetHead(HAVLTREE hTree, HANDLE& hValue);
AVLAPI bool AvlGetTail(HAVLTREE hTree, HANDLE& hValue);
AVLAPI bool AvlGetHeadEx(HAVLTREE hTree, HANDLE& hValue, void*& pPosKey);
AVLAPI bool AvlGetTailEx(HAVLTREE hTree, HANDLE& hValue, void*& pPosKey);
AVLAPI POSITION AvlGetKeyPosition(HAVLTREE hTree, void* pKey);
AVLAPI POSITION AvlGetHeadPosition(HAVLTREE hTree);
AVLAPI POSITION AvlGetTailPosition(HAVLTREE hTree);
AVLAPI POSITION AvlGetNextPosition(HAVLTREE hTree, POSITION pos);
AVLAPI POSITION AvlGetPrevPosition(HAVLTREE hTree, POSITION pos);
AVLAPI bool AvlRemoveHead(HAVLTREE hTree, HANDLE& hValue);
AVLAPI bool AvlRemoveTail(HAVLTREE hTree, HANDLE& hValue);
AVLAPI bool AvlRemoveHeadEx(HAVLTREE hTree, HANDLE& hValue, void*& pPosKey);
AVLAPI bool AvlRemoveTailEx(HAVLTREE hTree, HANDLE& hValue, void*& pPosKey);
AVLAPI void AvlRemoveAt(HAVLTREE hTree, POSITION pos);
AVLAPI POSITION AvlGetFirstPosGEKey(HAVLTREE hTree, void* pKey); // 节点值 >= pKey	
AVLAPI POSITION AvlGetFirstPosGTKey(HAVLTREE hTree, void* pKey); // 节点值 >  pKey	
AVLAPI POSITION AvlGetFirstPosSEKey(HAVLTREE hTree, void* pKey); // 节点值 <= pKey	
AVLAPI POSITION AvlGetFirstPosSTKey(HAVLTREE hTree, void* pKey); // 节点值 <  pKey	
AVLAPI int AvlGetCount(HAVLTREE hTree);
AVLAPI void* AvlGetPosKey(POSITION pos);
AVLAPI HANDLE AvlGetPosValue(POSITION pos);
AVLAPI void AvlSetPosValue(POSITION pos, HANDLE hValue);
//////////////////////////////////////////////////////////////////////////
AVLAPI POSITION AvlGetRoot(HAVLTREE hTree);
AVLAPI POSITION AvlGetParent(POSITION pos);
AVLAPI POSITION AvlGetLeftChild(POSITION pos);
AVLAPI POSITION AvlGetRightChild(POSITION pos);
AVLAPI int AvlGetHeight(POSITION pos);

#endif