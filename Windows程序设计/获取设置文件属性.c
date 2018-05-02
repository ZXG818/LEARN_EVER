#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
/*
*功能：设置和获取文件属性等
*参数：显示第一个参数指定文件的属性，时间，大小
*		将第二个参数的属性设置为隐藏，只读
*返回值：0代表执行完成，1代表发生错误
*/

//函数声明
DWORD ShowFileAttributes(LPSTR lpParam1);
DWORD SetFileHiddenAndReadonly(LPSTR lpParam2);
DWORD ShowFileTime(PFILETIME lptime);
DWORD ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow);
DWORD ShowFileAttrInfo(DWORD dwAttribute);


int main(int argc, char *argv[]){
	LPSTR lpParam1 = malloc(sizeof(CHAR)*MAX_PATH);		// 初始化申请空间
	LPSTR lpParam2 = malloc(sizeof(CHAR)*MAX_PATH);
	printf("请输入第一个文件路径:");
	gets(lpParam1);
	printf("请输入第二个文件路径:");
	gets(lpParam2);
	printf("显示第一个参数指定文件的属性，时间，大小\n");
	printf("将第二个参数的属性设置为隐藏，只读\n");

	ShowFileAttributes(lpParam1);
	SetFileHiddenAndReadonly(lpParam2);
	free(lpParam1);
	free(lpParam2);
	return 0;
}


/*
获取并显示文件属性，调用ShowFileTime，ShowFileSize，和
ShowFileAttrInfo函数

参数：LPSTR szPath，获取并显示此文件的属性
返回值：0代表执行完成，1代表发生错误
*/
DWORD ShowFileAttributes(LPSTR szPath){
	//文件属性结构
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	printf("文件:%s\n", szPath);

	//获取文件属性
	if (!GetFileAttributesEx(szPath,
		GetFileExInfoStandard,
		&wfad)){
		printf("获取文件属性错误:%d\n", GetLastError());
		return 1;
	}

	//显示相关时间
	printf("创建时间:\t");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("最后访问时间:\t");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("最后修改时间:\t");
	ShowFileTime(&(wfad.ftLastWriteTime));

	//显示文件大小
	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);
	//显示文件属性
	ShowFileAttrInfo(wfad.dwFileAttributes);

	printf("HHHHHHHAAAAAAAAAAAAAAAAAAAA\n");

	return 0;
}

//功能：转换文件时间并打印
//参数：PFILETIME lptime，指向文件时间的指针
DWORD ShowFileTime(PFILETIME lptime){
	//文件时间结构
	FILETIME ftLocal;
	//系统时间结构
	SYSTEMTIME st;
	//调整为系统所在时区的时间
	FileTimeToLocalFileTime(lptime, &ftLocal);
	
	//将文件时间转化为系统格式，便于显示
	FileTimeToSystemTime(&ftLocal, &st);

	//显示时间信息字符串
	printf("%4d年%#02d月%#02d日，%#02d:%#02d:%#02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return 0;
}


//打印文件大小信息
//参数：DWORD dwFileSizeHigh,文件大小高32位
//DWORD dwFileSizeLow,文件大小低32位
DWORD ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow){
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	//移动32位
	liFileSize <<= sizeof(DWORD) * 8;
	liFileSize += dwFileSizeLow;
	printf("文件大小:\t%I64u字节\n", liFileSize);
	return 0;
}

DWORD ShowFileAttrInfo(DWORD dwAttribute){
	//依此判断属性，并显示
	printf("文件属性:\t");
	if (dwAttribute&FILE_ATTRIBUTE_ARCHIVE){
		printf("<ARCHIVE>");
	}
	if (dwAttribute&FILE_ATTRIBUTE_COMPRESSED)
		printf("压缩");
	if (dwAttribute &FILE_ATTRIBUTE_DIRECTORY)
		printf("目录");
	if (dwAttribute&FILE_ATTRIBUTE_ENCRYPTED)
		printf("加密");
	if (dwAttribute&FILE_ATTRIBUTE_HIDDEN)
		printf("隐藏");
	if (dwAttribute&FILE_ATTRIBUTE_NORMAL)
		printf("NORMAL");
	if (dwAttribute&FILE_ATTRIBUTE_OFFLINE)
		printf("OFFLINE");
	if (dwAttribute&FILE_ATTRIBUTE_READONLY)
		printf("只读");
	if (dwAttribute&FILE_ATTRIBUTE_SPARSE_FILE)
		printf("SPARSE");
	if (dwAttribute&FILE_ATTRIBUTE_SYSTEM)
		printf("系统文件");

	if (dwAttribute&FILE_ATTRIBUTE_TEMPORARY)
		printf("临时文件");
	printf("\n");
	return 0;
}


//将指定的文件设置为隐藏和只读
//参数：LPSTR szFileName,文件路径

DWORD SetFileHiddenAndReadonly(LPSTR szFileName){
	//获取原来文件的属性
	DWORD dwFileAttributes = GetFileAttributes(szFileName);
	//将只读和隐藏属性附加到原来的文件属性上
	dwFileAttributes |= FILE_ATTRIBUTE_READONLY;
	dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;

	//设置文档属性并判断是否成功
	if (SetFileAttributes(szFileName, dwFileAttributes)){
		printf("文件%s\n的隐藏和属性设置成功\n", dwFileAttributes);
	}
	else{
		printf("属性设置;%d\n", GetLastError());
	}

	return 0;
}





