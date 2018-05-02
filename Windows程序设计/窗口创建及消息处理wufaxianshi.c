#include <windows.h>

HINSTANCE hinst;//ȫ�ֱ���

//��������
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//���ܣ���ʾһ������
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow){
	WNDCLASSEX wcx;//������
	HWND hwnd; //���ھ��
	MSG msg;//��Ϣ
	BOOL fGotMessage;//�Ƿ�ɹ���ȡ��Ϣ
	hinst = hInstance;//Ӧ�ó���ʵ�����������Ϊȫ�ֱ���

	wcx.cbSize = sizeof(wcx);//�ṹ���С
	wcx.style = CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = MainWndProc;//��Ϣ������
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;//����Ӧ�ó���ʵ�����
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = "MainClass";


	//Сͼ��
	wcx.hIconSm = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	//ע�ᴰ����
	if (!RegisterClassEx(&wcx)){
		MessageBox(NULL, "�������Ҫ��WindowsNTƽ̨�²�������", "����", MB_OKCANCEL | MB_ICONEXCLAMATION);
		return 1;
	}

	//��������
	hwnd = CreateWindow(
		"MainWClass",//������
		"CH 2-3",//���ڱ���
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		CW_USEDEFAULT,
		NULL,
		NULL,
		hInstance,
		NULL);

	if (!hwnd){
		return 1;
	}

	//��ʾ����
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//��Ϣѭ��
	while ((fGotMessage = GetMessage(&msg, NULL, 0, 0)) != 0 && fGotMessage != -1){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}


//MainWndProc������Ϣ������
//��������Ϣ������Ĭ�ϴ�����
LRESULT CALLBACK MainWndProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam){
	switch (uMsg){
	case WM_DESTROY:
		ExitThread(0);//��ֹ�߳�
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
