#ifndef __FL_CHAT_LOG_H__
#define __FL_CHAT_LOG_H__ 

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>
#include "spdlog/sinks/daily_file_sink.h"
#include "tc_singleton.h"

class FLChatLog
{
private:
    std::shared_ptr<spdlog::logger> m_pLogger;
public:
    inline void SetLogInfo(std::shared_ptr<spdlog::logger>& pLogger)
	{
        m_pLogger = pLogger;
	}

    inline std::shared_ptr<spdlog::logger>& GetLogger()
    {
        return m_pLogger;
    }
};
using FL_CHAT_LOG_INS_TYPE = taf::TC_Singleton<FLChatLog>;

#define FL_CHAT_LOG_INS FL_CHAT_LOG_INS_TYPE::getInstance()

#endif /* __FL_CHAT_LOG_H__ */