#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE 512

//����·�������ж��Ƿ�Ϊ�������Ƿ�������
//��������������·��������D:\

int main(int argc, PCHAR argv[]){
	//�洢�ļ�ϵͳ�����
	CHAR szFileSystemNameBuffer[BUFSIZE];
	DWORD dwLastError;
	DWORD dwFileSystemFlags;

	//�ж��Ƿ���������ʱ�Ĳ���
	/*if (argc != 2){
		printf("�������������ĸ�·��������\"D:\\\"\n");
		return -1;
	}*/

	argv[1] = "D:\\";

	//�ж�������������Ƿ�ΪCD\DVD    ROM
	if (GetDriveType(argv[1]) != DRIVE_CDROM){
		printf("������ %s ����CD\DVD ROM��\n", argv[1]);
		return -1;
	}

	//��ȡ����Ϣ
	if (!GetVolumeInformation(
		argv[1],
		NULL,
		0,
		NULL,
		NULL,
		&dwFileSystemFlags,
		szFileSystemNameBuffer,
		BUFSIZE)){
		dwLastError = GetLastError();//�ռ�����
		if (dwLastError == 21){//�����������Ӧ����Ϣ
			printf("�豸û��׼���ã�����������!\n");
			return 0;
		}
		else{
			printf("GetVolumeInformation ���� %d\n", dwLastError);
			return 0;
		}
	}

	printf("�����Ѿ����룬�ļ�ϵͳ���%s\n", szFileSystemNameBuffer);
	return 0;
}

