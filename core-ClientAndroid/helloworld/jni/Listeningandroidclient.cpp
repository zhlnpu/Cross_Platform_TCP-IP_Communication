#include "Listeningandroidclient.h"

ModelingData_androidclient::ModelingData_androidclient()
{
/*
	for (size_t i = 0; i < m_Models.size(); i++) {
		delete m_Models[i];
	}*/
}

ModelingData_androidclient::~ModelingData_androidclient()
{

}

bool ModelingData_androidclient::Init()
{
	if (!m_ServerConnection.ConnectServer("192.168.155.1"))
		return false;


	if (m_ServerConnection.IsConnected())
	{
//		int command = 1;
//		m_ServerConnection.Send((char *)command, sizeof(command));

		m_ServerConnection.Listening(processing_listening, this);
	}
	return true;

}

void ModelingData_androidclient::Parse(void* data)
{
/*
	DataType type;
	Modeling* pModeling = CharArrayToData((char*)data, type);

	if (type == DT_POINT) {
		MPoint* pPoint = (MPoint*)pModeling;
		m_Models.push_back(pPoint);
	}

	if (type == DT_POLYLINE) {
		MPolyline* pPoly = (MPolyline*)pModeling;
		m_Models.push_back(pPoly);
	}

	if (type == DT_PATH) {
		MPath* pPath = (MPath*)pModeling;
		m_Models.push_back(pPath);
	}

	if (type == DT_MODELRAW) {
		//Model3D* pModel = (Model3D*)pModeling;
		ModelRaw * pModel = (ModelRaw*)pModeling;
		m_Models.push_back(pModel);
	}*/
}

void* processing_listening(void* ptr)
{
	int iResult;
	ModelingData_androidclient* pModelingData = (ModelingData_androidclient*)ptr;

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	do {
	
		iResult = pModelingData->m_ServerConnection.Recv(recvbuf, recvbuflen);
		if (iResult > 0) {
			
			pModelingData->Parse((void*)recvbuf);




		}
	} while (iResult > 0);

	return 0;
}
