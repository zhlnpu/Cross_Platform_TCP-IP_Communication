#pragma once

#include "Modeling/ModelingData.h"
#include "Modeling/ServerConnection-Android.h"

#include <vector>
using namespace std;

class ModelingData
{
public:
	ServerConnection		m_ServerConnection;
	vector<Modeling*>		m_Models;

public:
	void Init(const char* server_name);
	void Parse(void* data);

	ModelingData();
	~ModelingData();
};

void* processing_listening(void* ptr);
