cmake_minimum_required(VERSION 3.7)
project(FTP)

set(CMAKE_CXX_STANDARD 11)

set(SOURCE_FILES main.cpp NetControl/Server.cpp NetControl/Server.h NetControl/Connection.cpp NetControl/Connection.h NetControl/DealConnect.cpp NetControl/DealConnect.h NetControl/ServerUtil.cpp NetControl/ServerUtil.h NetControl/ProcCommunicate.cpp NetControl/ProcCommunicate.h CmdControl/AnalyseCmd.cpp CmdControl/AnalyseCmd.h FileControl/FSControl.cpp FileControl/FSControl.h UserControl/User.cpp UserControl/User.h CmdControl/Datastructure.h FileControl/FSUtil.h)
add_executable(FTP ${SOURCE_FILES})