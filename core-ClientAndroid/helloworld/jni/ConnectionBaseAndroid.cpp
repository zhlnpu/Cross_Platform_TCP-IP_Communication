

#include "ConnectionBaseAndroid.h"


ServerConnection::ServerConnection() : m_bThreadCreated(false), m_ServerSocket(0), m_nConnected(false)
{
};

ServerConnection::~ServerConnection()
{
	if (IsConnected())
		close(m_ServerSocket);

	pthread_exit(NULL);
};

bool ServerConnection::ConnectServer(const char* server_name)
{
	m_ServerSocket = socket(PF_INET, SOCK_STREAM, 0);

	if (m_ServerSocket < 0)
		return false;

	struct sockaddr_in peerAddr;

	peerAddr.sin_family = AF_INET;
	peerAddr.sin_port = htons(DEFAULT_PORT);

	peerAddr.sin_addr.s_addr = inet_addr(server_name);

	m_nConnected = connect(m_ServerSocket, (struct sockaddr *)&peerAddr, sizeof(peerAddr));

	if (m_nConnected != 0){
		close(m_ServerSocket);
		return false;
	}

	return true;
}

bool ServerConnection::IsConnected()
{
	return (m_nConnected == 0);
}

int ServerConnection::Send(char* sendbuf, int sendbuflen)
{
	int iResult = send(m_ServerSocket, sendbuf, sendbuflen, 0);
	return iResult;

}

int ServerConnection::Recv(char* recvbuf, int recvbuflen)
{
	int iResult = recv(m_ServerSocket, recvbuf, recvbuflen, 0);
	return iResult;
}

int ServerConnection::Shutdown()
{
	int iResult = close(m_ServerSocket);

	if (m_bThreadCreated)
		pthread_kill(m_Threads, 1);

	return iResult;
}

int ServerConnection::Listening(void *(*start) (void *), void * arg)
{
	int rc = pthread_create(&m_Threads, NULL, start, arg);
	m_bThreadCreated = true;
	return rc;
}
