#ifndef __FL_CHAT_CALLBACK_H__
#define __FL_CHAT_CALLBACK_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

#include "fl_chat_client_header.h"
#include "fl_gmsv_cmd.h"
#include "fl_chat_cmd_processor_factory.h"
#include "fl_chat_log.h"

struct fl_chat_net_all_server_extra_data_t
{
    fl_chat_net_all_server_extra_data_t() : m_pDbServerBev(nullptr) { }

    struct bufferevent* m_pDbServerBev;
};

class FLChatCallBack
{
public:
///////结束连接和错误事件///
static void EventClientServerCallback(struct bufferevent *bev, short events, void *ctx);
///////读事件//////////////
static void ReadClientServerCallback(struct bufferevent *bev, void *ctx);
///////写事件//////////////
static void WriteClientServerCallback(struct bufferevent* bev, void* user_data);
///////监听事件////////////
static void ListenerCallback(struct evconnlistener* listener, evutil_socket_t fd, struct sockaddr* sa, int socklen, void* user_data);
///////连接错误事件////////
static void AcceptErrorCallback(struct evconnlistener *listener, void *ctx);
///////定时任务回调////////
//static void test_time_callback(evutil_socket_t fd, short what, void *arg);
///////定时器创建//////////
//bool CreateTimer(event_base *base,int sec,int usec,bool repeat,void (*func)(evutil_socket_t ,short ,void *),void *arg);
//////db_server回调///////
static void ReadDbServerCallback(struct bufferevent *bev, void *ctx);
static void WriteDbServerCallback(struct bufferevent* bev, void* user_data);
static void EventDbServerCallback(struct bufferevent *bev, short events, void *ctx);
};


#endif