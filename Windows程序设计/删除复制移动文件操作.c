#include <windows.h>
#include <stdio.h>


int main(int argc, PCHAR argv[]){
	//删除文件操作
	if (0 == lstrcmp("-d", argv[1]) && argc == 3){
		if (!DeleteFile(argv[2])){
			printf("删除文件错误:%x\n", GetLastError());
		}
		else{
			printf("删除成功!\n");
		}

	}

	else if (0 == lstrcmp("-c", argv[1]) && argc == 4){
		//复制，不覆盖已经存在的文件
		if (!CopyFile(argv[2], argv[3], TRUE)){
			if (GetLastError() == 0x50){//这个错误代号为文件已经存在
				printf("文件%s 已经存在，是否覆盖 y/n:", argv[3]);
				if ('y' == getchar()){
					//复制，覆盖已经存在的文件
					if (!CopyFile(argv[2], argv[3], FALSE)){
						printf("复制文件错误:%d\n", GetLastError());
					}
					else{
						printf("复制成功\n");
					}
				}
				else{
					return 0;
				}
			}
		}
		else{
			printf("复制成功\n");
		}
	}

	// -m参数，移动重命名文件
	else if (0 == lstrcmp("-m", argv[1]) && argc == 4){
		if (!MoveFile(argv[2], argv[3])){
			printf("移动文件错误:%d\n", GetLastError());
		}
		else{
			printf("移动文件成功\n");
		}
	}
	else{
		printf("参数错误\n");
	}

	return 0;
}

