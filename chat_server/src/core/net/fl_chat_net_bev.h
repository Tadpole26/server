#ifndef __FL_CHAT_NET_BEV_H__
#define __FL_CHAT_NET_BEV_H__
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <event2/bufferevent.h>

class FLChatConnectDbServerBev
{
public:
    inline void SetDbServerBev(struct bufferevent* pDbServerBev)
    {
        m_pDbServerBev = pDbServerBev;
    }
public:
    struct bufferevent* m_pDbServerBev;
};
using FL_CHAT_MYSQL_BEV_INS_TYPE = taf::TC_Singleton<FLChatConnectDbServerBev>;

#define FL_CHAT_MYSQL_BEV_INS FL_CHAT_MYSQL_BEV_INS_TYPE::getInstance()

#endif /* __FL_CHAT_NET_BEV_H__ */