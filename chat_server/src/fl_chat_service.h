/* 
 * File:   fl_chat_service.h
 * Author: Tadpole
 *
 * Created on 2020年8月3日, 上午11:31
 */

#ifndef __FL_CHAT_SERVICE_H__
#define __FL_CHAT_SERVICE_H__
#include "fl_chat_config.h"
#include "fl_chat_net_callback.h"
#include "fl_chat_timer.h"
#include "fl_chat_redis.h"
#include "fl_chat_net_bev.h"
#include "fl_chat_log.h"

#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <signal.h>
#include "tc_server_base.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>
#include "spdlog/sinks/daily_file_sink.h"


class FLChatService : public taf::CTCServerBase
{
public:
    FLChatService();

    bool    BeforeRun(int iArgc, char** pArgv);

    bool    LoadConfig();

    bool    CreateRedisIns();

    void    RealRun(int iArgc, char** pArgv) override;

    /*  连接db_server */
    bool    ConnectDbServer(struct event_base* base);

    void    EpollRunning(int iArgc, char** pArgv);

    bool    ReadRedis(std::string& stName);

public:
};

#endif
