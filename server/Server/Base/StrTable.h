

#ifndef __STRTABLE_H__
#define __STRTABLE_H__

#ifndef USE_STD_MAP
#define USE_STD_MAP
#endif

#include "Type.h"


struct _TABLEITEM_STR
{
	CHAR*	m_pString ;
	VOID*	m_pPtr ;
	UINT	m_Status ;

	_TABLEITEM_STR( )
	{
		m_pString = nullptr ;
		m_pPtr = nullptr ;
		m_Status = 0 ;
	}
	~_TABLEITEM_STR( )
	{
		SAFE_DELETE_ARRAY( m_pString ) ;
		m_pPtr = nullptr ;
		m_Status = 0 ;
	}
};

#ifdef	USE_STD_MAP
using namespace std;
typedef		std::map<string,VOID*>	strMap;
#endif

class StrTable
{
public :
	StrTable( ) ;
	~StrTable( ) ;

	//初始化表
	VOID		InitTable( UINT uMaxItem, UINT uSize ) ;
	//增加一个表项
	BOOL		Add( const CHAR* szString, VOID* pPtr ) ;
	//读取信息
	VOID*		Get( const CHAR* szString ) ;
	//删除表项
	VOID		Remove( const CHAR* szString ) ;
	VOID		RemoveWithData( const CHAR* szString, VOID* pPrt ) ;
	//清除所有数据
	VOID		CleanUp( ) ;

public :
	enum {
		STRTS_EMPTY = 0 ,
		STRTS_SET = 1 ,
		STRTS_USE = 2 ,
	};

private :

	_TABLEITEM_STR*	m_pTable ;
	UINT			m_Count ;
	UINT			m_StringSize ;

#ifdef	USE_STD_MAP
	strMap			m_mTable;
#endif


};

#endif
