#include "fl_chat_config.h"

CFlChatConfig* CFlChatConfig::m_pConfig = nullptr;

CFlChatConfig::config_loader_t CFlChatConfig::CONFIG_LOADER_LIST[] =
{
    { "system.xml",                   CFlChatConfig::GetSystemConfigParser                 },
};

size_t CFlChatConfig::s_iConfigSize = sizeof(CFlChatConfig::CONFIG_LOADER_LIST) / sizeof(CFlChatConfig::config_loader_t);