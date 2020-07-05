#include "stdafx.h"

#include "GCEnterScene.h"

BOOL GCEnterScene::Read( SocketInputStream& iStream ) 
{
__ENTER_FUNCTION
    UINT UserId = 0;
	iStream.Read( (CHAR*)(&UserId), sizeof(UINT) ) ;
	iStream.Read( (CHAR*)(&m_byRet), sizeof(BYTE));
	iStream.Read( (CHAR*)(&m_nSceneID), sizeof(WorkerID_t));

	iStream.Read( (CHAR*)(&m_CharName), sizeof(CHAR)*MAX_CHARACTER_NAME ) ;
	iStream.Read( (CHAR*)(&m_iSex), sizeof(UINT));
	iStream.Read( (CHAR*)(&m_iIcon), sizeof(UINT));
	iStream.Read( (CHAR*)(&m_TitleName), sizeof(CHAR)*MAX_CHARACTER_TITLE ) ;
	iStream.Read( (CHAR*)(&m_iSceneID), sizeof(UINT));
	iStream.Read( (CHAR*)(&m_iLevel), sizeof(UINT));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

BOOL GCEnterScene::Write( SocketOutputStream& oStream )const
{
__ENTER_FUNCTION

    UINT UserId = 0;
	oStream.Write( (CHAR*)(&UserId), sizeof(UINT) ) ;
	oStream.Write( (CHAR*)(&m_byRet), sizeof(BYTE) ) ;
	oStream.Write( (CHAR*)(&m_nSceneID), sizeof(WorkerID_t) ) ;

	oStream.Write( (CHAR*)(&m_CharName), sizeof(CHAR)*MAX_CHARACTER_NAME ) ;
	oStream.Write( (CHAR*)(&m_iSex), sizeof(UINT));
	oStream.Write( (CHAR*)(&m_iIcon), sizeof(UINT));
	oStream.Write( (CHAR*)(&m_TitleName), sizeof(CHAR)*MAX_CHARACTER_TITLE ) ;
	oStream.Write( (CHAR*)(&m_iSceneID), sizeof(UINT));
	oStream.Write( (CHAR*)(&m_iLevel), sizeof(UINT));
	return TRUE ;

__LEAVE_FUNCTION

	return FALSE ;
}

UINT GCEnterScene::Execute( Player* pPlayer )
{
__ENTER_FUNCTION

	return GCEnterSceneHandler::Execute( this, pPlayer ) ;

__LEAVE_FUNCTION

	return FALSE ;
}
