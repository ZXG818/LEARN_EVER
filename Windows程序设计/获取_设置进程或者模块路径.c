#include <windows.h>
#include <stdio.h>
int main(int argc, char *argv[]){
	//���ڴ洢��ǰ·��
	CHAR szCurrentDirectory[MAX_PATH];
	//���ڴ洢ģ��·��
	CHAR szMoudlePath[MAX_PATH];
	//Kernel32�ļ�������
	LPSTR szKernel32 = "kernel32.dll";
	HMODULE hKernel32;
	//��ǰ·���ĳ��ȣ�Ҳ�����жϻ�ȡ�Ƿ�ɹ�
	DWORD dwCurDirPathLen;

	//��ȡ���̵�ǰĿ¼
	dwCurDirPathLen = GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	if (dwCurDirPathLen == 0){
		printf("��ȡ��ǰĿ¼����:%d\n", GetLastError());
		return 0;
	}

	printf("���̵�ǰĿ¼Ϊ:%s\n", szCurrentDirectory);

	//�����̵�ǰĿ¼����Ϊ:C:\

	lstrcpy(szCurrentDirectory, "C:\\");
	if (!SetCurrentDirectory(szCurrentDirectory)){
		printf("���õ�ǰĿ¼����:%d\n", GetLastError());
		return 0;
	}

	printf("�Ѿ����õ�ǰĿ¼Ϊ:%s\n", szCurrentDirectory);

	//�ڵ�ǰĿ¼�´�����Ŀ¼"current_dir"
	CreateDirectory("current_dir", NULL);

	//�ٴλ�ȡϵͳ��ǰĿ¼
	dwCurDirPathLen = GetCurrentDirectory(MAX_PATH, szCurrentDirectory);
	if (dwCurDirPathLen == 0){
		printf("��ȡ��ǰĿ¼ʧ��:%d\n", GetLastError());
		return 0;
	}
	printf("GetCurrentDirectory��ȡ��ǰĿ¼Ϊ:%s\n", szCurrentDirectory);

	//ʹ��NULL��������ȡ��ģ���·��
	if (!GetModuleFileName(NULL, szMoudlePath, MAX_PATH)){
		printf("��ȡģ��·������:%d\n", GetLastError());
		return 0;
	}

	printf("��ģ��·��:%s\n", szMoudlePath);

	//��ȡKernel32.dllģ����
	hKernel32 = LoadLibrary(szKernel32);
	if (!GetModuleFileName(hKernel32, szMoudlePath, MAX_PATH)){
		printf("��ȡģ��·������:%d\n", GetLastError());
		return 0;
	}

	printf("Kernel32ģ��·��%s\n", szMoudlePath);
	return 0;
}



//�ڽ�����ʹ�����·���� �����·������ʼ���ǳ���ĵ�ǰ·�������ǿ�ִ���ļ���
//�ڵ�·����


//���̵ĵ�ǰ·����Ĭ���������Ӧ�ó����ִ���ļ����ڵ�·����


//ģ��·�������ĵ�ǰ·��������������̵�������ͽ����������ص����� DLL
//���ǽ��̵�ģ��