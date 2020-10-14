#ifndef __FL_CHAT_TIMER_H__
#define __FL_CHAT_TIMER_H__
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>

class FLChatTimer
{
public:
    static bool CreateTimer(event_base* pBase, int iSec, int iUsec, bool bRepeat, void (*pTimerCallBack)(evutil_socket_t, short, void *), void *arg);
    static bool CreateAllTimer(event_base *pBase);
};


#endif /* __FL_CHAT_TIMER_H__ */