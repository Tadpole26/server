#include "fl_chat_redis.h"

bool FLChatRedis::Connect()
{
	m_pContext = redisConnect(m_stRedisIp.c_str(), m_iRedisPort);
	if (m_pContext == nullptr || m_pContext->err)
	{
        spdlog::get("daily_logger")->error("connect redis error, {}", m_pContext->errstr);
		return false;
	}
    spdlog::get("daily_logger")->info("connect redis success!");
    return true;
}

void FLChatRedis::DisConnect()
{
	if (m_pContext)
    {
        spdlog::get("daily_logger")->info("disconnect redis success!");
        redisFree(m_pContext);
    }
    else
        spdlog::get("daily_logger")->error("disconnect redis error!");
}

void FLChatRedis::FreeReply()
{
	if (m_pReply)
	{
        spdlog::get("daily_logger")->info("free redis reply success!");
		freeReplyObject(m_pReply);
	}
	else
        spdlog::get("daily_logger")->error("free redis reply fail!");
}

bool FLChatRedis::Execute(FLChatRedisCallBackBase& cCallBackObj, const char* format, ...)
{

	va_list arg;
	va_start(arg, format);
	m_pReply = (redisReply*)redisvCommand(m_pContext, format, arg);
	if (m_pReply == nullptr)
	{
		spdlog::get("daily_logger")->error("get redis reply is nullptr!");
		return false;
	}

	if (m_pReply->type == REDIS_REPLY_ERROR)
	{
		spdlog::get("daily_logger")->error("get redis reply error, {}", m_pReply->str);
		return false;
	}

	cCallBackObj.ExecuteArray(m_pReply->len, m_pReply->elements, m_pReply->str, m_pReply->len);
	return true;
}

