//lpRootPathName ����� NULLL������ʹ�ó������еĵ�ǰ·�����ڵĴ��̷�����


#include <windows.h>
#include <stdio.h>

//�������������������ȡ���������������пռ䣬�������ȴ�����Ϣ

//�������������ĸ�·�� �����硰D:\��

BOOL GetDiskSpaceInfo(LPCSTR pszDrive){
	DWORD64 qwFreeBytesToCaller, qwTotalBytes, qwFreeBytes;
	DWORD dwSectPerClust, dwBytesPerSect, dwFreeClusters, dwTotalClusters;

	BOOL bResult;

	//ʹ��GetDiskFreeSpaceEx��ȡ������Ϣ����ӡ���
	bResult = GetDiskFreeSpaceEx(pszDrive,
		(PULARGE_INTEGER)&qwFreeBytesToCaller,
		(PULARGE_INTEGER)&qwTotalBytes,
		(PULARGE_INTEGER)&qwFreeBytes);

	if (bResult){
		printf("ʹ��GetDiskFreeSpaceEx��ȡ������Ϣ�ռ�:\n");
		printf("�ɻ�õĿ��пռ�(�ֽ�):\t\t%I64d\n", qwFreeBytesToCaller);
		printf("���пռ䣨�ֽڣ���\t\t%I64d\n", qwFreeBytes);
		printf("�������������ֽڣ���\t\t%I64d\n", qwTotalBytes);
	}

	//ʹ��GetDiskFreeSpace��ȡ������Ϣ����ӡ����
	bResult = GetDiskFreeSpace(pszDrive,
		&dwSectPerClust,
		&dwBytesPerSect,
		&dwFreeClusters,
		&dwTotalClusters);

	if (bResult){
		printf("\nʹ��GetDiskFreeSpace��ȡ������Ϣ�ռ�\n");
		printf("���еĴ�����:\t\t%d\n", dwFreeClusters);
		printf("�ܴ�����:\t\t%d\n", dwTotalClusters);
		printf("ÿ�ص���������:\t\t%d\n", dwSectPerClust);

		printf("ÿ�������������ֽڣ�:\t\t%d\n", dwBytesPerSect);

		printf("���пռ䣨�ֽڣ�:\t\t%I64d\n", (DWORD64)dwFreeClusters*(DWORD64)dwSectPerClust*(DWORD64)dwBytesPerSect);

		printf("�������������ֽڣ�:\t\t%I64d\n", (DWORD64)dwTotalClusters*(DWORD64)dwSectPerClust*(DWORD64)dwBytesPerSect);
	}

	return bResult;
}


int main(int argc, char *argv[]){
	LPSTR szDrivePath = "C:\\";
	GetDiskSpaceInfo(szDrivePath);
	return 0;
}

