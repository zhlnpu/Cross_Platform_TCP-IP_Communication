#pragma once

#include <string.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

#include <pthread.h>

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
