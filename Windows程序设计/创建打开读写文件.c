//��д�ļ�����ȡ�ļ���С֮ǰ����Ҫʹ�� CreateFile ������򿪵��ļ�������ļ����
#include <stdio.h>
#include <windows.h>

//��ȡ�ļ���С������ʮ�����Ƶ���ʽ��ӡ����
//������LPSTR szFilePath�ļ�·��

DWORD ReadFileContent(LPSTR szFilePath){
	//�ļ����
	HANDLE hFileRead;

	//�����ļ���С
	LARGE_INTEGER liFileSize;

	//�ɹ���ȡ�ļ����ݴ�С
	DWORD dwReadSize;

	//�ۼӼ����Ѿ���ȡ���ݵĴ�С
	LONGLONG liTotalRead = 0;

	//�ļ����ݻ���
	BYTE lpFileDataBuffer[32];


	//���Ѿ����ڵ��ļ�����ȡ����
	hFileRead = CreateFile(
		szFilePath,//Ҫ�򿪵��ļ���������·����
		GENERIC_READ,//�Զ���ʽ��
		FILE_SHARE_READ,//�ɹ����ȡ
		NULL,//Ĭ�ϰ�ȫ����
		OPEN_EXISTING,//ֻ���Ѿ����ڵ��ļ�
		FILE_ATTRIBUTE_NORMAL,//�����ļ�����
		NULL);

	//���ļ��Ƿ�ɹ�
	if (hFileRead == INVALID_HANDLE_VALUE){
		printf("���ļ�ʧ�ܣ�%d\n", GetLastError());
	}
	if (!GetFileSizeEx(hFileRead, &liFileSize)){
		printf("��ȡ�ļ���Сʧ��:%d\n", GetLastError());
	}
	else{
		printf("�ļ���С:%d\n", liFileSize.QuadPart);
	}


	//ѭ����ȡ���Ҵ�ӡ�ļ�����
	while (TRUE){
		DWORD i;
		if (!ReadFile(hFileRead,//���ļ��ľ��
			lpFileDataBuffer,//�洢��ȡ�ļ�����
			32,//���Ĵ�С���ֽڣ�
			&dwReadSize,//ʵ�ʶ�ȡ�Ĵ�С
			NULL)){//��ʹ��Overlapped

			printf("���ļ�����:%d\n", GetLastError());
			break;
		}
		printf("��ȡ��%d�ֽڣ��ļ������ǣ�", dwReadSize);
		for (i = 0; i < dwReadSize; i++){
			printf("0x%x ", lpFileDataBuffer[i]);
		}
		printf("\n");
		liTotalRead += dwReadSize;
		if (liTotalRead == liFileSize.QuadPart){
			printf("��ȡ�ļ�����\n");
			break;
		}
	}
	CloseHandle(hFileRead);
	return 0;
}

DWORD SaveDataToFile(
	LPSTR szFilePath,
	LPVOID lpData,
	DWORD dwDataSize){

	//�ļ����
	HANDLE hFileWrite;
	//�ɹ�д������ݴ�С
	DWORD dwWriteDataSize;
	//���Ѿ����ڵ��ļ�����ȡ����
	hFileWrite = CreateFile(
		szFilePath,//�ļ���
		GENERIC_WRITE,//��д�ķ�ʽ��
		0,			//�ɹ���
		NULL,		//Ĭ�ϰ�ȫ����
		OPEN_ALWAYS,   //���Ѿ����ڵ��ļ���û�оʹ���һ��
		FILE_ATTRIBUTE_NORMAL,//�����ļ�����
		NULL);//��ģ��

	if (hFileWrite == INVALID_HANDLE_VALUE){
		printf("���ļ�ʧ��:%d\n", GetLastError());
	}

	//�����ļ�ָ�뵽�ļ�ĩβ
	SetFilePointer(hFileWrite, 0, 0, FILE_END);

	//������д���ļ�
	if (!WriteFile(hFileWrite, lpData, dwDataSize, &dwWriteDataSize, NULL)){
		printf("д���ļ�ʧ��:%d\n", GetLastError());
	}
	else{
		printf("д���ļ��ɹ�,д��%d�ֽ�.\n", dwWriteDataSize);
	}
	CloseHandle(hFileWrite);
	return 0;
}


int main(int argc, char *argv[]){
	LPSTR szFileData = "����һ������";
	SaveDataToFile("C://Users//pc//Desktop//lizi.txt", szFileData, lstrlen(szFileData));
	ReadFileContent("C://Users//pc//Desktop//lizi.txt");
	return 0;
}
