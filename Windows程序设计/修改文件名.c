#include <stdio.h>
#include <stdlib.h>		//���Ի�ȡ�ļ��ĺ�׺��
#include <sys/stat.h>   //��ȡ�ļ���״̬
#include <time.h>		//ʱ�䴦������ص�ͷ�ļ�
#include <io.h>
#include <windows.h>
#include <fcntl.h>		//�޸��ļ����ĺ�����ͷ�ļ�


//��ȡ�ļ�����ʱ��
void TransformFileMakeTime(struct stat buf, char *fileMakeTime){
	memset(fileMakeTime, 0, sizeof(fileMakeTime));//��ȫ������
	strftime(fileMakeTime, 24, "%Y_%m_%d_%H_%M_%S", localtime(&buf.st_mtime));		//ʱ���ת��Ϊ��׼
}

//�����ļ������Ҵ�ӡ�ļ�������ʱ��
void ChangeFileName(PCHAR szFileFullPath){
	struct stat buf;
	stat(szFileFullPath, &buf);
	CHAR fileMakeTime[24];
	TransformFileMakeTime(buf, fileMakeTime);	//��������
	printf("%s\t", fileMakeTime);				//��ӡ�ļ�������ʱ��



	//��ȫ·����ÿһ���ֽ��зֽ�
	CHAR szFileDrive[MAX_PATH];			//�������̷�
	CHAR szFileDir[MAX_PATH];			//�м��·��
	CHAR szFileExtension[MAX_PATH];		//�ļ���׺��


	//��ȡ�ļ���ÿһ�����õĲ��֣�����Ҫ�Ĳ���������NULL
	_splitpath(szFileFullPath, szFileDrive, szFileDir, NULL, szFileExtension);	


	CHAR szFileNewName[MAX_PATH];		//���ļ���
	lstrcpy(szFileNewName, szFileDrive);
	lstrcat(szFileNewName, szFileDir);
	lstrcat(szFileNewName, "\\");
	lstrcat(szFileNewName, fileMakeTime);
	lstrcat(szFileNewName, szFileExtension);


	if (rename(szFileFullPath, szFileNewName)==0){//�޸��ļ���
		printf("###############�޸ĳɹ�####################\n");
	}
	else{
		perror("rename");
		printf("**********************%s**********************\n", szFileNewName);
	}

}



//ö���ļ�
DWORD EnumListFile(LPSTR szPath){
	HANDLE hFileList;
	WIN32_FIND_DATA FileData;
	CHAR szFilePath[MAX_PATH];
	CHAR szFileFullPath[MAX_PATH];

	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");

	hFileList = FindFirstFile(szFilePath, &FileData);
	if (hFileList == INVALID_HANDLE_VALUE){
		printf("����:%d\n", GetLastError());
		return 1;
	}

	else{
		do{//�����ļ�
			if (lstrcmp(FileData.cFileName, TEXT(".")) == 0 || lstrcmp(FileData.cFileName, TEXT("..")) == 0){
				continue;
			}
			wsprintf(szFileFullPath, "%s\\%s", szPath, FileData.cFileName);

			ChangeFileName(szFileFullPath);
			printf("\t\t%s\n\n", szFileFullPath);
			
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){	// ������ļ��о͵ݹ�
				EnumListFile(szFileFullPath);
			}
		} while (FindNextFile(hFileList, &FileData));
	}
	CloseHandle(hFileList);
	return 0;
}




int main(int argc, char *argv[]){

	CHAR szFilePath[MAX_PATH] = "C:\\Users\\pc\\Desktop\\�����ļ���";
	EnumListFile(szFilePath);

	return 0;
}
