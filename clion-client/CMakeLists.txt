cmake_minimum_required(VERSION 3.17)
project(tcpClient)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)


find_package (Threads)


#add_executable(tcpClient Socket-server.cpp ServerManager.cpp ServerManager.h Input.h main.cpp)

add_executable(tcpClient main.cpp)

target_link_libraries (tcpClient ${CMAKE_THREAD_LIBS_INIT})
