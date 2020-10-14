#include "fl_chat_processor_base.h"

CFlChatProcessorBase::CFlChatProcessorBase(uint16_t usCmd, const std::string& strCmdName)
	: m_usCmd(usCmd), m_strCmdName(strCmdName), m_iUserId(0)  { };

CFlChatProcessorBase::~CFlChatProcessorBase() { };

void CFlChatProcessorBase::SetClientUser(int32_t iUserId, struct bufferevent* pBev)
{
	m_iUserId = iUserId;
    m_pBev = pBev;
}

bool CFlChatProcessorBase::DoProcess(const char* pBuffer, unsigned int uiLength)
{
    // 1  /////////////////////用户是否在在线列表里面/////////////////////////////////////////

    //2   ///////////////////////////////解包是否成功//////////////////////////////////////////////

   /* msgpack::unpacked stResult;
    if(uiLength > 0)
    {
        try
        {
            msgpack::unpack(&stResult, pBuffer, uiLength);
        }
        catch(const std::runtime_error& stEx)
        {
            return (false);
        }
    }
*/
    //3   /////////////////////////////////redis获取用户数据//////////////////////////////////////////

    //4   ////////////////////////////////逻辑代码///////////////////////////////////////////////////
    bool bRet = DoUserRun(pBuffer, uiLength);
	//RK_LOGIC_LATER_INS->execute();

    return (bRet);
}

template <class PROTOBUF_T>
void CFlChatProcessorBase::SendToClient(PROTOBUF_T& stResultData, int iErrcode)
{
    fl_client_proto_header_t stClientHead;
    if ((sizeof(stResultData) + sizeof(stClientHead)) > MAX_CONNECTOR_PACKET)
    {
        spdlog::get("daily_logger")->error("send to client bag too big!");
        return;
    }
    
    stClientHead.m_usCmdSub = m_usCmd;
	stClientHead.m_iUserId = m_iUserId;
	stClientHead.m_usSvrRsp = (short)iErrcode;
    //计算包体大小
    //std::string stResultDataToStr;
    //stResultData.SerializeToString(&stResultDataToStr);
    unsigned int uiBagBodyLen = (unsigned int)stResultData.ByteSize();
    void* pBagBodyBuffer[uiBagBodyLen] = {0};
    stResultData.SerializeToArray(pBagBodyBuffer, uiBagBodyLen);

    stClientHead.m_uiPacketLen = uiBagBodyLen;
	unsigned int uiBagHeadLen = sizeof(stClientHead);
    if(bufferevent_write(m_pBev, &stClientHead, sizeof(stClientHead)) == -1)
    {
        spdlog::get("daily_logger")->error("send to client write fail!");
        bufferevent_free(m_pBev);
        return;
    }

    if (bufferevent_write(m_pBev, pBagBodyBuffer, uiBagBodyLen) == -1)
    {
        spdlog::get("daily_logger")->error("send to client write fail!");
        bufferevent_free(m_pBev);
        return;
    }
}

void 
CFlChatProcessorBase::SendToClient(int iErrorCode)
{
    fl_client_proto_header_t stClientHead;
    
    stClientHead.m_usCmdSub = m_usCmd;
	stClientHead.m_iUserId = m_iUserId;
	stClientHead.m_usSvrRsp = (short)iErrorCode;
    stClientHead.m_uiPacketLen = 0;
	//unsigned int uiBagHeadLen = sizeof(stClientHead);
    if(bufferevent_write(m_pBev, &stClientHead, sizeof(stClientHead)) == -1)
    {
        spdlog::get("daily_logger")->error("send to client write fail!");
        bufferevent_free(m_pBev);
        return;
    }
}

