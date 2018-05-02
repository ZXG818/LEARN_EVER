#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <stdbool.h>


//主线程的进入点是main函数
//辅助线程的进入点是DWORD WINAPI ThreadProc(LPVOID lpParam);函数

DWORD WINAPI ThreadProc(LPVOID lpParam){//回调函数
	int i = 0;
	while (i < 20){
		printf("I am from a thread,count = %d\n", i++);
	}
	return 0;
}

int main(int argc, char* argv[]){
	HANDLE hThread;
	DWORD dwThreadId;

	//创建一个线程
	hThread = CreateThread(
		NULL,//默认安全属性
		NULL,//默认堆栈大小
		ThreadProc,//线程入口地址（执行线程的回调函数）
		NULL,//传给函数的参数
		0,//指定线程立刻执行
		&dwThreadId);//返回线程的ID号


	

	printf("Now another thread has been created.ID=%d\n", dwThreadId);//打印辅助线程的ID号
	

	//等待新线程运行结束
	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);
	return 0;
}

