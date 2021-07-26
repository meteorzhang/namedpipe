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
		TEXT("\\\\.\\Pipe\\pipeWrite"),							//管道名  
		PIPE_ACCESS_DUPLEX,										//管道类型，双向通信  
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //管道参数  
		PIPE_UNLIMITED_INSTANCES,								//管道能创建的最大实例数量  
		0,														//输出缓冲区长度 0表示默认  
		0,														//输入缓冲区长度 0表示默认  
		NMPWAIT_WAIT_FOREVER,									//超时时间,NMPWAIT_WAIT_FOREVER为不限时等待
		NULL);													//指定一个SECURITY_ATTRIBUTES结构,或者传递零值.

	pipeRead = CreateNamedPipe(
		TEXT("\\\\.\\Pipe\\pipeRead"),							//管道名  
		PIPE_ACCESS_DUPLEX,										//管道类型，双向通信  
		PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,  //管道参数  
		PIPE_UNLIMITED_INSTANCES,								//管道能创建的最大实例数量  
		0,														//输出缓冲区长度 0表示默认  
		0,														//输入缓冲区长度 0表示默认  
		NMPWAIT_WAIT_FOREVER,									//超时时间,NMPWAIT_WAIT_FOREVER为不限时等待
		NULL);


	if (INVALID_HANDLE_VALUE == pipeWrite)
		cout << "创建管道失败: " << GetLastError() << endl;
	else
	{
		cout << "这是命名管道测试程序中的write服务器端" << endl;
		cout << "现在等待客户端连接..." << endl;
		if (!ConnectNamedPipe(pipeWrite, NULL))						//阻塞等待客户端连接。  
		{
			cout << "连接失败!" << endl;
			return 1;
		}
		else
			cout << "连接成功!" << endl;


		//if (!ReadFile(pipeWrite, buf, 256, &rLen, NULL))			//接受客户端发送数据
		//{
		//	cout << "从客户端接收并读取数据!" << endl;
		//	return 2;
		//}
		//else
		//	cout << "客户端接收的数据为 ： " << buf << endl << "数据长度为 " << rLen << endl;


		//char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,3344444]]";
		//WriteFile(pipeWrite, strMessage, sizeof(strMessage), &wLen, 0); //向客户端发送数据
		//CloseHandle(pipeWrite);											//关闭管道句柄 
	}

												//指定一个SECURITY_ATTRIBUTES结构,或者传递零值.
	if (INVALID_HANDLE_VALUE == pipeRead)
		cout << "创建管道失败: " << GetLastError() << endl;
	else
	{
		cout << "这是命名管道测试程序中的read服务器端" << endl;
		cout << "现在等待客户端连接..." << endl;
		if (!ConnectNamedPipe(pipeRead, NULL))						//阻塞等待客户端连接。  
		{
			cout << "连接失败!" << endl;
			return 1;
		}
		else
			cout << "连接成功!" << endl;


		//if (!ReadFile(pipeRead, buf, 256, &rLen, NULL))			//接受客户端发送数据
		//{
		//	cout << "从客户端接收并读取数据!" << endl;
		//	return 2;
		//}
		//else
		//	cout << "客户端接收的数据为 ： " << buf << endl << "数据长度为 " << rLen << endl;


		//char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,335555]]";
		//WriteFile(pipeRead, strMessage, sizeof(strMessage), &wLen, 0); //向客户端发送数据
		//CloseHandle(pipeRead);											//关闭管道句柄 
	}
	while (true)
	{

		char strMessage[] = "[1,2,3,[0,11.11,22],[1,22,335555],[1,22,335555],[1,22,335555],[1,22,335555]]";
		WriteFile(pipeWrite, strMessage, sizeof(strMessage), &wLen, 0); //向客户端发送数据	




		if (!ReadFile(pipeRead, buf, 256, &rLen, NULL))			//接受客户端发送数据
		{
			cout << "从客户端接收并读取数据!" << endl;
			return 2;
		}
		else
			cout << "客户端接收的数据为 ： " << buf << endl << "数据长度为 " << rLen << endl;



		Sleep(1000);
	}


	system("pause");
	return 0;
}
