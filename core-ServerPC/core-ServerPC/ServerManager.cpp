#include "ServerManager.h"
#include "input.h"

ServerManager::ServerManager(void)
{
}

ServerManager::~ServerManager(void)
{
}

void ServerManager::RmvClient(SOCKET client)
{
	m_Socket2Client.erase(client);

}

void ServerManager::AddClient(SOCKET client, int ip)
{
/*
	for (map<SOCKET, ClientInfo>::iterator it = m_Socket2Client.begin(); it != m_Socket2Client.end(); it++)
	{
		if ((*it).first == ctParam->ClientSocket)				// source should not be updated
			continue;
*/


	ClientInfo cInfo;
	cInfo.IP = ip;
//	cInfo.Type = (CLIENT_TYPE)type;

	m_Socket2Client[client] = cInfo;
}
