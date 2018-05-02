#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE MAX_PATH
#define FILESYSNAMEBUFSIZE MAX_PATH

//列举挂载点
BOOL ProcessVolumeMountPoint(HANDLE hPt,
	TCHAR *PtBuf,
	DWORD dwPtBufSize,
	TCHAR *Buf){
	BOOL bFlag;			//结果
	TCHAR Path[BUFSIZE]; //全路径
	TCHAR Target[BUFSIZE];//挂载点设备

	printf("\t Volume mount point found is \"%s\"\n", PtBuf);
	lstrcpy(Path, Buf);//复制路径，就是传入参数
	lstrcat(Path, PtBuf);

	bFlag = GetVolumeNameForVolumeMountPoint(Path, Target, BUFSIZE);//API函数调用

	if (!bFlag){
		printf("\t Attempt to get volume name for %s failed.\n", Path);
	}
	else{
		printf("\t Target of the volume mount point is %s.\n", Target);
	}

	bFlag = FindNextVolumeMountPoint(hPt, PtBuf, dwPtBufSize);

	return bFlag;
}

//判断卷类型，列举挂载点

BOOL ProcessVolume(HANDLE hVol,
	TCHAR *Buf,
	DWORD iBufSize){
	BOOL bFlag;			//返回标志
	HANDLE hPt;			//卷句柄
	TCHAR PtBuf[BUFSIZE]; //挂载点路径
	DWORD dwSysFlags;   //文件系统标记
	TCHAR FileSysNameBuf[FILESYSNAMEBUFSIZE];

	printf("Volume found is \"%s\".\n", Buf);

	//是否为NTFS
	GetVolumeInformation(Buf, NULL, 0, NULL, NULL,
		&dwSysFlags,
		FileSysNameBuf,
		FILESYSNAMEBUFSIZE);

	if (!(dwSysFlags & FILE_SUPPORTS_REPARSE_POINTS)){
		printf("\t This file system does not support volume mount points.\n");
	}
	else{
		//本卷中的挂载点
		hPt = FindFirstVolumeMountPoint(
			Buf,	//卷的路径
			PtBuf,  //挂载点路径
			BUFSIZE);

		if (hPt == INVALID_HANDLE_VALUE){
			printf("\t No volume mount points found!\n");
		}

		else{
			//处理挂载点
			bFlag = ProcessVolumeMountPoint(hPt,
				PtBuf,
				BUFSIZE,
				Buf);

			//循环
			while (bFlag){
				bFlag = ProcessVolumeMountPoint(hPt, PtBuf, BUFSIZE, Buf);
			}

			//结束
			FindVolumeMountPointClose(hPt);
		}
	}
	//下一个
	bFlag = FindNextVolume(hVol, Buf, iBufSize);
	return bFlag;
}


//获取挂载点

int GetMountPoint(void){
	TCHAR buf[BUFSIZE];//卷标识符
	HANDLE hVol;//卷句柄
	BOOL bFlag;//结果标志
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

//使用的说明方法
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
		argv[2],       //输入挂载点或者目录
		Buf,		   //输出卷名
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

