#include <windows.h>
#include <stdio.h>

//全局变量
//记录所有的文件和目录数
DWORD dwTotalFileNum = 0;


//遍历函数
DWORD ListAllFileInDir(LPSTR szPath){
	CHAR szFilePath[MAX_PATH];
	WIN32_FIND_DATA FindFileData;
	HANDLE hListFile;

	CHAR szFullPath[MAX_PATH];
	//构造代表子目录和文件夹路径的字符串,使用通配符*
	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");

	//查找第一个文件目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath, &FindFileData);

	if (hListFile == INVALID_HANDLE_VALUE){
		printf("出错:%d\n", GetLastError());
		return 1;
	}

	else{
		do{
			//过滤调.和.. ，不需要遍历
			if (lstrcmp(FindFileData.cFileName, TEXT(".")) == 0 || lstrcmp(FindFileData.cFileName, TEXT("..")) == 0){
				continue;
			}

			//构造成全路径
			wsprintf(szFullPath, "%s\\%s", szPath, FindFileData.cFileName);
			dwTotalFileNum++;

			printf("\n%d\t%s\t", dwTotalFileNum, szFullPath);
			//如果是目录，则递归调用，列举下级目录
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
	printf("请输入文件夹路径:");
	scanf("%s", szFilePath);
	//GetCurrentDirectory是获取进程的当前目录
	//GetCurrentDirectory(MAX_PATH, szFilePath);//加上这句则不是全部文件夹和文件，是当前的进程目录
	ListAllFileInDir(szFilePath);
	return 0;
}
