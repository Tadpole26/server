#include "fl_chat_login_processor.h"

REGISTER_CMD_FACTORY(FlGmsvCmd::CHAT_CMD_LOGIN, CRkChatLoginProcessor)

bool CRkChatLoginProcessor::ReadRedisNameInfo(std::string& stName)
{
    return true;
}


bool CRkChatLoginProcessor::DoUserRun(const char* pBuffer, unsigned int uiLength)
{
    switch (m_usCmd)
	{
        case FlGmsvCmd::CHAT_CMD_LOGIN:
        {
            FL_CHAT_LOG_INS->GetLogger()->info("CHAT_CMD_LOGIN");
            //第一个登录协议将在线client加载内存中
            CFlChatOnlineUser::user_info_t stUserInfo;
            FL_CHAT_LOG_INS->GetLogger()->info("CHAT_CMD_LOGIN1111");
            stUserInfo.m_pBev = m_pBev;
            FL_CHAT_LOG_INS->GetLogger()->info("CHAT_CMD_LOGIN2222");
            std::pair<CFlChatOnlineUser::iterator, bool> stRet;
            FL_CHAT_LOG_INS->GetLogger()->info("CHAT_CMD_LOGIN3333");
			stRet = CFlChatOnlineUser::GetInstance().AddUser(m_iUserId, stUserInfo);
            FL_CHAT_LOG_INS->GetLogger()->info("CHAT_CMD_LOGIN4444");
            if (stRet.second == false)
            {
                using namespace FL_CHAT_ERRCODE;
                FL_CHAT_LOG_INS->GetLogger()->error("insert user to user data fail {} !!!", m_iUserId);
                SEND_ERRCODE_AND_RET(LOGIN_ADD_ONLINE_MAP_FAIL)
            }

            break;
        }
    }
    return true;
}