

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

	//��ʼ����
	VOID		InitTable( UINT uMaxItem, UINT uSize ) ;
	//����һ������
	BOOL		Add( const CHAR* szString, VOID* pPtr ) ;
	//��ȡ��Ϣ
	VOID*		Get( const CHAR* szString ) ;
	//ɾ������
	VOID		Remove( const CHAR* szString ) ;
	VOID		RemoveWithData( const CHAR* szString, VOID* pPrt ) ;
	//�����������
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
