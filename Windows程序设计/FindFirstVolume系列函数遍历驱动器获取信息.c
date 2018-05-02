#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
//���ַ���������ʽ:  \\volume{GUID}����ʽ���������豸��

#define BUFSIZE 1024

//��������
BOOL GetDriverInfo(LPSTR szDrive);

/*����:Ӧ�ó���������������������������
GetDriverInfo��ȡ����������*/

int main(int argc, char *argv[]){
	TCHAR buf[BUFSIZE];//�����Ϣ
	HANDLE hVol;//��������
	BOOL bFlag;

	hVol = FindFirstVolume(buf, BUFSIZE);

	if (hVol == INVALID_HANDLE_VALUE){
		printf("No volumes found!\n");
		return -1;
	}

	GetDriverInfo(buf);

	//��ʵFindFirstVolume+FindNextVolume�����ͺ����Ǳ��������е�
	//Process32First+Process32Next����

	while (FindNextVolume(hVol,
		buf,
		BUFSIZE)){
		GetDriverInfo(buf);
	}

	bFlag = FindVolumeClose(hVol);//��������þ�Ҫ�ر�

	return bFlag;
}

//����:��ȡ������������
//������LPSTR szDrive
//ָ��Ҫ��ȡ���Ե��������ĸ�·������C:\
//����ֵΪBOOL����ʾ�Ƿ�ɹ�
BOOL GetDriverInfo(LPSTR szDrive){
	UINT uDriveType;
	DWORD dwVolumeSerialNumber;
	DWORD dwMaximumComponentLength;
	DWORD dwFileSystemFlags;
	CHAR szFileSystemNameBuffer[BUFSIZE];
	CHAR szDriveName[MAX_PATH];
	printf("\n%s\n", szDrive);
	uDriveType = GetDriveType(szDrive);//��ȡ������������
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
	printf("....\n");//��ӡ������һЩ����
	return TRUE;
}


