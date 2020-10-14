/* 
 * File:   fl_chat_cmd_processor_factory.h
 * Author: Tadpole
 *
 * Created on 2020年8月6日
 */

#ifndef __FL_CHAT_CMD_PROCESSOR_FACTORY_H__
#define __FL_CHAT_CMD_PROCESSOR_FACTORY_H__
#include "src/core/process/fl_chat_processor_base.h"
#include "src/core/log/fl_chat_log.h"
#include "fl_gmsv_cmd.h"
#include <functional>
/*
    工厂模式 
    将所有协议号和对应执行得函数绑定
*/

///构造创建子类放入map中
#define _REGISTER_CMD_FACTORY_WITH_LINE_NUM(CMD, CMD_NAME, CLASS_NAME, LINE_NUM)                                                                          \
struct _static_##CLASS_NAME##LINE_NUM                                                                                            \
{                                                                                                                      \
    _static_##CLASS_NAME##LINE_NUM()                                                                                             \
    {                                                                                                                  \
         CFlChatCmdMap::GetInstance().RegisterProcessorFactory((int)CMD, CMD_NAME, &CFlChatProcessorFactory<CLASS_NAME>::Create); \
    }                                                                                                                  \
};                                                                                                                     \
static _static_##CLASS_NAME##LINE_NUM g_stInstance##CLASS_NAME##LINE_NUM;

#define REGISTER_CMD_FACTORY_WITH_LINE_NUM(CMD, CLASS_NAME, LINE_NUM) _REGISTER_CMD_FACTORY_WITH_LINE_NUM(CMD, #CMD, CLASS_NAME, LINE_NUM)

#define REGISTER_CMD_FACTORY(CMD, CLASS_NAME) REGISTER_CMD_FACTORY_WITH_LINE_NUM(CMD, CLASS_NAME, __LINE__)

#define FL_CMD_CONTAINER  CFlChatCmdMap::GetInstance()


class CFlChatCmdMap
{
public:
    using fl_chat_processor_factory_type = processor_base_ptr_type (*)(uint16_t usCmd, const std::string& strCmdName);
   
public:
	static CFlChatCmdMap&			GetInstance();

	processor_base_ptr_type			GetProcessor(int iCmd);
    
    void                            RegisterProcessorFactory(uint16_t usCmd, const std::string& strCmdName, fl_chat_processor_factory_type pFactory);

private:
	CFlChatCmdMap();

private:
	static CFlChatCmdMap*                           m_pChatCmdMap;

private:
    processor_base_ptr_type                         m_stErrorProcessor;

    std::vector<std::function<processor_base_ptr_type()>>    m_stCmdMapProcessFactory;
};

#endif /* __FL_CHAT_CMD_PROCESSOR_FACTORY_H__ */