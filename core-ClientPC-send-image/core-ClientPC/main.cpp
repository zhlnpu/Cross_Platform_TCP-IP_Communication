#include "ClientApp.h"

/*
Usage:
 main.cpp：定义主控制流程
 ClientApp：定义接受数据方式和数据解析方式，解析数据存放于公有成员函数
 ServerConnection：定义服务器连接


*/

void main()
{
	ThisClient thisClient;



	while (true) {
		char input[6];
		scanf("%s", input);
		if (strcmp(input, "exit") == 0)
			break;

		if (strcmp(input, "test") == 0)
		{
			//本测试函数，是测试信息到服务器的收发，发送信息后自动接收信息并显示
			//激活此函数的方法：
			thisClient.Test();
		}

	}
	exit(0);
}