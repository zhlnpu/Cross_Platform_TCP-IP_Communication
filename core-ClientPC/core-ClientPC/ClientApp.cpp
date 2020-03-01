#pragma once
#include "ClientApp.h"

int FromWhom::byte_size()
{
	return sizeof(whom);
}

void FromWhom::ToCharArray(char buf[])
{

	// copy inputType to buf
	int pos = 0, len = sizeof(whom);
	memcpy_s(&buf[pos], len, &whom, len);

}

FromWhom::FromWhom(char data[])
{
	memcpy_s(&whom, sizeof(int), &data[0], sizeof(int));
}



// void FromWhom::ToCharArray(char buf[])
// {
// 	// copy inputType to buf
// 	int pos = 0, len = sizeof(_whom);
// 	memcpy_s(&buf[pos], len, &_whom, len);
// }



int BaseDatatype::byte_size()
{
	return FromWhom::byte_size() + sizeof(dataName) + sizeof(dataType);;
}

void BaseDatatype:: ToCharArray(char buf[])
{
	int pos = 0;
	int	len = FromWhom::byte_size();
	FromWhom::ToCharArray(buf);
	pos += len;

	len = sizeof(dataName);
	memcpy_s(&buf[pos], len, &dataName, len);
	pos += len;

	len = sizeof(dataType);
	memcpy_s(&buf[pos], len, &dataType, len);
	pos += len;
}

BaseDatatype::BaseDatatype(CLIENT_NAME __whom, DATA_NAME __dataName, DATA_TYPE __dataType)
{
	whom = __whom;
	dataName = __dataName;
	dataType = __dataType;
}







BaseDatatype::BaseDatatype(char data[])
{
	int pos = 0;
	int	len = sizeof(int);
	memcpy_s(&whom, len, &data[pos], len);
	pos += len;

	len = sizeof(int);
	memcpy_s(&dataName, len, &data[pos], len);
	pos += len;

	len = sizeof(int);
	memcpy_s(&dataType, len, &data[pos], len);
	pos += len;
}




 int C_Kun::byte_size()
{
	int length=BaseDatatype::byte_size() + sizeof(double) * 3;

	return length;
}

 void C_Kun::ToCharArray(char buf[])
 {
	 // copy inputType to buf
	 BaseDatatype::ToCharArray(buf);

	 int pos = BaseDatatype::byte_size();


	 int	 	 len = sizeof(double) * 3;
	 memcpy_s(&buf[pos], len, my_point, len);
	 pos += len;
 }


 C_Kun::C_Kun(char data[]) : BaseDatatype(data)
 {

	 int pos = BaseDatatype::byte_size();
	 int	 	 len = sizeof(double) * 3;

	 memcpy_s(my_point, len, &data[pos], len);
	
 }





 void  ThisClient::Test()
 {



	 //test communication

	 C_Kun cKun(CLIENT_NAME::CN_PC_1, DATA_NAME::DN_TEST, DATA_TYPE::DT_POINT3);

	 cKun.my_point[0] = 1.1;
	 cKun.my_point[1] = 1.2;
	 cKun.my_point[2] = 1.3;


	// cKun._whom = CLIENT_NAME::CT_PC_2;
	 char sendbuf[DEFAULT_BUFLEN];

	 cKun.ToCharArray(sendbuf);
	 m_Connection.Send(sendbuf, cKun.byte_size());



 }






ThisClient::ThisClient() :m_serverAddr("localhost")
{
	m_Connection.ConnectServer(m_serverAddr);
	if (m_Connection.IsConnected())
	{
		FromWhom command;
		command.whom = CLIENT_NAME::COMMAND_CONNECTION;
		//	command._DataType = CLIENT_TYPE::CT_PC_1;

		char buf[DEFAULT_BUFLEN];
		command.ToCharArray(buf);

		int iResult = m_Connection.Send(buf, command.byte_size());
		if (iResult == SOCKET_ERROR)
		{
			printf("Failed to build connection.\n");
		}
		else
		{
			m_Connection.Listening(ProcessInput, this);
			printf("Connected to Server.\n");
		}
	}
	else
	{
		printf("Failed to connect server.\n");

		exit(0);

	}




}

ThisClient::~ThisClient()
{
	m_Connection.Shutdown();
}



void*  ProcessInput(void *arg)
{
	ThisClient * client = (ThisClient*)arg;
	int iResult;
	/*CModelingDoc* pDoc = (CModelingDoc*)arg;*/

	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	do {
		iResult = client->m_Connection.Recv(recvbuf, recvbuflen);
		if (iResult > 0) {
			FromWhom fromWhom(recvbuf);





			//kun
			if (fromWhom.whom == CLIENT_NAME::CN_PC_1)
			{
				//add data processing codes here
				/*
				client->m_Connection.Send(databuf, dataLen);
				*/
				int data_name;
				memcpy_s(&data_name, sizeof(int), &recvbuf[sizeof(int)], sizeof(int));

				//kun
				if (data_name == DATA_NAME::DN_TEST)
				{
					C_Kun kun_point(recvbuf);

					cout << kun_point.my_point[0] << kun_point.my_point[1] << kun_point.my_point[2] << endl;


					kun_point.my_point[0]++;

					

					char sendbuf[DEFAULT_BUFLEN];

					kun_point.ToCharArray(sendbuf);
					client->m_Connection.Send(sendbuf, kun_point.byte_size());
				}


			}
			/*

			else if (fromWhom._whom == CLIENT_TYPE::COMMAND_TEST)
			{


			client->m_Connection.Send(fromWhom.ToCharArray(), fromWhom.byte_size());

			printf("Test data received from server: %d.\nConnection test success!\n\n",
			fromWhom._whom);

			//	m_Connection.Send(buf, cmd.byte_size());
			}*/
			else
			{
				printf("Unknown data.\n\n");
			}
		}

	} while (iResult > 0);

	return 0;
}




/*
void ThisClient::Test()
{
if (!m_Connection.IsConnected())
printf("Client is not connected\n\n");

FromWhom command;
command._whom = CLIENT_TYPE::COMMAND_TEST;
//	command._DataType = CLIENT_TYPE::CT_PC_1;

char buf[DEFAULT_BUFLEN];
command.ToCharArray(buf, 0);
int lenth = command.byte_size();
int iResult = m_Connection.Send(buf,lenth);



if (iResult == SOCKET_ERROR) {
printf("Failed to send.\n");
}
else
{
printf("Test data sent to server.\n");
}

}*/
