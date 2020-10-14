/* 
 * File:   fl_chat_system_config.h
 * Author: Tadpole
 *
 * Created on 2020年8月3日, 上午16:37
 */
#pragma once

#ifndef __FL_CHAT_SYSTEM_CONFIG_H__
#define __FL_CHAT_SYSTEM_CONFIG_H__

#include "fl_chat_config_base.h"

struct fl_chat_system_time_set_info_t
{
	fl_chat_system_time_set_info_t() : m_uiBeginTime(0), m_uiEndTime(0) { }

	fl_chat_system_time_set_info_t(uint32_t uiBeginTime, uint32_t uiEndTime) : m_uiBeginTime(uiBeginTime), m_uiEndTime(uiEndTime) { }

    uint32_t m_uiBeginTime;
    uint32_t m_uiEndTime;
};

struct fl_chat_system_pet_info_t
{
    fl_chat_system_pet_info_t() :  m_uiItemType(0), m_uiItemId(0), m_uiItemNum(0) { }

    fl_chat_system_pet_info_t(int uiItemType, int uiItemId, int uiItemNum) :  
                                m_uiItemType(uiItemType), m_uiItemId(uiItemId), m_uiItemNum(uiItemNum) { }

    int m_uiItemType;
    int m_uiItemId;
    int m_uiItemNum;
};

struct fl_chat_system_config_parser_t : public fl_chat_config_parser_base
{
    fl_chat_system_config_parser_t() : m_stBindIp(""), m_iBindPort(0), m_stTimeSetMap(), m_stPetMap() { }

    std::string m_stBindIp;
    int m_iBindPort;
    std::map<uint32_t, fl_chat_system_time_set_info_t> m_stTimeSetMap;
    std::map<uint32_t, fl_chat_system_pet_info_t> m_stPetMap;

    std::pair<bool, std::string> Load(const std::string& strXMLContent) override;
};


#endif /* __FL_CHAT_SYSTEM_CONFIG_H__*/