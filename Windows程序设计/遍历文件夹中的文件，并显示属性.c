#include <windows.h>
#include <stdio.h>

//����Ŀ¼�µ��ļ�����Ŀ¼������ʾ�ļ����ļ������أ����ܵ�����
//������LPSTR szPathΪҪ������·��
//����0����ִ����ɣ�����1������뷢������
DWORD EnumerateFileInDrectory(LPSTR szPath){
	WIN32_FIND_DATA FindFileData;//һ���ṹ�壬�����Ǻܶ�����
	HANDLE hListFile;//����de�ļ����
	CHAR szFilePath[MAX_PATH];

	//���������Ŀ¼���ļ���·�����ַ�����ʹ��ͨ�����*��
	lstrcpy(szFilePath, szPath);
	//���г���������ڲ�������.txt�ı��ļ�
	//lstrcat(szFilePath,"\\*.txt");

	lstrcat(szFilePath, "\\*");
	//���ҵ�һ���ļ�/Ŀ¼����ò��Ҿ��
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	//�жϾ��
	if (hListFile == INVALID_HANDLE_VALUE){
		printf("����:%d\n", GetLastError());
		return 1;
	}
	else{
		do {
			/*���������ʾ������Ŀ¼���ϼ�Ŀ¼�ġ�.���͡�..��,����ʹ��ע�Ͳ��ֵĴ�����й���
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||lstrcmp(FindFileData.cFileName,TEXT(".."))==0){
			continue;
			}
			*/

			//��ӡ�ļ�����Ŀ¼��
			printf("%s\t\t", FindFileData.cFileName);
			//�ж��ļ����ԣ��Ƿ�Ϊ�����ļ������ļ���
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED){
				printf("����");
			}

			//�ж��ĵ����ԣ��Ƿ�Ϊ�����ļ����ļ���
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN){
				printf("����");
			}

			//�ж��ļ����ԣ��Ƿ�ΪĿ¼
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				printf("<DIR>");
			}
			printf("\n");
			//�Լ�������������������Խ����ж�
		} while (FindNextFile(hListFile, &FindFileData));
		CloseHandle(hListFile);//�رվ��
	}
	return 0;
}

int main(int argc, char *argv[]){
	LPSTR szFilePath = "C://Users//pc//Desktop";
	EnumerateFileInDrectory(szFilePath);
	return 0;
}

		
