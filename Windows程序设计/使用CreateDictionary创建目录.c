#include <windows.h>
#include <stdio.h>

int main(int argc, char *argv[]){
	LPSTR szDirPath = "sub_dir";//�ڵ�ǰ����Ŀ¼�´����ļ���

	if (!CreateDirectory(szDirPath, NULL)){
		return 1;
	}


	//�����洴��Ŀ¼example_dir
	szDirPath = "C://Users//pc//Desktop//example_dir";
	if (!CreateDirectory(szDirPath, NULL)){
		printf("����Ŀ¼%s����\n", szDirPath);
		return 1;
	}

	printf("�ɹ�\n");
	return 0;
}
