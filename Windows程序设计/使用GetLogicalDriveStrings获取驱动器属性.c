#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#define BUFSIZE 1024

//函数声明
BOOL GetDriverInfo(LPSTR szDrive);


int main(int argc, char *argv[]){
	CHAR szLogicalDriveStrings[BUFSIZE];
	PCHAR szDrive;

	ZeroMemory(szLogicalDriveStrings, BUFSIZE);//BUFSIZE内存块全部置零

	//获取逻辑驱动器卷标名
	GetLogicalDriveStrings(BUFSIZE - 1, szLogicalDriveStrings);
	szDrive = (PCHAR)szLogicalDriveStrings;
	//循环处理每个卷
	do{
		if (!GetDriverInfo(szDrive)){
			printf("\nGet Volume Information Error: %d", GetLastError());
		}
		szDrive += (lstrlen(szDrive) + 1);//向下滑动
	} while (*szDrive != '\x00');


	return 0;
}



//功能:获取驱动器的属性
//参数：LPSTR szDrive
//指明要获取属性的驱动器的根路径，如C:\
//返回值为BOOL：表示是否成功
BOOL GetDriverInfo(LPSTR szDrive){
	UINT uDriveType;
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	CHAR szFileSystemNameBuffer[BUFSIZE];
	CHAR szDriveName[MAX_PATH];
	printf("\n%s\n", szDrive);
	uDriveType = GetDriveType(szDrive);//获取驱动器的类型
	switch (uDriveType){
	case DRIVE_UNKNOWN:
		printf("The drive type cannot be determined.");
		break;
	case DRIVE_NO_ROOT_DIR:
		printf("The root path is invalid, for example, no volume is mounted at the path.");
		break;
	case DRIVE_REMOVABLE:
		printf("The drive is a type has removable media, for example ,a floopy drive or removable hard disk.");
		break;
	case DRIVE_FIXED:
		printf("The drive is a type that cannot be removed ,for example, a fixed hard drive.");
		break;
	case DRIVE_REMOTE:
		printf("The drive is a remote (network) drive.");
		break;
	case DRIVE_CDROM:
		printf("The drive is a CD-ROM drive.");
		break;
	case DRIVE_RAMDISK:
		printf("The drive is a RAM disk.");
		break;
	}

	if (!GetVolumeInformation(
		szDrive,
		szDriveName,
		MAX_PATH,
		&dwVolumeSerialNumber,
		&dwMaximumComponentLength,
		&dwFileSystemFlags,
		szFileSystemNameBuffer,
		BUFSIZE)){
		return FALSE;
	}

	if (lstrlen(szDriveName) != 0){
		printf("\nDrive Name is %s\n", szDriveName);
	}
	printf("\nVolume Serial Number is %u", dwVolumeSerialNumber);
	printf("\nMaximum Component Length is %u", dwMaximumComponentLength);
	printf("\nSystem Type is %s\n", szFileSystemNameBuffer);

	if (dwFileSystemFlags & FILE_SUPPORTS_REPARSE_POINTS){
		printf("The file system does not support volume mount points.\n");
	}
	if (dwFileSystemFlags & FILE_VOLUME_QUOTAS){
		printf("The file system sypports disk quotas.\n");
	}
	if (dwFileSystemFlags & FILE_CASE_SENSITIVE_SEARCH){
		printf("The file system supports case-sensitive file names.\n");
	}
	printf("....\n");//打印其他的一些属性
	return TRUE;
}
