#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <tlhelp32.h>
int main(int argc, char* argv[]){
	PROCESSENTRY32 pe32;
	//��ʹ������ṹ֮ǰ�����������Ĵ�С
	pe32.dwSize = sizeof(pe32);
	//��ϵͳ�ڵ����еĽ�����һ������
	HANDLE hProcessSnap = ::CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	if (hProcessSnap == INVALID_HANDLE_VALUE){
		printf("CreateToolhelp32Snapshot����ʧ�ܣ�\n");
	}
	//�������̿��գ�������ʾÿ�����̵���Ϣ
	BOOL bMore = ::Process32First(hProcessSnap, &pe32);
	while (bMore){//�������ɵ��б�
		printf("��������:%s\n", pe32.szExeFile);
		printf("����ID��:%u\n\n", pe32.th32ProcessID);
		bMore = ::Process32Next(hProcessSnap, &pe32);
	}

	//��Ҫ�������snapshot����
	::CloseHandle(hProcessSnap);
	return 0;
}
