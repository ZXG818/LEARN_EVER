#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow){
	//����LPWSTR���͵Ŀ��ַ���
	LPWSTR szUnicode = L"This is a Unicode String";

	//����LPSTR ���͵�խ�ַ���
	LPSTR szMutliByte = "This is not a Unicode String";

	//����LPSTR ���͵��������ַ���
	LPSTR szString = TEXT("This string is a Unicode or not depends on the option");

	//ʹ��W�汾��API�������Կ��ַ���Ϊ����
	MessageBoxW(NULL, szUnicode, L"<�ַ�����1>", MB_OK);

	//ʹ��A�汾��API��������խ�ַ���Ϊ����
	MessageBoxA(NULL, szMutliByte, "<�ַ�����2>", MB_OK);

	//�Զ���Ӧ��API����
	MessageBox(NULL, szString, TEXT("<�ַ�����3>"), MB_OK);
	return 0;
}
