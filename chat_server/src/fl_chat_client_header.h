#ifndef __FL_CHAT_CLIENT_HEADER_H__
#define __FL_CHAT_CLIENT_HEADER_H__ 
#pragma pack(push, 1)
enum MAX_PACKET_LEN
{
    MAX_CONNECTOR_PACKET = 4096
};

struct fl_client_proto_header_t
{
    fl_client_proto_header_t() : m_usCheckCode(0), m_usMaskCode(0), m_uiPacketLen(0), m_usCmdMain(0), m_usCmdSub(0), m_iUserId(0) { }
    
    //校验码
    unsigned short      m_usCheckCode;
    //报文掩码
    unsigned short      m_usMaskCode;   
    unsigned int        m_uiPacketLen;
    unsigned short      m_usCmdMain;
    unsigned short      m_usCmdSub;
    int                 m_iUserId;
    //服务器返回
    short               m_usSvrRsp;

};

#pragma pack()
#endif /* __FL_CHAT_CLIENT_HEADER_H__*/