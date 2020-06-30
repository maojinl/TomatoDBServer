
/************************************************************************
*  更新时间 2010.7.23
*  更新人:  DGH
*  文件名:	WGMail.h
*  功能:	world转发邮件给server。
*           邮件内容的读入与写出功能;
*			调用邮件实现接口;
************************************************************************/



#include "stdafx.h"


#include "WGMail.h"



BOOL WGMail::Read( SocketInputStream& iStream ) 
{
	__ENTER_FUNCTION

 	iStream.Read( (CHAR*)(&m_PlayerID), sizeof(PlayerID_t) ) ;
	iStream.Read( (CHAR*)(&m_GUID), sizeof(m_GUID) ) ;

	iStream.Read( (CHAR*)&m_PageIndex,sizeof(UINT));
	iStream.Read( (CHAR*)&m_PageRowCount,sizeof(UINT));
	
	return TRUE ;

	__LEAVE_FUNCTION

	return FALSE ;
}

BOOL WGMail::Write( SocketOutputStream& oStream )const
{
	__ENTER_FUNCTION

 	oStream.Write( (CHAR*)(&m_PlayerID), sizeof(PlayerID_t) ) ;
	oStream.Write( (CHAR*)(&m_GUID), sizeof(m_GUID) ) ;

	oStream.Write( (CHAR*)&m_PageIndex,sizeof(UINT));
	oStream.Write( (CHAR*)&m_PageRowCount,sizeof(UINT));
	
	return TRUE ;

	__LEAVE_FUNCTION

	return FALSE ;
}

UINT WGMail::Execute( Player* pPlayer )
{
	__ENTER_FUNCTION

		return WGMailHandler::Execute( this, pPlayer ) ;

	__LEAVE_FUNCTION

		return FALSE ;
}


