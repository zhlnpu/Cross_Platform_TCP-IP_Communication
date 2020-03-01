#pragma once

//#include "ModelingData.h"
#include "ConnectionBaseAndroid.h"

#include <vector>
using namespace std;

class ModelingData_androidclient
{
public:
	ServerConnection		m_ServerConnection;
//	vector<Modeling*>		m_Models;

public:
	bool Init();
	void Parse(void* data);

	ModelingData_androidclient();
	~ModelingData_androidclient();
};

void* processing_listening(void* ptr);
