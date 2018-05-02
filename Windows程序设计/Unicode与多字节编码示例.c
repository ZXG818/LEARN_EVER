#include <windows.h>
#include <stdio.h>

int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow){
	//定义LPWSTR类型的宽字符串
	LPWSTR szUnicode = L"This is a Unicode String";

	//定义LPSTR 类型的窄字符串
	LPSTR szMutliByte = "This is not a Unicode String";

	//定义LPSTR 类型的自适用字符串
	LPSTR szString = TEXT("This string is a Unicode or not depends on the option");

	//使用W版本的API函数，以宽字符串为参数
	MessageBoxW(NULL, szUnicode, L"<字符编码1>", MB_OK);

	//使用A版本的API函数，以窄字符串为参数
	MessageBoxA(NULL, szMutliByte, "<字符编码2>", MB_OK);

	//自动适应的API函数
	MessageBox(NULL, szString, TEXT("<字符编码3>"), MB_OK);
	return 0;
}
