

#ifndef __PLAYERSTATUS_H__
#define __PLAYERSTATUS_H__


enum PLAYER_STATUS
{
	/////////////////////////////
	//��Ϸ�������е����״̬
	/////////////////////////////

	//��������ڷ������˵ĳ�ʼ״̬
	PS_SERVER_EMPTY = 100 ,		

	//����������ӳɹ����״̬����һ����Ҫ���͵���Ϣ�ǣ�
	//CGConnect�����N����û�յ������Ϣ����Ͽ�������
	PS_SERVER_CONNECT,

	// ��������������֤��ȴ��ͻ��˷���CGEnterScene��Ϣ
	// ���һ��ʱ����û���յ�CGEnterScene��Ϣ����Ͽ�����
	PS_SERVER_WAITING_FOR_ENTER ,	
								
	//���ڸս���Ŀͻ������ӣ����������յ�CGEnterScene��Ϣ���
	//IncomingPlayerManager�Ƴ���Ϣ׼������Scene��
	//�����Ѿ��ڳ����еĿͻ������ӣ��ͻ�����Ҫת������
	//�������յ�CGEnterScene��Ϣ���ԭ�������Ƴ���Ϣ��׼�����뵽�³���
	PS_SERVER_READY_TO_ENTER,

	//�ͻ������״̬����������Ϸ״̬
	PS_SERVER_NORMAL ,

	//����Ѿ��ӷ������϶Ͽ������ҽ������ݱ���׶�
	PS_SERVER_ENTER_RECYCLE ,
	PS_SERVER_LEAVE_RECYCLE ,

	///////////////////////////////
	//��Ϸ�ͻ����е����״̬
	///////////////////////////////
	PS_CLIENT_LOAD = 200 ,
	PS_CLIENT_CONNECT ,

	///////////////////////////////
	//�������ݷ������е�������״̬
	///////////////////////////////
	PS_WORLD_CONNECT = 500 ,
	PS_WORLD_NORMAL ,
};

#endif
