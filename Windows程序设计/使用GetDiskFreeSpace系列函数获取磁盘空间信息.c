//lpRootPathName 如果是 NULLL，函数使用程序运行的当前路径所在的磁盘分区。


#include <windows.h>
#include <stdio.h>

//根据输入的驱动器，获取磁盘总容量，空闲空间，簇数量等磁盘信息

//参数：驱动器的根路径 ，例如“D:\”

BOOL GetDiskSpaceInfo(LPCSTR pszDrive){
	DWORD64 qwFreeBytesToCaller, qwTotalBytes, qwFreeBytes;
	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;

	BOOL bResult;

	//使用GetDiskFreeSpaceEx获取磁盘信息并打印结果
	bResult = GetDiskFreeSpaceEx(pszDrive,
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);

	if (bResult){
		printf("使用GetDiskFreeSpaceEx获取磁盘信息空间:\n");
		printf("可获得的空闲空间(字节):\t\t%I64d\n", qwFreeBytesToCaller);
		printf("空闲空间（字节）：\t\t%I64d\n", qwFreeBytes);
		printf("磁盘总容量（字节）：\t\t%I64d\n", qwTotalBytes);
	}

	//使用GetDiskFreeSpace获取磁盘信息并打印出来
	bResult = GetDiskFreeSpace(pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters);

	if (bResult){
		printf("\n使用GetDiskFreeSpace获取磁盘信息空间\n");
		printf("空闲的簇数量:\t\t%d\n", dwFreeClusters);
		printf("总簇数量:\t\t%d\n", dwTotalClusters);
		printf("每簇的扇区数量:\t\t%d\n", dwSectPerClust);

		printf("每扇区的容量（字节）:\t\t%d\n", dwBytesPerSect);

		printf("空闲空间（字节）:\t\t%I64d\n", (DWORD64)dwFreeClusters*(DWORD64)dwSectPerClust*(DWORD64)dwBytesPerSect);

		printf("磁盘总容量（字节）:\t\t%I64d\n", (DWORD64)dwTotalClusters*(DWORD64)dwSectPerClust*(DWORD64)dwBytesPerSect);
	}

	return bResult;
}


int main(int argc, char *argv[]){
	LPSTR szDrivePath = "C:\\";
	GetDiskSpaceInfo(szDrivePath);
	return 0;
}

