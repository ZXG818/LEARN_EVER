#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>

BOOL FindFirst(DWORD dwValue);
BOOL FindNext(DWORD dwValue);
DWORD g_arList[1024];// ��ַ�б�
int g_nListCnt;// ��Ч��ַ�ĸ���
HANDLE g_hProcess;// Ŀ����̾��

BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue){
	// ��ȡһҳ�ڴ�
	BYTE arBytes[4096];
	if (!ReadProcessMemory(g_hProcess, (LPVOID)dwBaseAddr, arBytes, 4096, NULL)){
		return FALSE;
	}

	DWORD *pdw;
	for (int i = 0; i < (int)4 * 1024 - 3; i++){
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue){
			if (g_nListCnt >= 1024){
				return FALSE;
			}
			g_arList[g_nListCnt++] = dwBaseAddr + i;
		}
	}
	return TRUE;
}

BOOL FindFirst(DWORD dwValue){
	const DWORD dwOneGB = 1024 * 1024 * 1024;
	const DWORD dwOnePage = 4 * 1024;
	if (g_hProcess == NULL){
		return FALSE;
	}

	DWORD dwBase;
	OSVERSIONINFO vi = { sizeof(vi) };
	GetVersionEx(&vi);
	// Windows�汾�ж�
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS){
		dwBase = 4 * 1024 * 1024;// Windows 98ϵ�У�4MB
	}
	else{
		dwBase = 64 * 1024;// Windows NTϵ�� ��64KB
	}

	//�ڿ�ʼ��ַ��2GB�ĵ�ַ�ռ���в���
	for (; dwBase < 2 * dwOneGB; dwBase += dwOnePage){
		CompareAPage(dwBase, dwValue);
	}
	return TRUE;
}

void ShowList(){
	for (int i = 0; i < g_nListCnt; i++){
		printf("%08lX\n", g_arList[i]);
	}
}

// �������Ķ�ȡ���Ƕ����Ǹ���������ȽϽ��̵��ڴ��ַ��
BOOL FindNext(DWORD dwValue){
	int nOrgCnt = g_nListCnt;
	g_nListCnt = 0;

	BOOL bRet = FALSE;
	DWORD dwReadValue;
	for (int i = 0; i < nOrgCnt; i++){
		if (ReadProcessMemory(g_hProcess,
			(LPVOID)g_arList[i],
			&dwReadValue,
			sizeof(DWORD),
			NULL)){
			if (dwReadValue == dwValue){
				g_arList[g_nListCnt++] = g_arList[i];// ÿһ�ζ���һ�����
				bRet = TRUE;
			}
		}
	}
	return bRet;
}

BOOL WriteMemory(DWORD dwAddr, DWORD dwValue){
	return WriteProcessMemory(
		g_hProcess,
		(LPVOID)dwAddr,
		&dwValue,
		sizeof(DWORD),
		NULL);
}




int main(int argc, char* argv[]){
	char *szCommandLine = "C://Users//pc//Desktop//testor.exe";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;
	//��������
	CreateProcess(
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

	CloseHandle(pi.hThread);//�������̵߳Ļ��ر�

	g_hProcess = pi.hProcess;//����

	int iVal;
	printf("Input val:");
	scanf("%d", &iVal);
	//���е�һ�β���
	FindFirst(iVal);

	//��ӡ���������
	ShowList();
	while (g_nListCnt > 1){
		printf("Input val = ");
		scanf("%d", &iVal);
		FindNext(iVal);
		ShowList();
	}

	printf("New value = ");
	scanf("%d", &iVal);
	if (WriteMemory(g_arList[0], iVal)){
		printf("Write data successfully\n");
	}
	CloseHandle(g_hProcess);
	return 0;
}
