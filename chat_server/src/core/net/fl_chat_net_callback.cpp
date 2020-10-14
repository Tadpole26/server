#include "fl_chat_net_callback.h"


///////结束连接和错误事件//////////////
void FLChatCallBack::EventClientServerCallback(struct bufferevent *bev, short events, void *ctx)
{
	bool bFinish = false; 

	if (events & BEV_EVENT_EOF) 
	{
		bFinish = true;
		//std::cout << "connect close" << std::endl;	
	}
	else if (events & BEV_EVENT_ERROR) 
	{
		bFinish = true;
		//std::cout << "other error event" << std::endl;	
	}
	if (bFinish)
		bufferevent_free(bev); 
}
///////读事件//////////////
void FLChatCallBack::ReadClientServerCallback(struct bufferevent *bev, void *ctx)
{
	//获取buffevent的evbuffer长度
	struct evbuffer* input = bufferevent_get_input(bev);
	size_t sz = evbuffer_get_length(input);
	fl_client_proto_header_t stClientHead;

	/*
		读evbuffer里面的数据:
			1:剩余大小 < 包头大小
			2:剩余大小 > 包头大小 + 包体大小
			3:包头大小 < 剩余大小 < 包头大小 + 包体大小
	*/
	
	while(sz >= sizeof(stClientHead))
	{
		//读取包头大小,上面有包头大小检测(包头拷贝出来,防止head完整body不完整)
		/*auto iBagHeadLen = */evbuffer_copyout(input, &stClientHead, sizeof(stClientHead));
		
		//包体大小是否合法
		if (stClientHead.m_uiPacketLen > MAX_CONNECTOR_PACKET)
		{
			//如果释放 时还有未 决的延迟回调,则在回调完成之前 bufferevent 不会被删除
			FL_CHAT_LOG_INS->GetLogger()->error("client bag is too long!!");
			bufferevent_free(bev);
			break;
		}

		if (sz < (sizeof(stClientHead) + stClientHead.m_uiPacketLen))
		{
			break;
		}

		FL_CHAT_LOG_INS->GetLogger()->info("client bag info: {},{},{},{},{},{},{}, sz:{}", stClientHead.m_usCheckCode, stClientHead.m_usMaskCode, stClientHead.m_uiPacketLen,
																					stClientHead.m_usCmdMain, stClientHead.m_usCmdSub, stClientHead.m_iUserId, 
																					stClientHead.m_usSvrRsp, sz);

		//evbuffer中移出包头数据
		/*int iDrainHeadLen = */evbuffer_drain(input, sizeof(stClientHead));
		//读出包体长度
		char pBodyBuffer[MAX_CONNECTOR_PACKET] = {0};
		int iBodyLen = bufferevent_read(bev, pBodyBuffer, stClientHead.m_uiPacketLen);
		//去掉取出得包头包体长度
		sz -= (iBodyLen + sizeof(stClientHead)); 
		
		//构造对应cmd的工厂对象,执行对应cmd的函数
		processor_base_ptr_type stProcessor = FL_CMD_CONTAINER.GetProcessor(stClientHead.m_usCmdSub);
		stProcessor->SetClientUser(stClientHead.m_iUserId, bev);
		stProcessor->DoProcess(pBodyBuffer, stClientHead.m_uiPacketLen);
	}
}
///////写事件//////////////
void FLChatCallBack::WriteClientServerCallback(struct bufferevent* bev, void* user_data)
{
	//std::cout << "touch conn_writecb" << std::endl;
}

//////监听事件//////////////
/* fd:客户端io套接字 
 * sa:存储客户端ip等信息
 * user_data:传入的指针
 * */
