#include <windows.h>
#include <stdio.h>


int main(int argc, PCHAR argv[]){
	//ɾ���ļ�����
	if (0 == lstrcmp("-d", argv[1]) && argc == 3){
		if (!DeleteFile(argv[2])){
			printf("ɾ���ļ�����:%x\n", GetLastError());
		}
		else{
			printf("ɾ���ɹ�!\n");
		}

	}

	else if (0 == lstrcmp("-c", argv[1]) && argc == 4){
		//���ƣ��������Ѿ����ڵ��ļ�
		if (!CopyFile(argv[2], argv[3], TRUE)){
			if (GetLastError() == 0x50){//����������Ϊ�ļ��Ѿ�����
				printf("�ļ�%s �Ѿ����ڣ��Ƿ񸲸� y/n:", argv[3]);
				if ('y' == getchar()){
					//���ƣ������Ѿ����ڵ��ļ�
					if (!CopyFile(argv[2], argv[3], FALSE)){
						printf("�����ļ�����:%d\n", GetLastError());
					}
					else{
						printf("���Ƴɹ�\n");
					}
				}
				else{
					return 0;
				}
			}
		}
		else{
			printf("���Ƴɹ�\n");
		}
	}

	// -m�������ƶ��������ļ�
	else if (0 == lstrcmp("-m", argv[1]) && argc == 4){
		if (!MoveFile(argv[2], argv[3])){
			printf("�ƶ��ļ�����:%d\n", GetLastError());
		}
		else{
			printf("�ƶ��ļ��ɹ�\n");
		}
	}
	else{
		printf("��������\n");
	}

	return 0;
}

