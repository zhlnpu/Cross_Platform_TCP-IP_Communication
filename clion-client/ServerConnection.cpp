#include "ServerConnection.h"

//ServerConnection::ServerConnection() : m_bThreadCreated(false), m_ServerSocket(INVALID_SOCKET), m_iStartup(-1)
//{
//	m_iStartup = WSAStartup(MAKEWORD(2, 2), &m_wsaData);
//}

ServerConnection::ServerConnection()
{

}


ServerConnection::~ServerConnection()
{


	if(IsConnected())
		close(m_ServerSocket);

	pthread_exit(NULL);
}

bool ServerConnection::ConnectServer(const char* server_name)
{
	if(IsConnected())				// Aleardy conneced
		return true;

    struct sockaddr_in server;
    char *message , server_reply[2000];

    //Create socket
    m_ServerSocket = socket(AF_INET , SOCK_STREAM , 0);
    if (m_ServerSocket == -1)
    {
        printf("Could not create socket");
    }
    server.sin_addr.s_addr = inet_addr(server_name);
    server.sin_family = AF_INET;
    server.sin_port = htons( 27015 );
    //Connect to remote server
    if (connect(m_ServerSocket , (struct sockaddr *)&server , sizeof(server)) < 0)
    {
        puts("connect error");
        return false;
    }
    puts("Connected\n");

	return true;
}

bool ServerConnection::IsConnected()
{
	if(m_ServerSocket <=0)
		return false;
	return true;
}

int ServerConnection::Senddata(char* sendbuf, int sendbuflen)
{
	int iResult = send( m_ServerSocket, sendbuf, sendbuflen, 0 );
	return iResult;
}

int ServerConnection::Recvdata(char* recvbuf, int recvbuflen)
{
	int iResult = recv(m_ServerSocket, recvbuf, recvbuflen, 0);
	return iResult;
}


int ServerConnection::Shutdown()
{
	int iResult = close(m_ServerSocket);

	//if(m_bThreadCreated)
	//	pthread_kill(m_Threads, 1);

	return iResult;
}
