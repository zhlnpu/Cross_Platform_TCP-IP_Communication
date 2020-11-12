cmake_minimum_required(VERSION 3.17)
project(tcpServer)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_CXX_STANDARD 14)

add_executable(tcpServer Socket-server.cpp ServerManager.cpp ServerManager.h Input.h main.cpp)