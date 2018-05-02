#include <stdlib.h>
#include <stdio.h>
#include <windows.h>
#include <tlhelp32.h>
#include <stdbool.h>

BOOL FindFirst(DWORD dwValue);
BOOL FindNext(DWORD dwValue);
DWORD g_arList[1024];// 地址列表
int g_nListCnt;// 有效地址的个数
HANDLE g_hProcess;// 目标进程句柄

BOOL CompareAPage(DWORD dwBaseAddr, DWORD dwValue){
	// 读取一页内存
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
	// Windows版本判断
	if (vi.dwPlatformId == VER_PLATFORM_WIN32_WINDOWS){
		dwBase = 4 * 1024 * 1024;// Windows 98系列，4MB
	}
	else{
		dwBase = 64 * 1024;// Windows NT系列 ，64KB
	}

	//在开始地址到2GB的地址空间进行查找
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

// 接下来的读取就是都在那个数组里面比较进程的内存地址了
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
				g_arList[g_nListCnt++] = g_arList[i];// 每一次都是一层过滤
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
	//创建进程
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

	CloseHandle(pi.hThread);//不用主线程的话关闭

	g_hProcess = pi.hProcess;//进程

	int iVal;
	printf("Input val:");
	scanf("%d", &iVal);
	//进行第一次查找
	FindFirst(iVal);

	//打印出搜索结果
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
