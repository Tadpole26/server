#ifndef __FL_CHAT_CACHE_COMMON_H__
#define __FL_CHAT_CACHE_COMMON_H__

//////读取mysql数据到redis内存//////////

class CFlChatCacheCommon
{
public:
    static void LoadUserData();
};

#endif /* __FL_CHAT_CACHE_COMMON_H__  */