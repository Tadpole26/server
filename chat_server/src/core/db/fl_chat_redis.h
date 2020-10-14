#ifndef __FL_CHAT_REDIS_H__
#define __FL_CHAT_REDIS_H__ 

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>
#include "spdlog/sinks/daily_file_sink.h"
#include "hiredis/hiredis.h"
#include "tc_singleton.h"
#include "fl_chat_redis.h"

struct FLChatRedisCallBackBase
{
public:
	virtual bool ExecuteArray(const size_t total, const size_t pos, const char* str, const size_t len) = 0;
};


class FLChatRedis
{
public:
	FLChatRedis() = default;
	FLChatRedis& operator=(const FLChatRedis& ) = delete;
	FLChatRedis& operator=(const FLChatRedis& ) volatile = delete;
	~FLChatRedis() = default;
public:
	inline void SetRedisInfo(const std::string& stIp, const std::string& stPasswd, const int iPort, const int iTimeout)
	{
		m_stRedisIp = stIp;
		m_stRedisPasswd = stPasswd;
		m_iRedisPort = iPort;
		m_iRedisTimeout = iTimeout;
	}
	//获取服务器ip
	inline const std::string& GetIp() const { return m_stRedisIp; }
	//获取服务器授权密码
	inline const std::string& GetPasswd() const { return m_stRedisPasswd; }
	//获取服务器port
	inline int GetPort() { return m_iRedisPort; }
	//获取redis连接
	inline redisContext* GetContext() { return m_pContext; }
public:
	//创建一个不带超时的连接
	bool Connect();
	//断开连接
	void DisConnect();
	//释放查询结果
	void FreeReply();
	//执行命令
	bool Execute(FLChatRedisCallBackBase& cCallBackObj, const char* format, ...);
protected:
	redisContext* m_pContext;
	redisReply* m_pReply;
private:
	std::string m_stRedisIp;
	std::string m_stRedisPasswd;
	int m_iRedisPort;
	int m_iRedisTimeout;
};



using FL_CHAT_REDIS_INS_TYPE = taf::TC_Singleton<FLChatRedis>;

#define FL_CHAT_REDIS_INS FL_CHAT_REDIS_INS_TYPE::getInstance()

#endif /* __FL_CHAT_REDSI_H__ */