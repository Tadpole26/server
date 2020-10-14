/* 
 * File:   fl_chat_login_processor.h
 * Author: Tadpole
 *
 * Created on 2020年8月8日
 */

#ifndef __FL_CHAT_LOGIN_PROCESSOR_H__
#define	__FL_CHAT_LOGIN_PROCESSOR_H__

#include "src/core/process/fl_chat_processor_base.h"
#include "src/core/process/fl_chat_cmd_processor_factory.h"
#include "src/core/db/fl_chat_redis.h"
#include "src/core/log/fl_chat_log.h"

class CRkChatLoginProcessor : public CFlChatProcessorBase
{
public:
	CRkChatLoginProcessor(uint16_t usCmd, const std::string& strCmdName)
		: CFlChatProcessorBase(usCmd, strCmdName)
	{
	}

protected:
    bool DoUserRun(const char* pBuffer, unsigned int uiLength);

	bool ReadRedisNameInfo(std::string& stName);
};

#endif	/* __FL_CHAT_LOGIN_PROCESSOR_H__ */



