
//TODO
/* revised zhangli, 16/11/2016, about functions the srver need to occupy

functions:
	1.one more clients connect to server, include ID, nickname,(function list)
	2.communication settings, include A&Q, broadcast, inform, ppdl
	3.deliver complex data type with multiple types
	4.link to database
	5.one client can search the working status of another client, gathering its data acquired
	
*/

// All client info is stored in .XMl file, the server read it and only client with IP in the file can connect
/*
10.129.10.30
10.12910.142
*/

#pragma once

#include <map>
using namespace std;

#include <winsock2.h>

#include "ModelingManager.h"
#include <string>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>




typedef struct tagClientInfo
{
	CLIENT_TYPE		Type;
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
	void AddClient(SOCKET client, int id, int type);

	// Process inputs -------------------------------------------------------
	void ProcessInput(InputBase* pInput, const SOCKET& from);

	// Process outputs ------------------------------------------------------
	void ProcessModeling(Modeling* pModeling, const SOCKET& from);

	//void test(char input[]);

	ServerManager(void);
	~ServerManager(void);
};

