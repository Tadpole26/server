#include "fl_chat_online_user.h"

CFlChatOnlineUser* CFlChatOnlineUser::m_pOnlineUser = nullptr;

CFlChatOnlineUser::CFlChatOnlineUser() : m_stOnlineUserContainer()
{
	m_stOnlineUserContainer.reserve(DEFAULT_HASHMAP_SIZE);
}

CFlChatOnlineUser& CFlChatOnlineUser::GetInstance()
{
	if(nullptr == m_pOnlineUser)
	{
		m_pOnlineUser = new CFlChatOnlineUser();
	}

	return (*m_pOnlineUser);
}

CFlChatOnlineUser::const_iterator CFlChatOnlineUser::Begin() const
{
	return (m_stOnlineUserContainer.begin());
}

CFlChatOnlineUser::const_iterator CFlChatOnlineUser::End() const
{
	return (m_stOnlineUserContainer.end());
}

CFlChatOnlineUser::size_type CFlChatOnlineUser::GetUserNum() const
{
	return (m_stOnlineUserContainer.size());
}

CFlChatOnlineUser::const_iterator CFlChatOnlineUser::GetUserInfo(int iUserId) const
{
	return (m_stOnlineUserContainer.find(iUserId));
}


std::pair<CFlChatOnlineUser::iterator, bool> 					
CFlChatOnlineUser::AddUser(int iUserId, const user_info_t& stUserInfo)
{
    return (m_stOnlineUserContainer.insert(std::pair<int, user_info_t>(iUserId, stUserInfo)));
}

//std::pair<CRkLogicUser::iterator, bool>
//CFlChatOnlineUser::GetUser(int iUserId)
//{
//    auto stIter = m_stOnlineUserContainer.find(iUserId);
//    if (stIter != m_stOnlineUserContainer.end())
//    {
//        return (std::make_pair(stIter, true));
//    }
//    return (std::make_pair(stIter, false));
//}

bool 					
CFlChatOnlineUser::DelUser(int iUserId)
{
    auto stIter = m_stOnlineUserContainer.find(iUserId);
    if (stIter != m_stOnlineUserContainer.end())
    {
        //log
        m_stOnlineUserContainer.erase(iUserId);
    }
    
	return (true);
}


//void CRkLogicUser::UpdateUserOnlineTime()
//{
//    /*
//	int32_t iNow = CRkLogicCommon::GetSec();
//	for (auto iter = m_stOnlineUserContainer.begin(); iter != m_stOnlineUserContainer.end(); ++iter)
//		iter->second.m_iLastOnlineTime = iNow;
//        */
//}


