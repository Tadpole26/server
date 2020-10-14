#include "fl_chat_service.h"

FLChatService::FLChatService() { }

bool 
FLChatService::BeforeRun(int iArgc, char** pArgv)
{
	auto pDailyLogger = spdlog::daily_logger_mt("daily_logger", "logs/daily.log", 0, 0);
	if (pDailyLogger == nullptr)
	{
		pDailyLogger->error("create daily_logger fail!");
	}
	pDailyLogger->set_pattern("[%Y-%m-%d %H:%M:%S.%e] [%n] [%^%l%$] [p %P] [%o ms]:%v");
	//遇到trace及以上级别会立马将缓存的buffer写到文件中，底层调用是std::fflush(_fd)
	pDailyLogger->flush_on(spdlog::level::debug);
	pDailyLogger->info("create daily_logger success!");
	FL_CHAT_LOG_INS->SetLogInfo(pDailyLogger);
	return true;
}


bool 
FLChatService::ReadRedis(std::string& stName)
{
	struct FLChatRedisCallBackName : public FLChatRedisCallBackBase
	{
		std::string& m_stName;
		FLChatRedisCallBackName(std::string& stName) : m_stName(stName) { }

		bool ExecuteArray(const size_t total, const size_t pos, const char* str, const size_t len)
		{
			if (str && len)
				m_stName = std::string(str);
			return true;
		}
	};

	FLChatRedisCallBackName stCallback(stName);
	FL_CHAT_REDIS_INS->Execute(stCallback, "get name");

	return true;
}

void	
FLChatService::RealRun(int iArgc, char** pArgv)
{
	if (!BeforeRun(iArgc, pArgv))
	{
		FL_CHAT_LOG_INS->GetLogger()->error("service start fail, beforeRun fail!");
		return;
	}

    if (!LoadConfig())
	{
		FL_CHAT_LOG_INS->GetLogger()->error("service start fail, config load fail!");
		return;
	}

	if (!CreateRedisIns())
	{
		FL_CHAT_LOG_INS->GetLogger()->error("service start fail, create db fail!");
		return;
	}

	std::string stName("");
	ReadRedis(stName);
	FL_CHAT_LOG_INS->GetLogger()->info("get redis name {}", stName);
    
    EpollRunning(iArgc, pArgv);	
	return ;
}


bool
FLChatService::LoadConfig()
{
    CFlChatConfig* pConfig = new CFlChatConfig();
	CFlChatConfig::SetConfig(pConfig);

	std::pair<bool, std::string> stRet(true, "OK");
	fl_chat_config_parser_base* pParser;

	for (size_t i = 0; i < CFlChatConfig::s_iConfigSize; ++i)
	{
		const auto& stConfigLoader = CFlChatConfig::GetConfigLoader()[i];
		//pParser为子类得对象
		pParser = stConfigLoader.m_pParserGetFunc(pConfig);
		stRet = pParser->Load(stConfigLoader.m_pFileName);

		if (stRet.first == false)
		{
			FL_CHAT_LOG_INS->GetLogger()->error("{} load fail!", stConfigLoader.m_pFileName);
			return false;
		}

		std::stringstream stream;
		stream << __FILE__ << ":" << __LINE__ << "{" << __FUNCTION__ << "}" << stConfigLoader.m_pFileName<< "|MSG:" << stRet.second;
		FL_CHAT_LOG_INS->GetLogger()->info("{}", stream.str());
	}
	return true;
}

bool    
FLChatService::CreateRedisIns()
{
	FL_CHAT_REDIS_INS->SetRedisInfo("127.0.0.1", "123", 6379, 1);
	//程序结束时候释放redis连接
	if(FL_CHAT_REDIS_INS->Connect())
		return true;
	return false;
}

