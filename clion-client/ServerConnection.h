#pragma once


#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>
#include <map>
#include <string.h>
#include <iostream>

#include <sys/socket.h>


#include<arpa/inet.h>	//inet_addr
#include<unistd.h>	//write



#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "27015"
using namespace std;

class ServerConnection
{
private:
	int			m_iStartup;

	int		m_ServerSocket;

	pthread_t	m_Threads;
	bool		m_bThreadCreated;

public:
	bool ConnectServer(const char* server_name);
	bool IsConnected();

	int Senddata(char* sendbuf, int sendbuflen);
	int Recvdata(char* recvbuf, int recvbuflen);


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
	
	DT_ARDUINO = 1,
	DT_POWER = 2,
	DT_CHAOS = 3,

};


//kun
enum DATA_TYPE
{



	DT_POINT = 0,
	DT_POINT3 = 1,


};



