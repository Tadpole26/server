#include "fl_chat_service.h"

int main(int argc, char** argv)
{
    std::string strSvrMode;
    if(argc >= 2)
    {
        strSvrMode = std::string(argv[1]);
    }

	FLChatService service;
    if("debug" == strSvrMode)
    {
		service.RunEmbed(argc, argv);
    }
    else
    {
        //支持coredump&&Daemon&&realRun 
		service.RunAlone(argc, argv);
    }

	return (0);
}


