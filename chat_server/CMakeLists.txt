cmake_minimum_required(VERSION 3.11)
project(chat_serv)
set(CMAKE_CXX_STANDARD 11)
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -ggdb")

#源文件路径
#AUX_SOURCE_DIRECTORY(src/service/ SRC)
#AUX_SOURCE_DIRECTORY(/mnt/hgfs/Server-C++/chat_server/src/service/ SRC)

#声明main函数入口文件
set(SRC src/proto/CommonProto.pb.cc
		src/core/process/fl_chat_cmd_processor_factory.cpp
		src/core/config/fl_chat_config.cpp
		src/core/service/fl_chat_service.cpp
		src/service/fl_chat_login_processor.cpp
		src/fl_chat_main.cpp
		src/core/net/fl_chat_net_callback.cpp
		src/core/session/fl_chat_online_user.cpp
		src/core/process/fl_chat_processor_base.cpp
		src/core/service/fl_chat_service.cpp
		src/config/fl_chat_system_config.cpp
		src/core/timer/fl_chat_timer.cpp
		src/core/db/fl_chat_redis.cpp
		)

#声明头文件路径
set(
        INCLUDE_DIR
        ./
        /mysql/app/mysql80/include
        /usr/local/include
        /usr/local/include/public_include/protocol
        /usr/local/include/public_include/util
	/mnt/hgfs/Server-C++/public_include/protocol
	/mnt/hgfs/Server-C++/public_include/util
)

#链接库目录
set(
        LINK_DIR
        ./
        /usr/local/lib
)

#链接库
set(
        LINK_LIB
        pthread rt dl -rdynamic libboost_filesystem.a libboost_date_time.a libboost_system.a libboost_atomic.a crypto event protobuf libutil.a hiredis
)

#编译参数
set(
        CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Werror -Wno-unused-parameter -Wpointer-arith -Wshadow -std=c++11 -pipe -fPIC -ggdb -gdwarf-2 -Wno-deprecated"
)

#生成二进制文件路径
set(EXECUTABLE_OUTPUT_PATH ./)
#生成二进制文件名字
set(EXEC chat_serv)

#引入头文件
include_directories(SYSTEM ${INCLUDE_DIR})
#引入库文件目录
link_directories(${LINK_DIR})
#引入库文件
link_libraries(${LINK_LIB})

#源文件生成对应的可执行二进制文件
add_executable(${EXEC} ${SRC})

target_link_libraries(${EXEC} ${LINK_LIB})
