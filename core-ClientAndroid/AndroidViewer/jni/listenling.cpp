#include "listenling.h"

ModelingData::ModelingData()
{
	for (size_t i = 0; i < m_Models.size(); i++) {
		delete m_Models[i];
	}
}

ModelingData::~ModelingData()
{

}

void ModelingData::Init(const char* server_name)
{
	m_ServerConnection.ConnectServer("localhost");
	if (m_ServerConnection.IsConnected())
		m_ServerConnection.Listening(processing_listening, this);
}

CharArrayToData((char*)data, type);


void ModelingData::Parse(void* data)
{
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
	}
}

void* processing_listening(void* ptr)
{
	int iResult;
	ModelingData* pModelingData = (ModelingData*)ptr;

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