template <class PROTOBUF_T>
void CFlChatProcessorBase::SendToOtherClient(int iUserId, PROTOBUF_T& stResultData, int iErrcode)
{
    const auto& stInstance = CFlChatOnlineUser::GetInstance();
    auto iterFind = stInstance.GetUserInfo(iUserId);
    if (iterFind == stInstance.End())
    {
        spdlog::get("daily_logger")->error("could not find online user!");
        bufferevent_free(m_pBev);
        return ;
    }

    fl_client_proto_header_t stClientHead;
    if ((sizeof(stResultData) + sizeof(stClientHead)) > MAX_CONNECTOR_PACKET)
    {
        spdlog::get("daily_logger")->error("send to client bag too big!");
        return;
    }
    
    stClientHead.m_usCmdSub = m_usCmd;
	stClientHead.m_iUserId = m_iUserId;
	stClientHead.m_usSvrRsp = (short)iErrcode;
    //计算包体大小
    //std::string stResultDataToStr;
    //stResultData.SerializeToString(&stResultDataToStr);
    //unsigned int uiBagBodyLen = (unsigned int)stResultDataToStr.size();
    unsigned int uiBagBodyLen = (unsigned int)stResultData.ByteSize();
    void* pBagBodyBuffer[uiBagBodyLen] = {0};
    stResultData.SerializeToArray(pBagBodyBuffer, uiBagBodyLen);

    stClientHead.m_uiPacketLen = uiBagBodyLen;
	unsigned int uiBagHeadLen = sizeof(stClientHead);
    if(bufferevent_write(iterFind->second.m_pBev, &stClientHead, sizeof(stClientHead)) == -1)
    {
        spdlog::get("daily_logger")->error("send to client write fail!");
        bufferevent_free(m_pBev);
        return;
    }

    if (bufferevent_write(iterFind->second.m_pBev, pBagBodyBuffer, uiBagBodyLen) == -1)
    {
        spdlog::get("daily_logger")->error("send to client write fail!");
        bufferevent_free(m_pBev);
        return;
    }

}


//每次refrence内存,drain得时候触发,判断是否广播结束,结束释放membuffer
void CFlChatProcessorBase::ReferenceCleanCallBack(const void *data, long unsigned int datalen, void *extra)
{
    //当全部广播结束 释放内存
    if (--*(int *)extra == 0)
        free(extra);
}

template <class PROTOBUF_T>
void CFlChatProcessorBase::BroadcastToClient(PROTOBUF_T& stResultData)
{
    //构造包头
    fl_client_proto_header_t stClientHead;
    stClientHead.m_usCmdSub = m_usCmd;
	stClientHead.m_iUserId = m_iUserId;
	stClientHead.m_usSvrRsp = 1;
    int iBagHeadLen = sizeof(stClientHead);
    //pb序列化包体
    //std::string stResultDataToStr;
    //stResultData.SerializeToString(&stResultDataToStr);
    //int iBagBodyLen = (int)stResultDataToStr.size();
    unsigned int uiBagBodyLen = (unsigned int)stResultData.ByteSize();
    void* pBagBodyBuffer[uiBagBodyLen] = {0};
    stResultData.SerializeToArray(pBagBodyBuffer, uiBagBodyLen);
    //在线玩家
    const auto& stInstance = CFlChatOnlineUser::GetInstance();
    int iOnlineUserNum = (int)stInstance.GetUserNum();

    //开辟共享内存membuffer,发送次数+包头+包体(减少向每个客户evbuffer中copy)
    char* pShareMemBuff = malloc(sizeof(int) + iBagHeadLen + uiBagBodyLen);
    if (pShareMemBuff)
    {
        *(int *)pShareMemBuff = iOnlineUserNum;
        //memcpy(pShareMemBuff, &iOnlineUserNum, sizeof(int));
        memcpy(pShareMemBuff + sizeof(int), &stClientHead, iBagHeadLen);
        memcpy(pShareMemBuff + sizeof(int) + iBagHeadLen, pBagBodyBuffer, uiBagBodyLen);

        for (auto stIter = stInstance.Begin(); stIter != stInstance.End(); ++stIter)
        {
            //获得evbuffer输出缓冲区
            struct evbuffer* output = bufferevent_get_output(stIter->second.m_pBev);
            // 第二个参数发送的数据起始的地方, 第三个参数发送的数据的真正大小
            evbuffer_add_reference(output, pShareMemBuff + sizeof(int), (iBagHeadLen + uiBagBodyLen), ReferenceCleanCallBack, pShareMemBuff);
        }
    }
}