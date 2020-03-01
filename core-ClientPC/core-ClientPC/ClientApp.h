#pragma once


#include "ServerConnection.h"
#include <map>
#include <string>

class ThisClient
{
public:
	ServerConnection			m_Connection;
	//add extra codes here

private:
	//add extra codes here
	map<string, bool> dict;



	const char * m_serverAddr;
public:
	//add extra codes here
	void Test();

	ThisClient();
	~ThisClient();
};



void* ProcessInput(void *arg);


class FromWhom
{
public:
	CLIENT_NAME whom;

public:
	virtual int byte_size();
	virtual	void ToCharArray(char buf[]);
//	void ToCharArray(char buf[]);

//	yufu void  AddToCharArray(char buf[], int index);


	FromWhom()	{ whom = CLIENT_NAME::COMMAND_CONNECTION; }

	FromWhom(char data[]);
};








//_whom, dataname, datatype, data
class BaseDatatype : public FromWhom
{
public:
	DATA_NAME dataName;
	DATA_TYPE dataType;

public:
	virtual	int  byte_size();
	virtual	void ToCharArray(char buf[]);

	BaseDatatype::BaseDatatype(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType);

	BaseDatatype(char data[]);
};





//_whom, dataname, datatype, data
class C_Kun :public BaseDatatype
{
public:


	double my_point[3];

public:
	virtual int byte_size();
	virtual	void ToCharArray(char buf[]);
	C_Kun(char data[]);

	C_Kun(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType) :BaseDatatype(__whom, __dataName, __dataType){}


};