bool    
FLChatService::ConnectDbServer(struct event_base* base)
{
	struct bufferevent *pDbServerBev = bufferevent_socket_new(base, -1, BEV_OPT_CLOSE_ON_FREE);
	if (pDbServerBev == nullptr)
	{
		FL_CHAT_LOG_INS->GetLogger()->error("create db_server bev error!");
		return false;
	}
	struct sockaddr_in stDbSin;
	memset(&stDbSin, 0, sizeof(stDbSin));
	stDbSin.sin_family = AF_INET;
	stDbSin.sin_port = htons(9994);
	auto iDbSocketFd = bufferevent_socket_connect(pDbServerBev, (struct sockaddr*)&stDbSin, sizeof(stDbSin));
	if (iDbSocketFd < 0)
	{
		FL_CHAT_LOG_INS->GetLogger()->error("connect db_server error!");
		return false;
	}

	/*
	 * bufferevent中回调函数触发的条件与普通的event回调函数触发的条件不同(普通的事件在底层传输端口已经就绪，可读或可写时就会执行回调函数，而 bufferevent 是在读取或写入了一定量的数据后才会调用回调函数)
	 * 默认读取低水位为0,读取只要大于0触发conn_read_event,
	 * 默认读取高水位为bufferevent中evbuffer缓冲区容量(无限),超过高水位不读
	 * 默认写入低水位为0,evbuffer被清空时,触发写操作
	 * */
	bufferevent_setcb(pDbServerBev, FLChatCallBack::ReadDbServerCallback, FLChatCallBack::WriteDbServerCallback, FLChatCallBack::EventDbServerCallback, NULL);
	//启用bufferevent读写事件
	bufferevent_enable(pDbServerBev, EV_WRITE);
	bufferevent_enable(pDbServerBev, EV_READ);
	FL_CHAT_MYSQL_BEV_INS->SetDbServerBev(pDbServerBev);
	return true;
}

void 
FLChatService::EpollRunning(int iArgc, char** pArgv)
{
    //使用默认event_base
	struct event_base* base = event_base_new();
	if(base == nullptr)
	{
		FL_CHAT_LOG_INS->GetLogger()->error("could not initialize libevent!");
		return;
	}

	//根据操作系统和需求自动选择合适的select|poll|epoll
	FL_CHAT_LOG_INS->GetLogger()->info("starting libevent:{}", event_get_version());

	auto enEventFeature = event_base_get_features(base);
	if ((enEventFeature & EV_FEATURE_ET)) 
		FL_CHAT_LOG_INS->GetLogger()->info("Edge-triggered events are supported.");
	else if ((enEventFeature & EV_FEATURE_O1))
		FL_CHAT_LOG_INS->GetLogger()->info("O(1) event notification is supported.");
	else if ((enEventFeature & EV_FEATURE_FDS)) 
		FL_CHAT_LOG_INS->GetLogger()->info("All FD types are supported.");

	////connect db_server////
	if (!ConnectDbServer(base))
	{
		FL_CHAT_LOG_INS->GetLogger()->error("connect db_server fail!");
		return;
	}

	struct sockaddr_in sin;
	memset(&sin, 0, sizeof(sin));
	sin.sin_family = AF_INET;
	sin.sin_port = htons(CFlChatConfig::GetSystemConfig().m_iBindPort);

	//链接监听器
	/* 第四个参数详解: LEV_OPT_LEAVE_SOCKETS_BLOCKING(将默认非阻塞禁止)
	 * 		   LEV_OPT_CLOSE_ON_FREE(释放监听器,关闭底层套接字) 
	 * 		   LEV_OPT_CLOSE_ON_EXEC(底层套接字设置为FD_CLOEXEC)
	 * 		   LEV_OPT_REUSEABLE(可立即绑定同一端口)
	 * 		   LEV_OPT_THREADSAFE(线程安全)*/
	struct evconnlistener* listener = evconnlistener_new_bind(base,
			FLChatCallBack::ListenerCallback,          //新连接的回调函数
			(void*)base,                               //传递给回调函数 
			LEV_OPT_REUSEABLE|LEV_OPT_CLOSE_ON_FREE, 
			-1,                                        //listen参数,负数试图挑选一个最好值
			(struct sockaddr*)&sin, sizeof(sin));

	if (listener == nullptr)
	{
		FL_CHAT_LOG_INS->GetLogger()->error("Could not create a listener!");
		return;
	}

	//创建所有定时器任务
	FLChatTimer::CreateAllTimer(base);

	//监听去发生错误回调
	evconnlistener_set_error_cb(listener, FLChatCallBack::AcceptErrorCallback);
	//事件循环(默认event_loop)
	event_base_dispatch(base);
	//释放链接监听器
	evconnlistener_free(listener);
	event_base_free(base);
	return;
}