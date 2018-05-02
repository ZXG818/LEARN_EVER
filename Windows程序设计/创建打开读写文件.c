//读写文件、获取文件大小之前都需要使用 CreateFile 创建或打开的文件，获得文件句柄
#include <stdio.h>
#include <windows.h>

//读取文件大小，并以十六进制的形式打印出来
//参数：LPSTR szFilePath文件路径

DWORD ReadFileContent(LPSTR szFilePath){
	//文件句柄
	HANDLE hFileRead;

	//保存文件大小
	LARGE_INTEGER liFileSize;

	//成功读取文件数据大小
	DWORD dwReadSize;

	//累加计算已经读取数据的大小
	LONGLONG liTotalRead = 0;

	//文件数据缓存
	BYTE lpFileDataBuffer[32];


	//打开已经存在的文件，读取内容
	hFileRead = CreateFile(
		szFilePath,//要打开的文件名（包含路径）
		GENERIC_READ,//以读方式打开
		FILE_SHARE_READ,//可共享读取
		NULL,//默认安全设置
		OPEN_EXISTING,//只打开已经存在的文件
		FILE_ATTRIBUTE_NORMAL,//常规文件属性
		NULL);

	//打开文件是否成功
	if (hFileRead == INVALID_HANDLE_VALUE){
		printf("打开文件失败：%d\n", GetLastError());
	}
	if (!GetFileSizeEx(hFileRead, &liFileSize)){
		printf("获取文件大小失败:%d\n", GetLastError());
	}
	else{
		printf("文件大小:%d\n", liFileSize.QuadPart);
	}


	//循环读取并且打印文件内容
	while (TRUE){
		DWORD i;
		if (!ReadFile(hFileRead,//读文件的句柄
			lpFileDataBuffer,//存储读取文件内容
			32,//读的大小（字节）
			&dwReadSize,//实际读取的大小
			NULL)){//不使用Overlapped

			printf("读文件错误:%d\n", GetLastError());
			break;
		}
		printf("读取了%d字节，文件内容是：", dwReadSize);
		for (i = 0; i < dwReadSize; i++){
			printf("0x%x ", lpFileDataBuffer[i]);
		}
		printf("\n");
		liTotalRead += dwReadSize;
		if (liTotalRead == liFileSize.QuadPart){
			printf("读取文件结束\n");
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

	//文件句柄
	HANDLE hFileWrite;
	//成功写入的数据大小
	DWORD dwWriteDataSize;
	//打开已经存在的文件，读取内容
	hFileWrite = CreateFile(
		szFilePath,//文件名
		GENERIC_WRITE,//以写的方式打开
		0,			//可共享
		NULL,		//默认安全设置
		OPEN_ALWAYS,   //打开已经存在的文件，没有就创建一个
		FILE_ATTRIBUTE_NORMAL,//常规文件属性
		NULL);//无模板

	if (hFileWrite == INVALID_HANDLE_VALUE){
		printf("打开文件失败:%d\n", GetLastError());
	}

	//设置文件指针到文件末尾
	SetFilePointer(hFileWrite, 0, 0, FILE_END);

	//将数据写入文件
	if (!WriteFile(hFileWrite, lpData, dwDataSize, &dwWriteDataSize, NULL)){
		printf("写入文件失败:%d\n", GetLastError());
	}
	else{
		printf("写入文件成功,写入%d字节.\n", dwWriteDataSize);
	}
	CloseHandle(hFileWrite);
	return 0;
}


int main(int argc, char *argv[]){
	LPSTR szFileData = "这是一个例子";
	SaveDataToFile("C://Users//pc//Desktop//lizi.txt", szFileData, lstrlen(szFileData));
	ReadFileContent("C://Users//pc//Desktop//lizi.txt");
	return 0;
}
