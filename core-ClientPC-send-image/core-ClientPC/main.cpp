#include "ClientApp.h"

/*
Usage:
 main.cpp����������������
 ClientApp������������ݷ�ʽ�����ݽ�����ʽ���������ݴ���ڹ��г�Ա����
 ServerConnection���������������


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
			//�����Ժ������ǲ�����Ϣ�����������շ���������Ϣ���Զ�������Ϣ����ʾ
			//����˺����ķ�����
			thisClient.Test();
		}

	}
	exit(0);
}