#include "fl_chat_timer.h"
///////封装定时器///////////
bool FLChatTimer::CreateTimer(event_base* pBase, int iSec, int iUsec, bool bRepeat, void (*pTimerCallBack)(evutil_socket_t, short, void *), void *arg)
{
	if (pBase == nullptr)
        return false;
	if ((iSec == 0) && (iUsec == 0))
		return false;

	struct timeval stTimeout;

	/* 初始化事件
	 *     * base：event_base类型，event_base_new的返回值
	 *     * fd：监听的fd，listen的fd。 定时事件fd为 -1
	 *     * what：事件的类型及属性 EV_PERSIST - 永久事件，使得event_add永久生效，直到event_del调用
	 *     * cb：绑定的回调函数
	 *     * arg：给回调函数的参数
	 */
	struct event *pEv = event_new(pBase, -1, bRepeat ? EV_PERSIST : 0, pTimerCallBack, arg);

	if (pEv)
	{
		stTimeout.tv_sec = iSec;       // 秒
		stTimeout.tv_usec = iUsec;     // 微秒
		/* 激活事件
		 * 如果是一个未注册'ev'，调用'event_add'函数会注册该事件
		 * 如果是一个注册过的'ev'，调用该函数会在tv时间后重新注册该事件
		 */
		event_add(pEv, &stTimeout);
		return true;
	}   
	return false;
}

bool FLChatTimer::CreateAllTimer(event_base *pBase)
{
    return true;
}