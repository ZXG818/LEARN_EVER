//�ڴ��޸���

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <windows.h>
#include <tlhelp32.h>

BOOL FindFirst(DWORD dwValue);// ��Ŀ����̿ռ���е�һ������
BOOL FindNext(DWORD dwValue);// ��Ŀ����̿ռ���е�N������
DWORD g_arList[1024];// ��ַ�б�
int g_nListCnt;// ��Ч��ַ�ĸ���
HANDLE g_hProcess;// Ŀ����̾��
BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue);
void ShowList();

BOOL WriteMemory(DWORD dwAddr, DWORD dwValue);//д���̸ı��ڴ溯������


int main(void){
	//����02Testor����
	char *szFileName = "C://Users//pc//Desktop//testor.exe";
	STARTUPINFO si = { sizeof(si) };
	PROCESS_INFORMATION pi;
	si.dwFlags = STARTF_USESHOWWINDOW;
	si.wShowWindow = TRUE;

	CreateProcess(
		NULL,
		szFileName,
		NULL,
		NULL,
		FALSE,
		CREATE_NEW_CONSOLE,
		NULL,
		NULL,
		&si,
		&pi);

	//�ر��߳̾������Ȼ���ǲ�ʹ����
	CloseHandle(pi.hThread);

	g_hProcess = pi.hProcess;

	//����Ҫ�޸ĵ�ֵ
	int iVal;
	printf("Input val = ");
	scanf("%d", &iVal);

	//���е�һ�β���
	FindFirst(iVal);
	//��ӡ�������
	ShowList();


	while (g_nListCnt > 1){
		printf("Input val=");
		scanf("%d", &iVal);
		//�����´�����
		FindNext(iVal);
		//��ʾ�������
		ShowList();
	}
	printf("New Value = ");
	scanf("%d", &iVal);
	if (WriteMemory(g_arList[0], iVal)){
		printf("Write data success\n");
	}

	CloseHandle(g_hProcess);
	return 0;
}




//��ҳ�������ڴ�
BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue){
	//��ȡ1ҳ�ڴ�
	BYTE arBytes[4096];
	if (!ReadProcessMemory(g_hProcess, (LPVOID)dwBaseAddr, arBytes, 4096, NULL)){
		return FALSE;//��ҳ���ɶ�
	}

	//����һҳ�ڴ��в���
	DWORD *pdw;
	for (int i = 0; i < (int)4 * 1024 - 3; i++){
		pdw = (DWORD*)&arBytes[i];
		if (pdw[0] == dwValue){//����Ҫ���ҵ�ֵ?
			if (g_nListCnt >= 1024){
				return FALSE;
			}
			//��ӵ�ȫ�ֱ�����
			g_arList[g_nListCnt++] = dwBaseAddr + i;
		}
	}
	return TRUE;
}


BOOL FindFirst(DWORD dwValue){
	const DWORD dwOneGB = 1024 * 1024 * 1024;//1GB
	const DWORD dwOnePage = 4 * 1024;//4KB,һҳ�ڴ��С4KB
	if (g_hProcess == NULL){
		return FALSE;
	}

	//�鿴����ϵͳ�����ͣ��Ծ�����ʼ��ַ
	DWORD dwBase;
	OSVERSIONINFO vi = { sizeof(vi) };
	GetVersionEx(&vi);
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS){
		dwBase = 4 * 1024 * 1024;//Windows 98ϵ�У�4MB
	}
	else{
		dwBase = 640 * 1024;//Windows NTϵ�У�64KB
	}
	for (; dwBase < 2 * dwOneGB; dwBase += dwOnePage){
		//�Ƚ�1ҳ��С���ڴ�
		CompareAPage(dwBase, dwValue);
	}
	return TRUE;
}

void ShowList(){
	for (int i = 0; i < g_nListCnt; i++){
		printf("%08lX\n", g_arList[i]);
	}
}



BOOL FindNext(DWORD dwValue){
	//����m_arList��������Ч��ַ�ĸ�������ʼ���µ�m_nListCnt��ֵ
	int nOrgCnt = g_nListCnt;
	g_nListCnt = 0;
	//��m_arList�����¼�ĵ�ַ������
	BOOL bRet = FALSE;//����ʧ��
	DWORD dwReadValue;
	for (int i = 0; i < nOrgCnt; i++){
		if (ReadProcessMemory(g_hProcess, (LPVOID)g_arList[i], &dwReadValue, sizeof(DWORD), NULL)){
			if (dwReadValue == dwValue){
				g_arList[g_nListCnt++] = g_arList[i];
				bRet = TRUE;
			}
		}
	}
	return TRUE;
}

BOOL WriteMemory(DWORD dwAddr, DWORD dwValue){
	return WriteProcessMemory(
		g_hProcess,
		(LPVOID)dwAddr,
		&dwValue,
		sizeof(DWORD),
		NULL);
}

