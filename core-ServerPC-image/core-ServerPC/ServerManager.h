
#pragma once


#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <wchar.h>
#include <string.h>
#include <map>
#include <Afxwin.h>

#include <ws2tcpip.h>
#include <winsock2.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>


const  int image_width = 640;
const  int image_height = 480;


#define DEFAULT_BUFLEN 5000000
#define DEFAULT_PORT	"27015"

#pragma comment (lib, "Ws2_32.lib")

using namespace std;

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



typedef struct tagClientInfo
{
//	CLIENT_TYPE		Type;
	int				IP;
} ClientInfo;

// manage clients and distribute messages and objects
class ServerManager
{
public:
	SOCKET						ServerSocket;
	map<SOCKET, ClientInfo>		m_Socket2Client;		

private:
	//   ModelingManager				m_Manager;
		
public:
	void RmvClient(SOCKET client);
	void AddClient(SOCKET client, int id);

// 	// Process inputs -------------------------------------------------------
// 	void ProcessInput(InputBase* pInput, const SOCKET& from);
// 
// 	// Process outputs ------------------------------------------------------
// 	void ProcessModeling(Modeling* pModeling, const SOCKET& from);

	//void test(char input[]);

	ServerManager(void);
	~ServerManager(void);
};

