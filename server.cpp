#include <windows.h> 
#include <stdio.h> 
#include <tchar.h>
#include <strsafe.h>
#include <iostream>
using namespace std;
#include<chrono>
int main()
{
	char buf[256] = "";
	DWORD rLen = 0;
	DWORD wLen = 0;
	HANDLE pipeWrite = NULL;  
    HANDLE pipeRead = NULL;
	pipeWrite = CreateNamedPipe(
		TEXT("\\\\.\\Pipe\\pipeWrite"),							//�ܵ���  
		PIPE_ACCESS_DUPLEX,										//�ܵ����ͣ�˫��ͨ��  
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //�ܵ�����  
		PIPE_UNLIMITED_INSTANCES,								//�ܵ��ܴ��������ʵ������  
		0,														//������������� 0��ʾĬ��  
		0,														//���뻺�������� 0��ʾĬ��  
		NMPWAIT_WAIT_FOREVER,									//��ʱʱ��,NMPWAIT_WAIT_FOREVERΪ����ʱ�ȴ�
		NULL);													//ָ��һ��SECURITY_ATTRIBUTES�ṹ,���ߴ�����ֵ.

	pipeRead = CreateNamedPipe(
		TEXT("\\\\.\\Pipe\\pipeRead"),							//�ܵ���  
		PIPE_ACCESS_DUPLEX,										//�ܵ����ͣ�˫��ͨ��  
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //�ܵ�����  
		PIPE_UNLIMITED_INSTANCES,								//�ܵ��ܴ��������ʵ������  
		0,														//������������� 0��ʾĬ��  
		0,														//���뻺�������� 0��ʾĬ��  
		NMPWAIT_WAIT_FOREVER,									//��ʱʱ��,NMPWAIT_WAIT_FOREVERΪ����ʱ�ȴ�
		NULL);


	if (INVALID_HANDLE_VALUE == pipeWrite)
		cout << "�����ܵ�ʧ��: " << GetLastError() << endl;
	else
	{
		cout << "���������ܵ����Գ����е�write��������" << endl;
		cout << "���ڵȴ��ͻ�������..." << endl;
		if (!ConnectNamedPipe(pipeWrite, NULL))						//�����ȴ��ͻ������ӡ�  
		{
			cout << "����ʧ��!" << endl;
			return 1;
		}
		else
			cout << "���ӳɹ�!" << endl;


		//if (!ReadFile(pipeWrite, buf, 256, &rLen, NULL))			//���ܿͻ��˷�������
		//{
		//	cout << "�ӿͻ��˽��ղ���ȡ����!" << endl;
		//	return 2;
		//}
		//else
		//	cout << "�ͻ��˽��յ�����Ϊ �� " << buf << endl << "���ݳ���Ϊ " << rLen << endl;


		//char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,3344444]]";
		//WriteFile(pipeWrite, strMessage, sizeof(strMessage), &wLen, 0); //��ͻ��˷�������
		//CloseHandle(pipeWrite);											//�رչܵ���� 
	}

												//ָ��һ��SECURITY_ATTRIBUTES�ṹ,���ߴ�����ֵ.
	if (INVALID_HANDLE_VALUE == pipeRead)
		cout << "�����ܵ�ʧ��: " << GetLastError() << endl;
	else
	{
		cout << "���������ܵ����Գ����е�read��������" << endl;
		cout << "���ڵȴ��ͻ�������..." << endl;
		if (!ConnectNamedPipe(pipeRead, NULL))						//�����ȴ��ͻ������ӡ�  
		{
			cout << "����ʧ��!" << endl;
			return 1;
		}
		else
			cout << "���ӳɹ�!" << endl;


		//if (!ReadFile(pipeRead, buf, 256, &rLen, NULL))			//���ܿͻ��˷�������
		//{
		//	cout << "�ӿͻ��˽��ղ���ȡ����!" << endl;
		//	return 2;
		//}
		//else
		//	cout << "�ͻ��˽��յ�����Ϊ �� " << buf << endl << "���ݳ���Ϊ " << rLen << endl;


		//char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,335555]]";
		//WriteFile(pipeRead, strMessage, sizeof(strMessage), &wLen, 0); //��ͻ��˷�������
		//CloseHandle(pipeRead);											//�رչܵ���� 
	}
	while (true)
	{

		char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,335555],[1,22,335555],[1,22,335555],[1,22,335555]]";
		WriteFile(pipeWrite, strMessage, sizeof(strMessage), &wLen, 0); //��ͻ��˷�������	




		if (!ReadFile(pipeRead, buf, 256, &rLen, NULL))			//���ܿͻ��˷�������
		{
			cout << "�ӿͻ��˽��ղ���ȡ����!" << endl;
			return 2;
		}
		else
			cout << "�ͻ��˽��յ�����Ϊ �� " << buf << endl << "���ݳ���Ϊ " << rLen << endl;



		Sleep(1000);
	}


	system("pause");
	return 0;
}
