#pragma once

enum COMMAND_TYPE
{
	COMMAND_CONNECTION = 0,
	COMMAND_TEST = 1,
	COMMAND_DATA = 2,
};

enum CLIENT_TYPE
{
	CT_NULL = 0,
	CT_PC_1 = 11,
	CT_PC_2 = 12,
	CT_UNITY_1 = 21,
	CT_ANDROID_1 = 31,
};

enum DATA_TYPE
{
	DT_ARDUINO = 1,
	DT_POWER = 2,
	DT_CHAOS=3,

};




typedef struct tagCommand
{
	int		_CommandType;
	int _DataType;

	int byte_size()
	{
		return sizeof(_CommandType) + sizeof(_DataType);
	}

	void ToCharArray(char buf[], int index)
	{
		// copy inputType to buf
		int pos = index,len = sizeof(_CommandType);
		memcpy_s(&buf[pos], len, &_CommandType, len);
		pos += len;

		len = sizeof(int);
		memcpy_s(&buf[pos], len, &_DataType, len);
		pos += len;
	}

	tagCommand() { _CommandType = COMMAND_TYPE::COMMAND_CONNECTION; _DataType = 0; };
	tagCommand(char data[])
	{
		memcpy_s(&_CommandType, sizeof(int), &data[0], sizeof(int));
		memcpy_s(&_DataType, sizeof(int), &data[sizeof(int)], sizeof(int));
	};
} Command;

typedef struct tagTestConnection : Command
{
	int _value;
	int byte_size()
	{
		return sizeof(_CommandType) + sizeof(_DataType)+sizeof(_value);
	}
	void ToCharArray(char buf[], int index)
	{
		// copy inputType to buf
		int pos = index,

		len = sizeof(_CommandType);
		memcpy_s(&buf[pos], len, &_CommandType, len);
		pos += len;

		len = sizeof(int);
		memcpy_s(&buf[pos], len, &_DataType, len);
		pos += len;

		len = sizeof(int);
		memcpy_s(&buf[pos], len, &_value, len);
		pos += len;


	}
	tagTestConnection(char data[]) :	Command(data)
	{
	
		memcpy_s(&_value, sizeof(int), &data[sizeof(int)*2], sizeof(int));
	};
	tagTestConnection(int __c, int __d, int __v)
	{
		_CommandType = __c;
		_DataType = __d;
		_value = __v;
	};

}TestConnection;



