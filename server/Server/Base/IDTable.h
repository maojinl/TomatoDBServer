



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

	//初始化表
	VOID		InitTable( UINT MaxItem ) ;
	//增加一个表项
	BOOL		Add( UINT id, VOID* pPtr ) ;
	//读取信息
	VOID*		Get( UINT id ) ;
	//删除表项
	VOID		Remove( UINT id ) ;
	//清除所有数据
	VOID		CleanUp( ) ;

protected :

private :

	map<IDMAP>  	m_pTable ;
	UINT			m_Count ;


};

#endif
