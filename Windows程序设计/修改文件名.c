#include <stdio.h>
#include <stdlib.h>		//可以获取文件的后缀名
#include <sys/stat.h>   //获取文件的状态
#include <time.h>		//时间处理函数相关的头文件
#include <io.h>
#include <windows.h>
#include <fcntl.h>		//修改文件名的函数的头文件


//获取文件创建时间
void TransformFileMakeTime(struct stat buf, char *fileMakeTime){
	memset(fileMakeTime, 0, sizeof(fileMakeTime));//先全部置零
	strftime(fileMakeTime, 24, "%Y_%m_%d_%H_%M_%S", localtime(&buf.st_mtime));		//时间戳转化为标准
}

//更改文件名并且打印文件创建的时间
void ChangeFileName(PCHAR szFileFullPath){
	struct stat buf;
	stat(szFileFullPath, &buf);
	CHAR fileMakeTime[24];
	TransformFileMakeTime(buf, fileMakeTime);	//函数调用
	printf("%s\t", fileMakeTime);				//打印文件创建的时间



	//对全路径的每一部分进行分解
	CHAR szFileDrive[MAX_PATH];			//驱动器盘符
	CHAR szFileDir[MAX_PATH];			//中间的路径
	CHAR szFileExtension[MAX_PATH];		//文件后缀名


	//获取文件的每一个有用的部分，不想要的参数部分填NULL
	_splitpath(szFileFullPath, szFileDrive, szFileDir, NULL, szFileExtension);	


	CHAR szFileNewName[MAX_PATH];		//新文件名
	lstrcpy(szFileNewName, szFileDrive);
	lstrcat(szFileNewName, szFileDir);
	lstrcat(szFileNewName, "\\");
	lstrcat(szFileNewName, fileMakeTime);
	lstrcat(szFileNewName, szFileExtension);


	if (rename(szFileFullPath, szFileNewName)==0){//修改文件名
		printf("###############修改成功####################\n");
	}
	else{
		perror("rename");
		printf("**********************%s**********************\n", szFileNewName);
	}

}



//枚举文件
DWORD EnumListFile(LPSTR szPath){
	HANDLE hFileList;
	WIN32_FIND_DATA FileData;
	CHAR szFilePath[MAX_PATH];
	CHAR szFileFullPath[MAX_PATH];

	lstrcpy(szFilePath, szPath);
	lstrcat(szFilePath, "\\*");

	hFileList = FindFirstFile(szFilePath, &FileData);
	if (hFileList == INVALID_HANDLE_VALUE){
		printf("错误:%d\n", GetLastError());
		return 1;
	}

	else{
		do{//遍历文件
			if (lstrcmp(FileData.cFileName, TEXT(".")) == 0 || lstrcmp(FileData.cFileName, TEXT("..")) == 0){
				continue;
			}
			wsprintf(szFileFullPath, "%s\\%s", szPath, FileData.cFileName);

			ChangeFileName(szFileFullPath);
			printf("\t\t%s\n\n", szFileFullPath);
			
			if (FileData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY){	// 如果是文件夹就递归
				EnumListFile(szFileFullPath);
			}
		} while (FindNextFile(hFileList, &FileData));
	}
	CloseHandle(hFileList);
	return 0;
}




int main(int argc, char *argv[]){

	CHAR szFilePath[MAX_PATH] = "C:\\Users\\pc\\Desktop\\测试文件夹";
	EnumListFile(szFilePath);

	return 0;
}
