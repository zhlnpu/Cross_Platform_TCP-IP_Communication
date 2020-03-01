#pragma once

#include "Modeling/ModelingData.h"
#include "Modeling/ServerConnection-Android.h"

#include <vector>
using namespace std;

class ModelingData_androidclient
{
public:
	ServerConnection		m_ServerConnection;
//	vector<Modeling*>		m_Models;

public:
	void Init(const char* server_name);
	void Parse(void* data);

	ModelingData_androidclient();
	~ModelingData_androidclient();
};

void* processing_listening(void* ptr);
