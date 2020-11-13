cmake_minimum_required(VERSION 3.17)
project(tcpServer)
SET(CMAKE_BUILD_TYPE Debug)


set(CMAKE_CXX_STANDARD 14)


find_package (Threads)


#add_executable(tcpServer Socket-server.cpp ServerManager.cpp ServerManager.h Input.h main.cpp)

add_executable(tcpServer main.cpp)

target_link_libraries (tcpServer ${CMAKE_THREAD_LIBS_INIT})
