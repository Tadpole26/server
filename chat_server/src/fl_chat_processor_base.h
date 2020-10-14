/* 
 * File:   fl_chat_processor_base_h
 * Author: Tadpole
 *
 * Created on 20120.8.6
 */
#ifndef __FL_CHAT_PROCESSOR_BASE_H__
#define __FL_CHAT_PROCESSOR_BASE_H__
#include <memory>
#include <vector>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/listener.h>
#include <event2/util.h>
#include <event2/event.h>
#include <cstring>
#include "fl_chat_client_header.h"
#include "fl_chat_online_user.h"
#include "fl_chat_errcode.h"

#include <spdlog/spdlog.h>
#include <spdlog/fmt/bundled/format.h>
#include "spdlog/sinks/daily_file_sink.h"

#define SEND_ERRCODE_AND_RET(ERROR_CODE) \
{	\
SendToClient(ERROR_CODE); \
return (false);	\
}

class CFlChatProcessorBase
{
public:
    CFlChatProcessorBase(uint16_t usCmd, const std::string& strCmdName);

    virtual ~CFlChatProcessorBase();

    void SetClientUser(int32_t iUserId, struct bufferevent* pBev);

    bool DoProcess(const char* pBuffer, unsigned int uiLength);

protected:    
    virtual bool DoUserRun(const char* pBuffer, unsigned int uiLength) = 0;

public:
    template <class PROTOBUF_T>
	void SendToClient(PROTOBUF_T& stResultData, int iErrcode);

    void SendToClient(int iErrorCode);

    template <class PROTOBUF_T>
	void SendToOtherClient(int iUserId, PROTOBUF_T& stResultData, int iErrcode);

    static void ReferenceCleanCallBack(const void *data, long unsigned int datalen, void *extra);
    template <class PROTOBUF_T>
	void BroadcastToClient(PROTOBUF_T& stResultData);

protected:
	uint16_t	m_usCmd;
	std::string m_strCmdName;
	int32_t		m_iUserId;              //用户id
    struct bufferevent* m_pBev;         //用户读写缓冲区
}; 



/////////////////////////构造智能指针和对应得constructor&deletor//////////////////////////////
template <class T>
class CFlDefaultProcessorCreator
{
public:
    static T* Create(uint16_t usCmd, const std::string& strCmdName)
    {
        return (new T(usCmd, strCmdName));
    }
    
    static void Destory(CFlChatProcessorBase* pProcessor)
    {
        delete pProcessor;
    }
};

typedef std::shared_ptr<CFlChatProcessorBase> processor_base_ptr_type;

template <class T, class CreatorT = CFlDefaultProcessorCreator<T> >
class CFlChatProcessorFactory
{
public:
    static processor_base_ptr_type Create(uint16_t usCmd, const std::string& strCmdName)
    {
        //TAF_STATIC_CHECK(SUPERSUBCLASS(CFlChatProcessorBase, T), processor_factory_type_can_not_convert);
        
        return (processor_base_ptr_type(CreatorT::Create(usCmd, strCmdName), CreatorT::Destory));
    };
};

#endif /*   __FL_CHAT_PROCESSOR_BASE_H__  */