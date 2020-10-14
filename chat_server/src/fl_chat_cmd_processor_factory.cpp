#include "fl_chat_cmd_processor_factory.h"


CFlChatCmdMap* CFlChatCmdMap::m_pChatCmdMap = nullptr;

CFlChatCmdMap::CFlChatCmdMap()
{
	//m_stErrorProcessor = std::static_pointer_cast<CRkLogicProcessorBase>(std::make_shared<CRkLogicErrorProcessor>());

	const size_t uiArraySize = FlGmsvCmd:: CHAT_CMD_END - FlGmsvCmd:: CHAT_CMD_BEGIN + 1;
    m_stCmdMapProcessFactory.resize(uiArraySize);
}

CFlChatCmdMap&	
CFlChatCmdMap::GetInstance()
{
	if(nullptr == m_pChatCmdMap)
	{
		m_pChatCmdMap = new CFlChatCmdMap();
	}

	return (*m_pChatCmdMap);
}

processor_base_ptr_type	
CFlChatCmdMap::GetProcessor(int iCmd)
{
    int iMaxArrayIndex = FlGmsvCmd::CHAT_CMD_END - FlGmsvCmd::CHAT_CMD_BEGIN + 1;
	if((nullptr == m_pChatCmdMap) || (iCmd <= FlGmsvCmd::CHAT_CMD_BEGIN) 
       || (iCmd >= FlGmsvCmd::CHAT_CMD_END) || (iCmd - FlGmsvCmd::CHAT_CMD_BEGIN >= iMaxArrayIndex))
	{
		FL_CHAT_LOG_INS->GetLogger()->error("cmd is out of range, cmd range:{} ~ {}, cmd:{} ", FlGmsvCmd::CHAT_CMD_BEGIN, FlGmsvCmd::CHAT_CMD_END, iCmd);
	}

    if(nullptr == m_stCmdMapProcessFactory[iCmd - FlGmsvCmd::CHAT_CMD_BEGIN])
    {
        FL_CHAT_LOG_INS->GetLogger()->error("cmd is not register");
    }

    processor_base_ptr_type pProcessorObj = m_stCmdMapProcessFactory[iCmd - FlGmsvCmd::CHAT_CMD_BEGIN]();
    
    return (pProcessorObj);
}

void                            
CFlChatCmdMap::RegisterProcessorFactory(uint16_t usCmd, const std::string& strCmdName, fl_chat_processor_factory_type pFactory)
{
    if((usCmd >= FlGmsvCmd::CHAT_CMD_BEGIN) && (usCmd <= FlGmsvCmd:: CHAT_CMD_END) && (nullptr != pFactory))
    {
		m_stCmdMapProcessFactory[usCmd - FlGmsvCmd::CHAT_CMD_BEGIN] = std::bind(pFactory, usCmd, strCmdName);
    }
}


