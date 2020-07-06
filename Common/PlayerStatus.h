

#ifndef __PLAYERSTATUS_H__
#define __PLAYERSTATUS_H__


enum PLAYER_STATUS
{
	/////////////////////////////
	//游戏服务器中的玩家状态
	/////////////////////////////

	//玩家数据在服务器端的初始状态
	PS_SERVER_EMPTY = 100 ,		

	//玩家网络连接成功后的状态，下一个需要发送的消息是：
	//CGConnect，如果N秒内没收到这个消息，则断开此连接
	PS_SERVER_CONNECT,

	// 经过服务器的验证后等待客户端发送CGEnterScene消息
	// 如果一段时间内没有收到CGEnterScene消息，则断开连接
	PS_SERVER_WAITING_FOR_ENTER ,	
								
	//对于刚接入的客户端连接，服务器接收到CGEnterScene消息后从
	//IncomingPlayerManager移除信息准备加入Scene中
	//对于已经在场景中的客户端连接，客户端需要转换场景
	//服务器收到CGEnterScene消息后从原场景里移除信息，准备加入到新场景
	PS_SERVER_READY_TO_ENTER,

	//客户端玩家状态进入正常游戏状态
	PS_SERVER_NORMAL ,

	//玩家已经从服务器上断开，并且进入数据保存阶段
	PS_SERVER_ENTER_RECYCLE ,
	PS_SERVER_LEAVE_RECYCLE ,

	///////////////////////////////
	//游戏客户端中的玩家状态
	///////////////////////////////
	PS_CLIENT_LOAD = 200 ,
	PS_CLIENT_CONNECT ,

	///////////////////////////////
	//世界数据服务器中的连接者状态
	///////////////////////////////
	PS_WORLD_CONNECT = 500 ,
	PS_WORLD_NORMAL ,
};

#endif
