#include <windows.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <tlhelp32.h>

DWORD DisplayTheProcess();//��������
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

	DWORD dwId;//�������̵�ID��Ҳ��Ҫ�رս��̵Ĳ���ID
	if (bRet){
		CloseHandle(pi.hThread);
		CloseHandle(pi.hProcess);
		dwId = pi.dwProcessId;
		MessageBox(NULL, TEXT("���̴����ɹ�"), TEXT("��Ϣ"), MB_OKCANCEL);
	}

	DWORD dwResult = DisplayTheProcess();//���ú���
	printf("һ����%d������\n", dwResult);
	printf("=============================================");
	MessageBox(NULL, TEXT("����Ҫ�رս���notepad"), TEXT("����"), MB_ICONEXCLAMATION);
	if (TerminateProcessFormId(dwId)){
		printf("���±��Ѿ��ر�\n\n");
	}

	dwResult = DisplayTheProcess();
	printf("����һ����%d������\n\n", dwResult);
	return 0;
}



DWORD DisplayTheProcess(){
	PROCESSENTRY32 pe32;
	pe32.dwSize = sizeof(pe32);

	HANDLE hProcessSnap = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhel32Snapshot����ʧ��!\n");
		return -1;
	}
	BOOL bMore = Process32First(hProcessSnap, &pe32);
	DWORD cnt = 0;
	while (bMore){
		printf("��������:%s\n", pe32.szExeFile);
		printf("����ID:%d\n", pe32.th32ProcessID);
		bMore = Process32Next(hProcessSnap, &pe32);
		cnt++;
	}

	CloseHandle(hProcessSnap);
	return cnt;
}


BOOL TerminateProcessFormId(DWORD dwId){
	BOOL bRet = FALSE;
	//��Ŀ����̣�ȡ�ý��̾��
	//���пɽ��е�Ȩ��
	HANDLE hProcess = OpenProcess(PROCESS_ALL_ACCESS, FALSE, dwId);
	if (hProcess != NULL){
		bRet = TerminateProcess(hProcess, 0);//�رս���
	}
	CloseHandle(hProcess);
	return bRet;
}

