/* 
 * File:   fl_chat_config.h
 * Author: Tadpole
 *
 * Created on 2020年8月3日, 下午15:06
 */

#ifndef __FL_CHAT_CONFIG_H__
#define __FL_CHAT_CONFIG_H__
#include "fl_chat_system_config.h"



/*
    通过宏创建配置对象,以供读取配置文件和使用配置内存数据
*/
#define DECLARE_CONFIG_PARSER(class_name, func_name, member_name) \
public: \
    static const class_name& func_name() { return (m_pConfig->member_name); } \
    static fl_chat_config_parser_base* func_name##Parser(CFlChatConfig* pConfig) { return (pConfig->func_name##Parser()); } \
    class_name* func_name##Parser() { return (&(member_name)); } \
private: \
    class_name member_name; \

///////////////////////////////////////////////////////////////////////////////////////////////
class CFlChatConfig
{
public:
    CFlChatConfig() { }

    using fl_chat_get_parser_func_t = fl_chat_config_parser_base* (*)(CFlChatConfig* pConfig);

    struct config_loader_t
    {
        const char*                    m_pFileName;
        fl_chat_get_parser_func_t      m_pParserGetFunc;
    };

    static CFlChatConfig* GetConfig() { return m_pConfig; }
    static void SetConfig(CFlChatConfig* pConfig) { m_pConfig = pConfig; }
    static config_loader_t* GetConfigLoader() { return (CONFIG_LOADER_LIST); }
private:
    DECLARE_CONFIG_PARSER(fl_chat_system_config_parser_t, GetSystemConfig, m_stSystemConfig)
public:
    static size_t s_iConfigSize;

private:
    static config_loader_t                             CONFIG_LOADER_LIST[];

    static CFlChatConfig*                              m_pConfig;
};





#endif /*__FL_CHAT_CONFIG_H__*/