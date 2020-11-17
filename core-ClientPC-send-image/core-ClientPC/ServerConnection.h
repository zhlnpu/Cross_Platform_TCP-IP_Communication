#pragma once

#include <wchar.h>

#include <string.h>
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iostream>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")



#define DEFAULT_BUFLEN 5000000
#define DEFAULT_PORT "27015"
using namespace std;

class ServerConnection
{
private:
	WSADATA		m_wsaData;
	int			m_iStartup;

	SOCKET		m_ServerSocket;

	pthread_t	m_Threads;
	bool		m_bThreadCreated;

public:
	bool ConnectServer(const char* server_name);
	bool IsConnected();

	int Send(char* sendbuf, int sendbuflen);
	int Recv(char* recvbuf, int recvbuflen);

	int Listening(void *(__cdecl *start) (void *), void* arg);

	int Shutdown();

	ServerConnection();
	~ServerConnection();
};


enum CLIENT_NAME
{
	COMMAND_CONNECTION = 0,


	CN_PC_1 = 101,
	CN_PC_2 = 102,
	CN_PC_3 = 103,
	CN_PC_4 = 104,
	CN_PC_5 = 105,
	
	
	CN_UNITY_1 = 201,
	CN_UNITY_2 = 202,
	CN_UNITY_3 = 203,
	CN_UNITY_4 = 204,
	CN_UNITY_5 = 205,


	CN_ANDROID_1 = 301,
	CN_ANDROID_2 = 302,
	CN_ANDROID_3 = 303,
	CN_ANDROID_4 = 304,
	CN_ANDROID_5 = 305,


	CN_HOLOLENS_1 = 401,
	CN_HOLOLENS_2 = 402,
	CN_HOLOLENS_3 = 403,
	CN_HOLOLENS_4 = 404,
	CN_HOLOLENS_5 = 405,


};

enum DATA_NAME
{

	DN_TEST = 0,
	
	DN_ARDUINO = 1,
	DN_POWER = 2,
	DN_CHAOS = 3,
	DN_IMAGE = 4,

};


//kun
enum DATA_TYPE
{



	DT_POINT = 0,
	DT_POINT3 = 1,


};



