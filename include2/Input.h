#pragma once

#include <wchar.h>

#define DEFAULT_BUFLEN	4096

// InputType ------------------------------------
typedef int InputType;
#define IT_EMPTY		0
#define IT_COMMAND		1
#define IT_GESTURE		2
#define IT_FINGERTIP	3

// CommandType ----------------------------------
// typedef int _CommandType;
// #define CT_EMPTY		0
// #define CT_TYPE			1
// #define CT_REMOVE		2

// GestureType ----------------------------------
typedef int GestureType;
#define GT_EMPTY		0
#define GT_BACK			101
#define GT_GO			102
#define GT_FLIP			103

// TipType -------------------------------------
typedef int TipType;
#define TIP_EMPTY		0
#define TIP_STOPED		1
#define TIP_STARTMOVE	2
#define TIP_STOPMOVE	3
#define TIP_MOVING		4






#include <string.h>


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




typedef struct tagInputBase
{
	InputType		inputType;

	int byte_size()
	{
		return sizeof(InputType);
	}

	void ToCharArray(char buf[], int index)
	{
		// copy inputType to buf
		int pos = index, len = sizeof(InputType);
		memcpy_s(&buf[pos], len, &inputType, len);
		pos += len;
	}

	tagInputBase() { inputType = IT_EMPTY; };
	tagInputBase(char data[])
	{
		memcpy_s(&inputType, sizeof(int), data, sizeof(int));
	}
} InputBase;

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
		int pos = index, 

		len = sizeof(_CommandType);
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

typedef struct tagGesture : public InputBase
{
	GestureType		gestureType;

	int byte_size()
	{
		return sizeof(InputType) + sizeof(GestureType);
	}

	void ToCharArray(char buf[], int index)
	{
		// copy inputType to buf
		int pos = index, len = sizeof(InputType);
		memcpy_s(&buf[pos], len, &inputType, len);
		pos += len;

		len = sizeof(GestureType);
		memcpy_s(&buf[pos], len, &gestureType, len);
		pos += len;
	}

	tagGesture() { inputType = IT_GESTURE; gestureType = GT_EMPTY; };
	tagGesture(char data[]) : InputBase(data)
	{
		memcpy_s(&gestureType, sizeof(int), &data[sizeof(int)], sizeof(int));
	}
} Gesture;

typedef struct tagFingerTip : public InputBase
{
	TipType			tipType;

	float			x;
	float			y;
	float			z;

	bool operator != (const tagFingerTip& ft)
	{
		if((tipType != ft.tipType) || (x != ft.x) || (y != ft.y) || (z != ft.z))
			return true;
		else
			return false; 
	};

	int byte_size()
	{
		return sizeof(InputType) + sizeof(TipType) + sizeof(float) * 3;
	}

	void ToCharArray(char buf[], int index)
	{
		// copy inputType to buf
		int pos = index, len = sizeof(InputType);
		memcpy_s(&buf[pos], len, &inputType, len);
		pos += len;

		len = sizeof(TipType);
		memcpy_s(&buf[pos], len, &tipType, len);
		pos += len;

		len = sizeof(float);
		memcpy_s(&buf[pos], len, &x, len);
		pos += len;

		len = sizeof(float);
		memcpy_s(&buf[pos], len, &y, len);
		pos += len;

		len = sizeof(float);
		memcpy_s(&buf[pos], len, &z, len);
		pos += len;
	}

	tagFingerTip() { inputType = IT_FINGERTIP; tipType = TIP_EMPTY; };
	tagFingerTip(char data[]) : InputBase(data)
	{
		memcpy_s(&tipType, sizeof(int), &data[sizeof(int)], sizeof(int));
		memcpy_s(&x, sizeof(float), &data[sizeof(int) * 2], sizeof(float));
		memcpy_s(&y, sizeof(float), &data[sizeof(int) * 2 + sizeof(float)], sizeof(float));
		memcpy_s(&z, sizeof(float), &data[sizeof(int) * 2 + sizeof(float) * 2], sizeof(float));
	}
} FingerTip;