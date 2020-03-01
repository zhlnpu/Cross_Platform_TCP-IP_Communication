#pragma once

#include <string.h>

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h> 
#include <pthread.h>

//#include <../../../arch-arm/usr/include/sys/socket.h>
#include <sys/socket.h>

#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT 27015

class ServerConnection
{
private:
	int				m_ServerSocket;
	int				m_nConnected;

	pthread_t		m_Threads;
	bool			m_bThreadCreated;

public:
	bool ConnectServer(const char* server_name);
	bool IsConnected();

	int Send(char* sendbuf, int sendbuflen);
	int Recv(char* recvbuf, int recvbuflen);

	int Listening(void *(*start) (void *), void * arg);

	int Shutdown();

	ServerConnection();
	~ServerConnection();
};
