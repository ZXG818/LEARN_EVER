#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
DWORD DisplayProcessList();
int main(int argc, char* argv[]){
	char *szCommandLine = "notepad";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION  pi;
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
	DWORD dwRecord = 0;
	if (bRet){
		dwRecord = pi.dwProcessId;//记事本的进程ID
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		
		printf("新进程为的ID为：%d\n", pi.dwProcessId);
		printf("新进程的主线程的进程ID为：%d\n", pi.dwThreadId);
	}

	MessageBox(NULL, TEXT("新的进程“记事本”已经创建"), TEXT("提示"), MB_OKCANCEL);

	DWORD dwSumProcess = DisplayProcessList();
	printf("一共有%d个进程\n", dwSumProcess);

	int nSelect = MessageBox(NULL, TEXT("是否终止记事本进程?"), TEXT("警告"), MB_OKCANCEL|MB_ICONEXCLAMATION);
	if (nSelect == IDOK){
		BOOL bRet = FALSE;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRecord);
		if (hProcess != NULL){
			bRet = TerminateProcess(hProcess, 0);
		}
		CloseHandle(hProcess);
		MessageBox(NULL, TEXT("记事本进程已经关闭"), TEXT("提示"), MB_OKCANCEL);
	}
	else{
		MessageBox(NULL, TEXT("记事本还在运行"), TEXT("提示"), MB_OKCANCEL);
	}

	dwSumProcess = DisplayProcessList();
	printf("现在一共有%d个进程\n", dwSumProcess);
	return 0;
}

DWORD DisplayProcessList(){
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhelp32Snapshot调用失败!\n");
		return -1;
	}
	DWORD dwSumProcess = 0;
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	while (bMore){
		printf("进程名称:%s\n", pe32.szExeFile);
		printf("进程ID号:%d\n\n", pe32.th32ProcessID);
		bMore = Process32Next(hProcessSnap, &pe32);
		dwSumProcess++;
	}
	CloseHandle(hProcessSnap);
	return dwSumProcess;
}
