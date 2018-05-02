#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH

//�оٹ��ص�
BOOL ProcessVolumeMountPoint(HANDLE hPt,
	TCHAR *PtBuf,
	DWORD dwPtBufSize,
	TCHAR *Buf){
	BOOL bFlag;			//���
	TCHAR Path[BUFSIZE]; //ȫ·��
	TCHAR Target[BUFSIZE];//���ص��豸

	printf("\t Volume mount point found is \"%s\"\n", PtBuf);
	lstrcpy(Path, Buf);//����·�������Ǵ������
	lstrcat(Path, PtBuf);

	bFlag = GetVolumeNameForVolumeMountPoint(Path, Target, BUFSIZE);//API��������

	if (!bFlag){
		printf("\t Attempt to get volume name for %s failed.\n", Path);
	}
	else{
		printf("\t Target of the volume mount point is %s.\n", Target);
	}

	bFlag = FindNextVolumeMountPoint(hPt, PtBuf, dwPtBufSize);

	return bFlag;
}

//�жϾ����ͣ��оٹ��ص�

BOOL ProcessVolume(HANDLE hVol,
	TCHAR *Buf,
	DWORD iBufSize){
	BOOL bFlag;			//���ر�־
	HANDLE hPt;			//����
	TCHAR PtBuf[BUFSIZE]; //���ص�·��
	DWORD dwSysFlags;   //�ļ�ϵͳ���
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];

	printf("Volume found is \"%s\".\n", Buf);

	//�Ƿ�ΪNTFS
	GetVolumeInformation(Buf, NULL, 0, NULL, NULL,
		&dwSysFlags,
		FileSysNameBuf,
		FILESYSNAMEBUFSIZE);

	if (!(dwSysFlags & FILE_SUPPORTS_REPARSE_POINTS)){
		printf("\t This file system does not support volume mount points.\n");
	}
	else{
		//�����еĹ��ص�
		hPt = FindFirstVolumeMountPoint(
			Buf,	//���·��
			PtBuf,  //���ص�·��
			BUFSIZE);

		if (hPt == INVALID_HANDLE_VALUE){
			printf("\t No volume mount points found!\n");
		}

		else{
			//������ص�
			bFlag = ProcessVolumeMountPoint(hPt,
				PtBuf,
				BUFSIZE,
				Buf);

			//ѭ��
			while (bFlag){
				bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);
			}

			//����
			FindVolumeMountPointClose(hPt);
		}
	}
	//��һ��
	bFlag = FindNextVolume(hVol, Buf, iBufSize);
	return bFlag;
}


//��ȡ���ص�

int GetMountPoint(void){
	TCHAR buf[BUFSIZE];//���ʶ��
	HANDLE hVol;//����
	BOOL bFlag;//�����־
	printf("Volume mount points info of this computer:\n\n");

	hVol = FindFirstVolume(buf, BUFSIZE);
	if (hVol == INVALID_HANDLE_VALUE){
		printf("No volumes found!\n");
		return -1;
	}

	bFlag = ProcessVolume(hVol, buf, BUFSIZE);

	while (bFlag){
		bFlag = ProcessVolume(hVol, buf, BUFSIZE);
	}

	bFlag = FindVolumeClose(hVol);
	return bFlag;
}

//ʹ�õ�˵������
void Usage(PCHAR argv){
	printf("\n\n\t%s,mount a volume at a mount point.\n", argv);
	printf("\tFor example ,\"mount D:\\mnt\\drives\\ E:\\\"\n");
}

int main(int argc, char *argv[]){
	BOOL bFlag;
	CHAR Buf[BUFSIZE];
	if (argc != 3){
		GetMountPoint();
		Usage(argv[0]);
		return -1;
	}

	bFlag = GetVolumeNameForVolumeMountPoint(
		argv[2],       //������ص����Ŀ¼
		Buf,		   //�������
		BUFSIZE);


	if (bFlag != TRUE){
		printf("Retrieving volume name for %s failed.\n", argv[2]);
		return -2;
	}

	printf("Volume name of %s is %s\n", argv[2], Buf);
	bFlag = SetVolumeMountPoint(
		argv[1],
		Buf);

	if (!bFlag){
		printf("Attempt to mount %s at %s failed.error code is \n", argv[2], argv[1], GetLastError());
	}
	return bFlag;
}

