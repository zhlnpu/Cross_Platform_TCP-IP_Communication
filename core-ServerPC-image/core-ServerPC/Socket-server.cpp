

#include "ServerManager.h"
#include <iostream>
#include <string>


ServerManager		serverManager;

struct ClientThreadParam
{
	int			ipAddr;
	SOCKET		ClientSocket;
};
int getLength(char * code)
{
	int a = 0;

	/*while (true)
	{
		printf("%d ", *(code + a));
			//cout << *(code + a) << endl;
		a++;
	}*/


	while (*(code + a) != -52)
	{
		//	cout << *(code + a) << endl;
		a++;
	}
	return   a;
}
UINT ClientThread(LPVOID pParam)
{
	int iResult;
	ClientThreadParam* ctParam = (ClientThreadParam*)pParam;

	// 1. Receiving and Sending Data on the Server
	char recvbuf[100+3 * image_width* image_height];
	int recvbuflen = 100+3 * image_width* image_height;


	do {																						// 5.1 Receive until the peer shuts down the connection
		iResult = recv(ctParam->ClientSocket, recvbuf, recvbuflen, 0);
		if (iResult > 0) {	
		
			char ip_str[INET_ADDRSTRLEN];
			inet_ntop(AF_INET, &ctParam->ipAddr, ip_str, INET_ADDRSTRLEN);

			CLIENT_NAME _CommandType;
			memcpy_s(&_CommandType, sizeof(int), &recvbuf[0], sizeof(int));
			//Command command(recvbuf);
			//0. connection new client
			if (_CommandType == CLIENT_NAME::COMMAND_CONNECTION)
			{
				serverManager.AddClient(ctParam->ClientSocket, ctParam->ipAddr);
				printf("Client number is %d.\n", serverManager.m_Socket2Client.size());
				printf("Client %s is connected!\n\n", ip_str);
			}

			else
			{
			//	cout << "Received data from client: " + to_string(_CommandType) << endl;

				for (map<SOCKET, ClientInfo>::iterator it = serverManager.m_Socket2Client.begin(); it != serverManager.m_Socket2Client.end(); it++)
				{
					 					if ((*it).first == ctParam->ClientSocket)				// source should not be updated
											continue;
										send((*it).first, recvbuf, 100+ 3 * image_width* image_height, 0);
				}
			}
				

			/*


			//2. transfer data
			else
				if (_CommandType == COMMAND_TYPE::COMMAND_DATA )
				{

					//serverManager.ProcessInput(&command, ctParam->ClientSocket);
					printf("Received data from %s!\n\n", ip_str);
					int buflen = getLength(recvbuf);
					for (map<SOCKET, ClientInfo>::iterator it = serverManager.m_Socket2Client.begin(); it != serverManager.m_Socket2Client.end(); it++)
					{
						if ((*it).first == ctParam->ClientSocket)				// source should not be updated
							continue;
						send((*it).first, recvbuf, buflen, 0);
					}				
				}
				else
			if ( _CommandType == COMMAND_TYPE::COMMAND_TEST_FLOAT)
			{
				float test_float;
				memcpy_s(&test_float, sizeof(float), &recvbuf[sizeof(int)], sizeof(float));

				//serverManager.ProcessInput(&command, ctParam->ClientSocket);
				printf("Received data from %s!\n\n", ip_str);
				printf("TEST: %f\n\n", test_float);

		/ *		int buflen = getLength(recvbuf);
				
				send(ctParam->ClientSocket, recvbuf, buflen, 0);* /

			}
			else
				if (_CommandType == COMMAND_TYPE::COMMAND_TEST_DOUBLE)
				{
				float test_double;
				memcpy_s(&test_double, sizeof(double), &recvbuf[sizeof(int)], sizeof(double));

				//serverManager.ProcessInput(&command, ctParam->ClientSocket);
				printf("Received data from %s!\n\n", ip_str);
				printf("TEST: %f\n\n", test_double);

				int buflen = getLength(recvbuf);

				send(ctParam->ClientSocket, recvbuf, buflen, 0);


				}*/
		


		
			/*

			//1. test connection
			else if (command._CommandType == COMMAND_TYPE::COMMAND_TEST)
			{

			//		serverManager.ProcessInput(&command, ctParam->ClientSocket);

			TestConnection test(recvbuf);
			printf("Test data received from %s: %d, %d.\n\n", ip_str, test._DataType, test._value);

			test._DataType++;
			test._value++;
			char buf[DEFAULT_BUFLEN];
			int buflen = test.byte_size();
			test.ToCharArray(buf, 0);
			send(ctParam->ClientSocket, buf, buflen, 0);
			}*/
				/*else
				{
					printf("Unknown data from %s.\n\n", ip_str);
				}*/
		}
		else if (iResult == 0) {
			printf("Client was closing!\n");
		}
		else
		{
			printf("Client was closed!\n");

		}
		
	} while (iResult > 0);

	// 2. Disconnecting the Server
	serverManager.RmvClient(ctParam->ClientSocket);
	printf("Client number is %d.\n", serverManager.m_Socket2Client.size());

	iResult = shutdown(ctParam->ClientSocket, SD_SEND);										// 2.1 shutdown the connection since we're done
	if (iResult == SOCKET_ERROR) {
		printf("Failed to shutdown client with error: %d\n", WSAGetLastError());
		closesocket(ctParam->ClientSocket);
		delete ctParam;
		return 1;
	}
	else {
		closesocket(ctParam->ClientSocket);													// 2.2 cleanup
		delete ctParam;
		return 0;
	}
}

