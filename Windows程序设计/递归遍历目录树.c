#include <windows.h>
#include <stdio.h>

//ȫ�ֱ���
//��¼���е��ļ���Ŀ¼��
DWORD dwTotalFileNum = 0;


//��������
DWORD ListAllFileInDir(LPSTR szPath){
	CHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;

	CHAR szFullPath[MAX_PATH];
	//���������Ŀ¼���ļ���·�����ַ���,ʹ��ͨ���*
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");

	//���ҵ�һ���ļ�Ŀ¼����ò��Ҿ��
	hListFile = FindFirstFile(szFilePath, &FindFileData);

	if (hListFile == INVALID_HANDLE_VALUE){
		printf("����:%d\n", GetLastError());
		return 1;
	}

	else{
		do{
			//���˵�.��.. ������Ҫ����
			if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 || lstrcmp(FindFileData.cFileName, TEXT("..")) == 0){
				continue;
			}

			//�����ȫ·��
			wsprintf(szFullPath, "%s\\%s", szPath, FindFileData.cFileName);
			dwTotalFileNum++;

			printf("\n%d\t%s\t", dwTotalFileNum, szFullPath);
			//�����Ŀ¼����ݹ���ã��о��¼�Ŀ¼
			if (FindFileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){
				printf("<DIR>");
				ListAllFileInDir(szFullPath);
			}
		} while (FindNextFile(hListFile, &FindFileData));
	}
	return 0;
}

int main(int argc, PCHAR argv[]){
	LPSTR szFilePath[MAX_PATH];
	printf("�������ļ���·��:");
	scanf("%s", szFilePath);
	//GetCurrentDirectory�ǻ�ȡ���̵ĵ�ǰĿ¼
	//GetCurrentDirectory(MAX_PATH, szFilePath);//�����������ȫ���ļ��к��ļ����ǵ�ǰ�Ľ���Ŀ¼
	ListAllFileInDir(szFilePath);
	return 0;
}
