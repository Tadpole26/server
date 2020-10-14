#pragma once

#include <cstdint>
#include <string>
#include <functional>
#include <algorithm>
#include <sstream>
#include <set>
#include <map>
#include <vector>
#include <string>
#include <unordered_map>
#include <iostream>

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/foreach.hpp>


struct fl_chat_config_parser_base
{
    using get_xml_content_callback_type = std::function<const std::string&(const std::string&)>;

	fl_chat_config_parser_base() : m_stGetXMLContentCallback(GetEmptyXMLContent) { } ;

	virtual ~fl_chat_config_parser_base() {  }

	virtual std::pair<bool, std::string> Load(const std::string& strXMLContent) = 0;

	void SetGetXMLContentCallback(get_xml_content_callback_type stCallback) { m_stGetXMLContentCallback = stCallback; };

private:
	static const std::string& GetEmptyXMLContent(const std::string& strName)
	{
		(void)strName;
		static std::string strEmptyContent;
		return (strEmptyContent);
	}

protected:
	get_xml_content_callback_type   m_stGetXMLContentCallback;
};