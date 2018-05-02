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
		dwRecord = pi.dwProcessId;//���±��Ľ���ID
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		
		printf("�½���Ϊ��IDΪ��%d\n", pi.dwProcessId);
		printf("�½��̵����̵߳Ľ���IDΪ��%d\n", pi.dwThreadId);
	}

	MessageBox(NULL, TEXT("�µĽ��̡����±����Ѿ�����"), TEXT("��ʾ"), MB_OKCANCEL);

	DWORD dwSumProcess = DisplayProcessList();
	printf("һ����%d������\n", dwSumProcess);

	int nSelect = MessageBox(NULL, TEXT("�Ƿ���ֹ���±�����?"), TEXT("����"), MB_OKCANCEL|MB_ICONEXCLAMATION);
	if (nSelect == IDOK){
		BOOL bRet = FALSE;
		HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwRecord);
		if (hProcess != NULL){
			bRet = TerminateProcess(hProcess, 0);
		}
		CloseHandle(hProcess);
		MessageBox(NULL, TEXT("���±������Ѿ��ر�"), TEXT("��ʾ"), MB_OKCANCEL);
	}
	else{
		MessageBox(NULL, TEXT("���±���������"), TEXT("��ʾ"), MB_OKCANCEL);
	}

	dwSumProcess = DisplayProcessList();
	printf("����һ����%d������\n", dwSumProcess);
	return 0;
}

DWORD DisplayProcessList(){
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhelp32Snapshot����ʧ��!\n");
		return -1;
	}
	DWORD dwSumProcess = 0;
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	while (bMore){
		printf("��������:%s\n", pe32.szExeFile);
		printf("����ID��:%d\n\n", pe32.th32ProcessID);
		bMore = Process32Next(hProcessSnap, &pe32);
		dwSumProcess++;
	}
	CloseHandle(hProcessSnap);
	return dwSumProcess;
}
