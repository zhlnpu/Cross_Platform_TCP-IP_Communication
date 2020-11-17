#pragma once


#include "ServerConnection.h"
#include <map>
#include <string>

#include <opencv.hpp>
using namespace cv;


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



const  int image_width = 640;
const  int image_height = 480;



//_whom, dataname, datatype, data
class C_Image :public BaseDatatype
{
public:


	//	double my_point[3];
	//	int my_image[image_width*image_height*3];

public:
	virtual int byte_size();
	virtual	void ToCharArray(char buf[], Mat image);
	C_Image(char data[]);

	C_Image(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType) :BaseDatatype(__whom, __dataName, __dataType){}


};