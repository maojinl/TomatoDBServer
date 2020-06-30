#ifndef __SCENEMANAGER_H__
#define __SCENEMANAGER_H__

#include "Type.h"
#include "IDTable.h"
#include "Config.h"
#include "Scene.h"

/////////////////////////////////////////////////////////////////////////////////
// SceneManager
/////////////////////////////////////////////////////////////////////////////////
class SceneManager
{
public :
	SceneManager( ) ;
	~SceneManager( ) ;

	//��ʼ���ӿ�
	BOOL			Init( UINT MaxSceneCount = MAX_SCENE ) ;

	//���ݳ�����ȡ�ó�������ָ��
	Scene*			GetScene( SceneID_t SceneID ) ;
	//���ݳ�����ȡ�ó���������Ϣ
	_SCENE_DATA*	GetSceneInfo( SceneID_t SceneID ) ;
	//���ݳ������жϴ˳����Ƿ��ڵ�ǰ�������˳�����
	BOOL			IsInCurServer( SceneID_t SceneID ) ;
	//���ݳ������жϴ˳����Ƿ񱻵�ǰ�������ϵ�ĳ���������˳�����
	BOOL			IsInCurMachine( SceneID_t SceneID ) ;

	//��ϵͳ�����һ������
	BOOL			AddScene( Scene* pScene ) ;
	//��һ��������ϵͳ��ɾ��
	BOOL			DelScene( SceneID_t SceneID ) ;

	//����ĳ�������е�����
	VOID			SetScenePlayerCount( SceneID_t SceneID, INT count ){
		if( SceneID < 0 && SceneID>=MAX_SCENE ) return ;
		m_aScenePlayerCount[SceneID] = count ;
	};
	//��ȡĳ�������е�����
	INT				GetScenePlayerCount( SceneID_t SceneID ){
		if( SceneID < 0 && SceneID>=MAX_SCENE ) return 0 ;
		return m_aScenePlayerCount[SceneID] ;
	};

	VOID			SetTotalPlayerCount(INT nCount){ m_nTotalPlayerCount=nCount; } ;
	INT				GetTotalPlayerCount(){ return m_nTotalPlayerCount ; } ;
	SceneID_t		GetSpecialSceneIDFromCurServer( ) ;//ȡ��һ���ڵ�ǰServer�ϵ���Ϸ�߼�����
    BOOL BroadCast_Scene(Packet* pMsg);

private :
	Scene*			m_pScene[MAX_SCENE] ;			//��������ָ��
	INT				m_aScenePlayerCount[MAX_SCENE] ;//����������
	UINT			m_Count ;//��ǰϵͳ�еĳ�������

	INT				m_nTotalPlayerCount ;//������Ϸ����������ܺ�
};

extern SceneManager* g_pSceneManager ;


#endif
