#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
/*
*���ܣ����úͻ�ȡ�ļ����Ե�
*��������ʾ��һ������ָ���ļ������ԣ�ʱ�䣬��С
*		���ڶ�����������������Ϊ���أ�ֻ��
*����ֵ��0����ִ����ɣ�1����������
*/

//��������
DWORD ShowFileAttributes(LPSTR lpParam1);
DWORD SetFileHiddenAndReadonly(LPSTR lpParam2);
DWORD ShowFileTime(PFILETIME lptime);
DWORD ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow);
DWORD ShowFileAttrInfo(DWORD dwAttribute);


int main(int argc, char *argv[]){
	LPSTR lpParam1 = malloc(sizeof(CHAR)*MAX_PATH);		// ��ʼ������ռ�
	LPSTR lpParam2 = malloc(sizeof(CHAR)*MAX_PATH);
	printf("�������һ���ļ�·��:");
	gets(lpParam1);
	printf("������ڶ����ļ�·��:");
	gets(lpParam2);
	printf("��ʾ��һ������ָ���ļ������ԣ�ʱ�䣬��С\n");
	printf("���ڶ�����������������Ϊ���أ�ֻ��\n");

	ShowFileAttributes(lpParam1);
	SetFileHiddenAndReadonly(lpParam2);
	free(lpParam1);
	free(lpParam2);
	return 0;
}


/*
��ȡ����ʾ�ļ����ԣ�����ShowFileTime��ShowFileSize����
ShowFileAttrInfo����

������LPSTR szPath����ȡ����ʾ���ļ�������
����ֵ��0����ִ����ɣ�1����������
*/
DWORD ShowFileAttributes(LPSTR szPath){
	//�ļ����Խṹ
	WIN32_FILE_ATTRIBUTE_DATA wfad;
	printf("�ļ�:%s\n", szPath);

	//��ȡ�ļ�����
	if (!GetFileAttributesEx(szPath,
		GetFileExInfoStandard,
		&wfad)){
		printf("��ȡ�ļ����Դ���:%d\n", GetLastError());
		return 1;
	}

	//��ʾ���ʱ��
	printf("����ʱ��:\t");
	ShowFileTime(&(wfad.ftCreationTime));
	printf("������ʱ��:\t");
	ShowFileTime(&(wfad.ftLastAccessTime));
	printf("����޸�ʱ��:\t");
	ShowFileTime(&(wfad.ftLastWriteTime));

	//��ʾ�ļ���С
	ShowFileSize(wfad.nFileSizeHigh, wfad.nFileSizeLow);
	//��ʾ�ļ�����
	ShowFileAttrInfo(wfad.dwFileAttributes);

	printf("HHHHHHHAAAAAAAAAAAAAAAAAAAA\n");

	return 0;
}

//���ܣ�ת���ļ�ʱ�䲢��ӡ
//������PFILETIME lptime��ָ���ļ�ʱ���ָ��
DWORD ShowFileTime(PFILETIME lptime){
	//�ļ�ʱ��ṹ
	FILETIME ftLocal;
	//ϵͳʱ��ṹ
	SYSTEMTIME st;
	//����Ϊϵͳ����ʱ����ʱ��
	FileTimeToLocalFileTime(lptime, &ftLocal);
	
	//���ļ�ʱ��ת��Ϊϵͳ��ʽ��������ʾ
	FileTimeToSystemTime(&ftLocal, &st);

	//��ʾʱ����Ϣ�ַ���
	printf("%4d��%#02d��%#02d�գ�%#02d:%#02d:%#02d\n", st.wYear, st.wMonth, st.wDay, st.wHour, st.wMinute, st.wSecond);
	return 0;
}


//��ӡ�ļ���С��Ϣ
//������DWORD dwFileSizeHigh,�ļ���С��32λ
//DWORD dwFileSizeLow,�ļ���С��32λ
DWORD ShowFileSize(DWORD dwFileSizeHigh, DWORD dwFileSizeLow){
	ULONGLONG liFileSize;
	liFileSize = dwFileSizeHigh;
	//�ƶ�32λ
	liFileSize <<= sizeof(DWORD) * 8;
	liFileSize += dwFileSizeLow;
	printf("�ļ���С:\t%I64u�ֽ�\n", liFileSize);
	return 0;
}

DWORD ShowFileAttrInfo(DWORD dwAttribute){
	//�����ж����ԣ�����ʾ
	printf("�ļ�����:\t");
	if (dwAttribute&FILE_ATTRIBUTE_ARCHIVE){
		printf("<ARCHIVE>");
	}
	if (dwAttribute&FILE_ATTRIBUTE_COMPRESSED)
		printf("ѹ��");
	if (dwAttribute &FILE_ATTRIBUTE_DIRECTORY)
		printf("Ŀ¼");
	if (dwAttribute&FILE_ATTRIBUTE_ENCRYPTED)
		printf("����");
	if (dwAttribute&FILE_ATTRIBUTE_HIDDEN)
		printf("����");
	if (dwAttribute&FILE_ATTRIBUTE_NORMAL)
		printf("NORMAL");
	if (dwAttribute&FILE_ATTRIBUTE_OFFLINE)
		printf("OFFLINE");
	if (dwAttribute&FILE_ATTRIBUTE_READONLY)
		printf("ֻ��");
	if (dwAttribute&FILE_ATTRIBUTE_SPARSE_FILE)
		printf("SPARSE");
	if (dwAttribute&FILE_ATTRIBUTE_SYSTEM)
		printf("ϵͳ�ļ�");

	if (dwAttribute&FILE_ATTRIBUTE_TEMPORARY)
		printf("��ʱ�ļ�");
	printf("\n");
	return 0;
}


//��ָ�����ļ�����Ϊ���غ�ֻ��
//������LPSTR szFileName,�ļ�·��

DWORD SetFileHiddenAndReadonly(LPSTR szFileName){
	//��ȡԭ���ļ�������
	DWORD dwFileAttributes = GetFileAttributes(szFileName);
	//��ֻ�����������Ը��ӵ�ԭ�����ļ�������
	dwFileAttributes |= FILE_ATTRIBUTE_READONLY;
	dwFileAttributes |= FILE_ATTRIBUTE_HIDDEN;

	//�����ĵ����Բ��ж��Ƿ�ɹ�
	if (SetFileAttributes(szFileName, dwFileAttributes)){
		printf("�ļ�%s\n�����غ��������óɹ�\n", dwFileAttributes);
	}
	else{
		printf("��������;%d\n", GetLastError());
	}

	return 0;
}





