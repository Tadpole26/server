#include "fl_chat_system_config.h"

std::pair<bool, std::string> fl_chat_system_config_parser_t::Load(const std::string& stXmlFileName)
{
    try
    {
        using namespace boost::property_tree;
        
        ptree pt;
        read_xml(stXmlFileName.c_str(), pt);
        //ptree& ptRoot = pt.get_child("root");
        ptree& ptInfo = pt.get_child("root.info");
        //std::string stInfo = ptInfo.get<std::string>("<xmlattr>.tag");
        m_stBindIp = ptInfo.get<std::string>("<xmlattr>.bind_ip");
        m_iBindPort = ptInfo.get<int>("<xmlattr>.bind_port");

        //LOG_TRACE_DEBUG << "m_stBindIp:" << m_stBindIp << ",m_iBindPort:" << m_iBindPort << std::endl;

        ptree& ptTimeSet = pt.get_child("root.time_set");
        BOOST_FOREACH(ptree::value_type& stValue, ptTimeSet)
        {
            if (stValue.first == "item")
            {
                fl_chat_system_time_set_info_t stData(stValue.second.get<int>("<xmlattr>.begin_time"), stValue.second.get<int>("<xmlattr>.end_time"));
                m_stTimeSetMap.insert(std::pair<uint32_t, fl_chat_system_time_set_info_t> (stValue.second.get<int>("<xmlattr>.id"), stData));
            }
        }

        ptree& ptPetList = pt.get_child("root.pet_list");
        BOOST_FOREACH(ptree::value_type& stValue, ptPetList)
        {
            if (stValue.first == "pet")
            {
                fl_chat_system_pet_info_t stData(stValue.second.get<int>("<xmlattr>.item_type"), 
                                                    stValue.second.get<int>("<xmlattr>.item_id"), 
                                                    stValue.second.get<int>("<xmlattr>.item_num"));
                m_stPetMap.insert(std::pair<uint32_t, fl_chat_system_pet_info_t> (stValue.second.get<int>("<xmlattr>.id"), stData));
            }
        }

        return (std::pair<bool, std::string>(true, "OK"));
    }
    catch (boost::property_tree::ptree_bad_path& e)
    {
        return (std::pair<bool, std::string>(false, e.what()));
    }
    catch (boost::property_tree::ptree_bad_data& e)
    {
        return (std::pair<bool, std::string>(false, e.what()));
    }
}