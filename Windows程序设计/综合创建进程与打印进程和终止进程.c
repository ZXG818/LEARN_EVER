#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <tlhelp32.h>

DWORD DisplayTheProcess();//函数声明
BOOL TerminateProcessFormId(DWORD dwId);

int main(int argc, char *argv[]){
	char *szCommandLine = "notepad";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;

	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;

	BOOL bRet = CreateProcess(
		NULL,
		szCommandLine,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	DWORD dwId;//创建进程的ID，也是要关闭进程的参数ID
	if (bRet){
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		dwId = pi.dwProcessId;
		MessageBox(NULL, TEXT("进程创建成功"), TEXT("消息"), MB_OKCANCEL);
	}

	DWORD dwResult = DisplayTheProcess();//调用函数
	printf("一共有%d个进程\n", dwResult);
	printf("=============================================");
	MessageBox(NULL, TEXT("现在要关闭进程notepad"), TEXT("警告"), MB_ICONEXCLAMATION);
	if (TerminateProcessFormId(dwId)){
		printf("记事本已经关闭\n\n");
	}

	dwResult = DisplayTheProcess();
	printf("现在一共有%d个进程\n\n", dwResult);
	return 0;
}



DWORD DisplayTheProcess(){
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhel32Snapshot调用失败!\n");
		return -1;
	}
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	DWORD cnt = 0;
	while (bMore){
		printf("进程名称:%s\n", pe32.szExeFile);
		printf("进程ID:%d\n", pe32.th32ProcessID);
		bMore = Process32Next(hProcessSnap, &pe32);
		cnt++;
	}

	CloseHandle(hProcessSnap);
	return cnt;
}


BOOL TerminateProcessFormId(DWORD dwId){
	BOOL bRet = FALSE;
	//打开目标进程，取得进程句柄
	//所有可进行的权限
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwId);
	if (hProcess != NULL){
		bRet = TerminateProcess(hProcess, 0);//关闭进程
	}
	CloseHandle(hProcess);
	return bRet;
}

