/////////////////////////////////////////////////////////////////////////
//	�ļ�����: NGWordManager.h
//	����ʱ��:2010-8-11
//	������Ա:DGH
//	���ܼ��:�ؼ��ʹ��˹�����
//////////////////////////////////////////////////////////////////////////


#ifndef   __NGWORD_MANAGER_H__
#define   

#include "Type.h"

//#include "MTreeAPI.h"  //ɢ�б�

#include "vector"

//#pragma comment(lib,"MTreeAPI.lib");
//#pragma comment(lib,"");

#define  MAX_NG_WORD_LEN  200 //���Ե��м�¼����ַ���(����������)

typedef  struct  _NGWORD{
UINT  aid;
CHAR  ngWord[ MAX_NG_WORD_LEN +1 ];
UINT  nLen;
}NGWORD;

typedef NGWORD  *PNGWORD;

class NGWordManager{

public:
	NGWordManager();
	virtual ~NGWordManager();

public:
	static CHAR   szFindKey[ MAX_NG_WORD_LEN +1 ];

	UINT Init();
    //����NGWORD �б�;
	//������NGWORD�����ļ�·��;
	//�ɹ�������TRUE
	//ʧ�ܣ�����FALSE;
	UINT  LoadNGWord( CHAR* ngFile );

public:

    //У���ı��Ƿ����,����н��ԣ����Խ����������滻�� "*" ��ʾ; 
	//����srcWord��ҪУ����ı�;
	//����: srcWord�ǽ������ݣ�����TRUE;
	//      srcWord���ǽ������ݣ�����FALSE;
	UINT  VerifyNGWord( CHAR* srcWord );

	//У���ı��Ƿ�������� 
	//����srcWord��ҪУ����ı�(MAX_LEN =200);
	//����:  srcWord�����������ݣ�����TRUE;
	//        srcWordδ�����������ݣ�����FALSE;
	BOOL  FindNGWord(CHAR* srcWord )const;

public:
	//���ɢ�б�
	VOID  Clear();
	UINT  GetNGWordCount(){  return m_TreeCount ; }
	CHAR* GetFindKey() { return szFindKey; }

private:
    //����ɢ�б�;
	//Ŀǰ��ɢ�б�Ϊһ��hash��.
	HANDLE m_hTree; 
	UINT   m_TreeCount; //ɢ�б��¼����;	

	//������б�������һ�����Լ�¼���� 
	// hTree:ɢ����; aid �������  sWord ��������
	// ����:������ɢ�����е����;
	INT   AddNGWord(HANDLE hTree,UINT aid, CHAR* sWord );
	//ɢ������ѯ
	//pCond����ѯ����
	//����ֵ������ѯ������,����TRUE;
	//��δ��ѯ������,����FALSE;
	//static bool  FilterProc( LPSELECTCOND pCond );

	//ɢ����ƥ��(����ƥ��:��Դ����ɢ�б����ƥ��)
	//hTree ����ɢ�������
	//sKey ƥ�����ݣ�֧��ͨ��� '%' (ͨ�������ַ��� '?'(ͨ�䵥���ַ�) )

	//��ע��,�������������������ʹ��

	// bAsc ����ʽ(�����֧�ִ�ӡ�б��õ�) �˴�����!!
	// bTopEnable ��ӡ�б����ʼλ��(true �ӿ�ͷ��; false ��ĩβ��) �˴�����!!
	// nTopCount ��ӡ������( 0:��ʾ���е� >0 ��ʾ��ӡ��ָ�������ļ�¼���˴�����!!
	UINT AccessSingle(HANDLE hTree, char* sKey, bool bAsc=false, bool bTopEnable=false,int nTopCount=0);

	//ɢ����ƥ��(����ƥ��:��ɢ�б�����ص�����Դ�����ݽ���ƥ��)
	//hTree ����ɢ�������
	//sKey ƥ�����ݣ�֧��ͨ��� '%' (ͨ�������ַ��� '?'(ͨ�䵥���ַ�) )

	//��ע��,�������������������ʹ��

	// bAsc ����ʽ(�����֧�ִ�ӡ�б��õ�) �˴�����!!
	// bTopEnable ��ӡ�б����ʼλ��(true �ӿ�ͷ��; false ��ĩβ��) �˴�����!!
	// nTopCount ��ӡ������( 0:��ʾ���е� >0 ��ʾ��ӡ��ָ�������ļ�¼���˴�����!!

    UINT AccessSingleMatch(HANDLE hTree, char* sKey, bool bAsc=false, bool bTopEnable=false,int nTopCount=0);


	VOID ReplaceNGWord( CHAR* srcNGWord );
	//ɾ������
	//
	VOID OnDelete(HANDLE hValue, HANDLE hPara)
	{
		PNGWORD pNGWord;
		pNGWord = PNGWORD(hValue);
		delete pNGWord;
		return;
	}


private:
	vector< PNGWORD > m_NGWordList;//�����б�;

};

extern NGWordManager g_NGWordManager;

#endif




