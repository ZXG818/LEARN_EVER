#include <windows.h>
#include <stdio.h>

//遍历目录下的文件和子目录，将显示文件和文件夹隐藏，加密的属性
//参数：LPSTR szPath为要遍历的路径
//返回0代表执行完成，返回1代表代码发生错误
DWORD EnumerateFileInDrectory(LPSTR szPath){
	WIN32_FIND_DATA FindFileData;//一个结构体，其中是很多属性
	HANDLE hListFile;//查找de文件句柄
	CHAR szFilePath[MAX_PATH];

	//构造代表子目录和文件夹路径的字符串，使用通配符‘*’
	lstrcpy(szFilePath, szPath);
	//下行程序可以用于查找所有.txt文本文件
	//lstrcat(szFilePath,"\\*.txt");

	lstrcat(szFilePath, "\\*");
	//查找第一个文件/目录，获得查找句柄
	hListFile = FindFirstFile(szFilePath, &FindFileData);
	//判断句柄
	if (hListFile == INVALID_HANDLE_VALUE){
		printf("错误:%d\n", GetLastError());
		return 1;
	}
	else{
		do {
			/*如果不想显示代表本级目录和上级目录的“.”和“..”,可以使用注释部分的代码进行过滤
			if(lstrcmp(FindFileData.cFileName,TEXT("."))==0||lstrcmp(FindFileData.cFileName,TEXT(".."))==0){
			continue;
			}
			*/

			//打印文件名，目录名
			printf("%s\t\t", FindFileData.cFileName);
			//判断文件属性，是否为加密文件或者文件夹
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_ENCRYPTED){
				printf("加密");
			}

			//判断文档属性，是否为隐藏文件或文件夹
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_HIDDEN){
				printf("隐藏");
			}

			//判断文件属性，是否为目录
			if (FindFileData.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY){
				printf("<DIR>");
			}
			printf("\n");
			//自己还可以添加其他的属性进行判断
		} while (FindNextFile(hListFile, &FindFileData));
		CloseHandle(hListFile);//关闭句柄
	}
	return 0;
}

int main(int argc, char *argv[]){
	LPSTR szFilePath = "C://Users//pc//Desktop";
	EnumerateFileInDrectory(szFilePath);
	return 0;
}

		