UINT ServerThread(LPVOID pParam)
{
	// 1. Accepting a Connection -----------------------------------------------------------------------------
	while (true)
	{
		sockaddr client_addr;
		int addr_len = sizeof(sockaddr);

		//wait, wait, wait..........until a client connected
		SOCKET ClientSocket = accept(serverManager.ServerSocket, &client_addr, &addr_len);	// 1.1 Accept a client socket

		//executed only when a client a connected
		if (ClientSocket == INVALID_SOCKET) {
			printf("accept failed with error: %d\n", WSAGetLastError());
		}
		else
		{
			struct sockaddr_in* pV4Addr = (struct sockaddr_in*)&client_addr;
			int ipAddr = pV4Addr->sin_addr.s_addr;

			ClientThreadParam*	ctParam = new ClientThreadParam;
			ctParam->ipAddr = ipAddr;
			ctParam->ClientSocket = ClientSocket;

			//	printf("A client connected.\n");

			AfxBeginThread(ClientThread, (LPVOID)ctParam);
		}
	}

	return 0;
}

bool InitServerSocket(SOCKET& ServerSocket)
{
	int iResult;

	// 1. Initialize Winsock ----------------------------------------------------------------------------------
	WSADATA wsaData;
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return false;
	}

	// 2. Creating a Socket for the Server --------------------------------------------------------------------
	struct addrinfo *result = NULL;
	struct addrinfo hints;

	//settings of the server socket
	ZeroMemory(&hints, sizeof(hints));													//fill in the memory of hints with 0
	hints.ai_family = AF_INET;				//=2, IPV4
	hints.ai_socktype = SOCK_STREAM;		//=1, stream, correspond to TCP
	hints.ai_protocol = IPPROTO_TCP;		//TCP protocol
	hints.ai_flags = AI_PASSIVE;			//socket addr is used for listening bind

	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);							// 2.1 Resolve the server address and port
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return false;
	}

	ServerSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);	// 2.2 Create a SOCKET for connecting to server
	if (ServerSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return false;
	}

	// 3. Binding a Socket -----------------------------------------------------------------------------------
	iResult = bind(ServerSocket, result->ai_addr, (int)result->ai_addrlen);			// 3.1 Setup the TCP listening socket
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ServerSocket);
		WSACleanup();
		return false;
	}

	freeaddrinfo(result);

	// 3. Listening on a Socket ------------------------------------------------------------------------------
	iResult = listen(ServerSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ServerSocket);
		WSACleanup();
		return false;
	}

	return true;
}

BOOL WINAPI ConsoleHandler(DWORD CEvent)
{
	switch (CEvent)
	{
	case CTRL_CLOSE_EVENT:
		closesocket(serverManager.ServerSocket);							// 4.2 No longer need server socket
		WSACleanup();
		break;
	default:
		break;
	}
	return true;
}



/*
//check IP authentication, zhangli, 16/11/16
bool CheckIP(char * _clientIP)
{
	FILE  * fin;
	fopen_s(&fin, "IP.txt", "r");
	if (fin == NULL)
	{
		printf("open IP file failed!\n");
		return false;
	}
	while (!feof(fin))
	{
		char  clientIP[16];
		fscanf(fin, "%s\n", clientIP);
		//printf(clientIP[count-1]);

		if (strcmp(clientIP, _clientIP) == 0)
		{
			return true;
		}
	}
	fclose(fin);
	printf("client IP is not authorized!!!\n");
	return false;
}*/






int __cdecl main(void)
{

	DeleteMenu(GetSystemMenu(GetConsoleWindow(), FALSE), SC_CLOSE, MF_BYCOMMAND);
	DrawMenuBar(GetConsoleWindow());

	serverManager.ServerSocket = INVALID_SOCKET;

	//set params, create server socket and bind, listen
	if (!InitServerSocket(serverManager.ServerSocket))
		return 1;

	printf("Server is Ready!\n");

	SetConsoleCtrlHandler(ConsoleHandler, true);

	//begin server thread
	AfxBeginThread(ServerThread, 0);

	while (true) {
		char input[6];
		scanf("%s", input);
		
		//清屏
		if (strcmp(input, "clear") == 0)
		{
			system("cls");
		}


		//无客户端连接后，推出程序
		if (strcmp(input, "exit") == 0)
		{
			if (serverManager.m_Socket2Client.size() == 0)
			{
				break;
			}
			else
			{
				printf("Client is running!\n\n");
			}
		}



		// type any key to test this code --------------------------------------
		//serverManager.test(input);
	}

	serverManager.m_Socket2Client.clear();

	closesocket(serverManager.ServerSocket);							// 4.2 No longer need server socket
	WSACleanup();

	return 0;
}


