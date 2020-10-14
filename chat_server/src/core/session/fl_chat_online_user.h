#ifndef __FL_CHAT_ONLINE_USRE_H__
#define __FL_CHAT_ONLINE_USER_H__

#include <cstdlib>
#include <set>
#include <string>
#include <unordered_map>

class CFlChatOnlineUser
{
public:
	enum CONST_VAR
	{
            DEFAULT_HASHMAP_SIZE = 100000
	};

	typedef struct user_info_s
	{
		user_info_s() : m_usClientPort(0), m_strClientIP("127.0.0.1"), m_iLoginTime(0), m_pBev(nullptr){}
            unsigned short      m_usClientPort;
            std::string         m_strClientIP;
            int                 m_iLoginTime;
			struct bufferevent *m_pBev;
	}user_info_t;

	using container_type = std::unordered_map<int32_t, user_info_t>;

	using iterator = container_type::iterator;

	using const_iterator = container_type::const_iterator;

	using size_type = container_type::size_type;

public:
	static CFlChatOnlineUser&        GetInstance();

	const_iterator              Begin() const;

	const_iterator              End() const;

	size_type                   GetUserNum() const;

	const_iterator              GetUserInfo(int iUserId) const;

	std::pair<iterator, bool>   AddUser(int iUserId, const user_info_t& stUserInfo);

    std::pair<iterator, bool>   GetUser(int iUserId);

	bool                        DelUser(int iUserId);

	void UpdateUserOnlineTime();

private:
	CFlChatOnlineUser();

private:
	container_type              m_stOnlineUserContainer;

	static CFlChatOnlineUser*   m_pOnlineUser;
};


#endif /* __FL_CHAT_ONLINE_USER_H__  */