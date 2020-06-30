/////////////////////////////////////////////////////////////////////////
//	文件名称: NGWordManager.h
//	创建时间:2010-8-11
//	创建人员:DGH
//	功能简介:关键词过滤管理器
//////////////////////////////////////////////////////////////////////////


#ifndef   __NGWORD_MANAGER_H__
#define   

#include "Type.h"

//#include "MTreeAPI.h"  //散列表

#include "vector"

//#pragma comment(lib,"MTreeAPI.lib");
//#pragma comment(lib,"");

#define  MAX_NG_WORD_LEN  200 //禁言单行记录最大字符数(包含结束符)

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
    //加载NGWORD 列表;
	//参数是NGWORD配置文件路径;
	//成功：返回TRUE
	//失败：返回FALSE;
	UINT  LoadNGWord( CHAR* ngFile );

public:

    //校验文本是否禁言,如果有禁言，则自将禁言内容替换成 "*" 表示; 
	//参数srcWord是要校验的文本;
	//返回: srcWord是禁言内容，返回TRUE;
	//      srcWord不是禁言内容，返回FALSE;
	UINT  VerifyNGWord( CHAR* srcWord );

	//校验文本是否包含禁言 
	//参数srcWord是要校验的文本(MAX_LEN =200);
	//返回:  srcWord包含禁言内容，返回TRUE;
	//        srcWord未包含禁言内容，返回FALSE;
	BOOL  FindNGWord(CHAR* srcWord )const;

public:
	//清空散列表
	VOID  Clear();
	UINT  GetNGWordCount(){  return m_TreeCount ; }
	CHAR* GetFindKey() { return szFindKey; }

private:
    //禁言散列表;
	//目前的散列表为一级hash表.
	HANDLE m_hTree; 
	UINT   m_TreeCount; //散列表记录行数;	

	//向禁言列表中增加一个禁言记录数据 
	// hTree:散列树; aid 禁言序号  sWord 禁言内容
	// 返回:禁言在散列树中的序号;
	INT   AddNGWord(HANDLE hTree,UINT aid, CHAR* sWord );
	//散列树查询
	//pCond，查询条件
	//返回值，若查询到禁言,返回TRUE;
	//若未查询到禁言,返回FALSE;
	//static bool  FilterProc( LPSELECTCOND pCond );

	//散列树匹配(正向匹配:将源串与散列表进行匹配)
	//hTree 禁言散列树句柄
	//sKey 匹配内容（支持通配符 '%' (通配任意字符） '?'(通配单个字符) )

	//请注意,以下三个参数在这儿不使用

	// bAsc 排序方式(这个是支持打印列表用的) 此处不用!!
	// bTopEnable 打印列表的起始位置(true 从开头起; false 从末尾起) 此处不用!!
	// nTopCount 打印的行数( 0:表示所有的 >0 表示条印出指定行数的记录）此处不用!!
	UINT AccessSingle(HANDLE hTree, char* sKey, bool bAsc=false, bool bTopEnable=false,int nTopCount=0);

	//散列树匹配(反向匹配:将散列表中相关的项与源串内容进行匹配)
	//hTree 禁言散列树句柄
	//sKey 匹配内容（支持通配符 '%' (通配任意字符） '?'(通配单个字符) )

	//请注意,以下三个参数在这儿不使用

	// bAsc 排序方式(这个是支持打印列表用的) 此处不用!!
	// bTopEnable 打印列表的起始位置(true 从开头起; false 从末尾起) 此处不用!!
	// nTopCount 打印的行数( 0:表示所有的 >0 表示条印出指定行数的记录）此处不用!!

    UINT AccessSingleMatch(HANDLE hTree, char* sKey, bool bAsc=false, bool bTopEnable=false,int nTopCount=0);


	VOID ReplaceNGWord( CHAR* srcNGWord );
	//删除禁言
	//
	VOID OnDelete(HANDLE hValue, HANDLE hPara)
	{
		PNGWORD pNGWord;
		pNGWord = PNGWORD(hValue);
		delete pNGWord;
		return;
	}


private:
	vector< PNGWORD > m_NGWordList;//禁言列表;

};

extern NGWordManager g_NGWordManager;

#endif




