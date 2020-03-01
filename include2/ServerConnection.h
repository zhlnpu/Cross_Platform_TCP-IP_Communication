#pragma once

#include <stdlib.h>
#include <stdio.h>
#include <pthread.h>

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>

// Need to link with Ws2_32.lib, Mswsock.lib, and Advapi32.lib
#pragma comment (lib, "Ws2_32.lib")
#pragma comment (lib, "Mswsock.lib")
#pragma comment (lib, "AdvApi32.lib")

#define DEFAULT_BUFLEN 4096
#define DEFAULT_PORT "27015"

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