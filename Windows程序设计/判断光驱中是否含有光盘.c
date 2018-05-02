#include <stdio.h>
#include <windows.h>
#include <tchar.h>

#define BUFSIZE 512

//根据路径参数判断是否为光驱，是否放入光盘
//参数：驱动器根路径，例如D:\

int main(int argc, PCHAR argv[]){
	//存储文件系统类别名
	CHAR szFileSystemNameBuffer[BUFSIZE];
	DWORD dwLastError;
	DWORD dwFileSystemFlags;

	//判断是否输入运行时的参数
	/*if (argc != 2){
		printf("请输入驱动器的根路径，比如\"D:\\\"\n");
		return -1;
	}*/

	argv[1] = "D:\\";

	//判断输入的驱动器是否为CD\DVD    ROM
	if (GetDriveType(argv[1]) != DRIVE_CDROM){
		printf("驱动器 %s 不是CD\DVD ROM。\n", argv[1]);
		return -1;
	}

	//获取卷信息
	if (!GetVolumeInformation(
		argv[1],
		NULL,
		0,
		NULL,
		NULL,
		&dwFileSystemFlags,
		szFileSystemNameBuffer,
		BUFSIZE)){
		dwLastError = GetLastError();//收集错误
		if (dwLastError == 21){//错误代号所对应的信息
			printf("设备没有准备好，请勿放入光盘!\n");
			return 0;
		}
		else{
			printf("GetVolumeInformation 错误 %d\n", dwLastError);
			return 0;
		}
	}

	printf("光盘已经放入，文件系统类别：%s\n", szFileSystemNameBuffer);
	return 0;
}

