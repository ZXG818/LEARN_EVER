#include <windows.h>
#include <string.h>
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	PSTR szCmdLine,
	int iCmdShow){


	LPSTR szString = "Windows data type ,string.";
	CHAR lpString[128];
	DWORD dwMax = 0xFFFFFFFF;
	DWORD dwOne = 0x1;

	INT iMax = 0xFFFFFFFF;
	INT iOne = 0x1;

	int nMax = 0xFFFFFFFF;

	MessageBox(NULL, szString, "LPSTR", MB_OK);

	CopyMemory(lpString, szString, lstrlen(szString) + 1);//�����ڴ棬��szString���Ƶ�lpString�У�����NULL������
	//strcpy(lpString, szString);//���������Ҳ����

	MessageBox(NULL, lpString, "CHAR[]", MB_OK);

	if (dwMax > dwOne){
		MessageBox(NULL, "DWORD���͵����� 0xFFFFFFFF > 0xl", "DWORD", MB_OK);
	}

	if (iMax < iOne){
		MessageBox(NULL, "INT���͵����� 0xFFFFFFFF > 0xl", "DWORD", MB_OK);

	}
	if (dwMax == iMax){
		MessageBox(NULL, "GoodNight!", "title", MB_OK);
	}

	if (iMax == nMax){
		MessageBox(NULL, "hahahahah", "sleep", MB_OK);
	}


	return 0;
}
