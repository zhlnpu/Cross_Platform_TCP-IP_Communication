#include "ServerConnection.h"

ServerConnection::ServerConnection() : m_bThreadCreated(false), m_ServerSocket(INVALID_SOCKET), m_iStartup(-1)
{
	m_iStartup = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
}

ServerConnection::~ServerConnection()
{
	if (m_iStartup == 0)
		WSACleanup();

	if(IsConnected())
		closesocket(m_ServerSocket);

	pthread_exit(NULL);
}

bool ServerConnection::ConnectServer(const char* server_name)
{
	if(m_iStartup != 0)
		return false;

	if(IsConnected())				// Aleardy conneced
		return true;

	// 1. Creating a Socket for the Client -----------------------------------------------------------------
	struct addrinfo *result = NULL, *ptr = NULL, hints;
	ZeroMemory( &hints, sizeof(hints) );
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	int iResult = getaddrinfo(server_name, DEFAULT_PORT, &hints, &result);				// 1.1 Resolve the server address and port
	if ( iResult != 0 )
		return false;

	// 2. Attempt to connect to an address until one succeeds -----------------------------------------------
	m_ServerSocket = INVALID_SOCKET;
	for(ptr = result; ptr != NULL ; ptr = ptr->ai_next) {
		m_ServerSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);		// 2.1 Create a SOCKET for connecting to server
		if (m_ServerSocket == INVALID_SOCKET) {
			continue;
		}

		iResult = connect( m_ServerSocket, ptr->ai_addr, (int)ptr->ai_addrlen);			// 2.2 Connect to server.
		if (iResult == SOCKET_ERROR) {
			m_ServerSocket = INVALID_SOCKET;
			continue;
		}
	}

	freeaddrinfo(result);

	if (m_ServerSocket == INVALID_SOCKET)
		return false;

	return true;
}

bool ServerConnection::IsConnected()
{
	if(m_iStartup != 0)
		return false;

	if(m_ServerSocket == INVALID_SOCKET)
		return false;

	return true;
}

int ServerConnection::Send(char* sendbuf, int sendbuflen)
{
	int iResult = send( m_ServerSocket, sendbuf, sendbuflen, 0 );
	return iResult;
}

int ServerConnection::Recv(char* recvbuf, int recvbuflen)
{
	int iResult = recv(m_ServerSocket, recvbuf, recvbuflen, 0);
	return iResult;
}

int ServerConnection::Listening(void *(__cdecl *start) (void *), void* arg)
{
	int rc = pthread_create(&m_Threads, NULL, start, arg);
	m_bThreadCreated = true;
	return rc;
}

int ServerConnection::Shutdown()
{
	int iResult = closesocket(m_ServerSocket);

	if(m_bThreadCreated)
		pthread_kill(m_Threads, 1);

	return iResult;
}