void FLChatCallBack::ListenerCallback(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data)
{
	//struct event_base* base = (struct event_base*)user_data;
	struct event_base *base = evconnlistener_get_base(listener);
	/*
	 * BEV_OPT_CLOSE_ON_FREE:释放bufferevent关闭底层套接字
	 * BEV_OPT_THREADSAFE:线程安全
	 * BEV_OPT_DEFER_CALLBACKS:延迟回调
	 * BEV_OPT_UNLOCK_CALLBACKS:回调不锁定*/
	struct bufferevent* bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
	if (!bev)
	{
		FL_CHAT_LOG_INS->GetLogger()->error("error constructing bufferevent!");
		event_base_loopbreak(base);
		return;
	}

	/*
	 * bufferevent中回调函数触发的条件与普通的event回调函数触发的条件不同(普通的事件在底层传输端口已经就绪，可读或可写时就会执行回调函数，而 bufferevent 是在读取或写入了一定量的数据后才会调用回调函数)
	 * 默认读取低水位为0,读取只要大于0触发conn_read_event,
	 * 默认读取高水位为bufferevent中evbuffer缓冲区容量(无限),超过高水位不读
	 * 默认写入低水位为0,evbuffer被清空时,触发写操作
	 * */
	bufferevent_setcb(bev, ReadClientServerCallback, WriteClientServerCallback, EventClientServerCallback, NULL);
	//启用bufferevent读写事件(这个地方要写成 | 形式 不然非长连接read回调不会触发)
	bufferevent_enable(bev, EV_READ|EV_WRITE);
	//bufferevent_enable(bev, EV_READ);
}
///////连接错误事件/////////////
void FLChatCallBack::AcceptErrorCallback(struct evconnlistener *listener, void *ctx)
{
	struct event_base *base = evconnlistener_get_base(listener); 
	int err = EVUTIL_SOCKET_ERROR(); 
	FL_CHAT_LOG_INS->GetLogger()->error("Got an error on the listener {} {}", err, evutil_socket_error_to_string(err));
	//立刻退出事件循环
	event_base_loopexit(base, NULL);
}


void FLChatCallBack::ReadDbServerCallback(struct bufferevent *bev, void *ctx)
{
	//获取buffevent的evbuffer长度
	struct evbuffer* input = bufferevent_get_input(bev);
	size_t sz = evbuffer_get_length(input);
	fl_client_proto_header_t stClientHead;

	/*
		读evbuffer里面的数据:
			1:剩余大小 < 包头大小
			2:剩余大小 > 包头大小 + 包体大小
			3:包头大小 < 剩余大小 < 包头大小 + 包体大小
	*/
	
	while(sz >= sizeof(stClientHead))
	{
		//读取包头大小,上面有包头大小检测(包头拷贝出来,防止head完整body不完整)
		/*auto iBagHeadLen = */evbuffer_copyout(input, &stClientHead, sizeof(stClientHead));
		
		//包体大小是否合法
		if (stClientHead.m_uiPacketLen > MAX_CONNECTOR_PACKET)
		{
			//如果释放 时还有未 决的延迟回调,则在回调完成之前 bufferevent 不会被删除
			FL_CHAT_LOG_INS->GetLogger()->error("client bag is too long!!");
			bufferevent_free(bev);
			break;
		}

		if (sz < (sizeof(stClientHead) + stClientHead.m_uiPacketLen))
		{
			break;
		}

		//evbuffer中移出包头数据
		int iDrainHeadLen = evbuffer_drain(input, sizeof(stClientHead));
		//读出包体长度
		char pBodyBuffer[MAX_CONNECTOR_PACKET] = {0};
		int iBodyLen = bufferevent_read(bev, pBodyBuffer, stClientHead.m_uiPacketLen);
		//去掉取出得包头包体长度
		sz -= (iBodyLen + iDrainHeadLen); 
		
		//构造对应cmd的工厂对象,执行对应cmd的函数
		processor_base_ptr_type stProcessor = FL_CMD_CONTAINER.GetProcessor(stClientHead.m_usCmdSub);
		stProcessor->SetClientUser(stClientHead.m_iUserId, bev);
		stProcessor->DoProcess(pBodyBuffer, stClientHead.m_uiPacketLen);
	}
}

void FLChatCallBack::WriteDbServerCallback(struct bufferevent* bev, void* user_data)
{
	
}

void FLChatCallBack::EventDbServerCallback(struct bufferevent *bev, short events, void *ctx)
{
	bool bFinish = false; 

	if (events & BEV_EVENT_EOF) 
	{
		bFinish = true;
		//std::cout << "connect close" << std::endl;	
	}
	else if (events & BEV_EVENT_ERROR) 
	{
		bFinish = true;
		//std::cout << "other error event" << std::endl;	
	}
	if (bFinish)
		bufferevent_free(bev); 
}
