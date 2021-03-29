



#ifndef __IDTABLE_H__
#define __IDTABLE_H__

#include "Type.h"
#include <map>

#define IDMAP  UINT,VOID*

class IDTable
{
public :
	IDTable( ) ;
	~IDTable( ) ;

	//��ʼ����
	VOID		InitTable( UINT MaxItem ) ;
	//����һ������
	BOOL		Add( UINT id, VOID* pPtr ) ;
	//��ȡ��Ϣ
	VOID*		Get( UINT id ) ;
	//ɾ������
	VOID		Remove( UINT id ) ;
	//�����������
	VOID		CleanUp( ) ;

protected :

private :

	map<IDMAP>  	m_pTable ;
	UINT			m_Count ;


};

#endif
