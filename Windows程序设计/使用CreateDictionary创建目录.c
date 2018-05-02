#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	LPSTR szDirPath = "sub_dir";//在当前程序目录下创建文件夹

	if (!CreateDirectory(szDirPath, NULL)){
		return 1;
	}


	//在左面创建目录example_dir
	szDirPath = "C://Users//pc//Desktop//example_dir";
	if (!CreateDirectory(szDirPath, NULL)){
		printf("创建目录%s错误\n", szDirPath);
		return 1;
	}

	printf("成功\n");
	return 0;
}
