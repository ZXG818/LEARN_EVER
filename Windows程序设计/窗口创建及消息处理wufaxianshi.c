#include <windows.h>

HINSTANCE hinst;//全局变量

//函数声明
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int);
LRESULT CALLBACK MainWndProc(HWND, UINT, WPARAM, LPARAM);

//功能：显示一个窗口
int WINAPI WinMain(
	HINSTANCE hInstance,
	HINSTANCE hPrevInstance,
	LPSTR lpCmdLine,
	int nCmdShow){
	WNDCLASSEX wcx;//窗口类
	HWND hwnd; //窗口句柄
	MSG msg;//消息
	BOOL fGotMessage;//是否成功获取消息
	hinst = hInstance;//应用程序实例句柄，保存为全局变量

	wcx.cbSize = sizeof(wcx);//结构体大小
	wcx.style = CS_VREDRAW | CS_HREDRAW;
	wcx.lpfnWndProc = MainWndProc;//消息处理函数
	wcx.cbClsExtra = 0;
	wcx.cbWndExtra = 0;
	wcx.hInstance = hInstance;//所属应用程序实例句柄
	wcx.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wcx.hCursor = LoadCursor(NULL, IDC_ARROW);
	wcx.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcx.lpszMenuName = NULL;
	wcx.lpszClassName = "MainClass";


	//小图标
	wcx.hIconSm = (HICON)LoadImage(hInstance,
		MAKEINTRESOURCE(5),
		IMAGE_ICON,
		GetSystemMetrics(SM_CXSMICON),
		GetSystemMetrics(SM_CYSMICON),
		LR_DEFAULTCOLOR);

	//注册窗口类
	if (!RegisterClassEx(&wcx)){
		MessageBox(NULL, "这个程序要再WindowsNT平台下才能运行", "警告", MB_OKCANCEL | MB_ICONEXCLAMATION);
		return 1;
	}

	//创建窗口
	hwnd = CreateWindow(
		"MainWClass",//窗口名
		"CH 2-3",//窗口标题
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

	//显示窗口
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);

	//消息循环
	while ((fGotMessage = GetMessage(&msg, NULL, 0, 0)) != 0 && fGotMessage != -1){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return msg.wParam;

}


//MainWndProc窗口消息处理函数
//对所有消息都是用默认处理函数
LRESULT CALLBACK MainWndProc(HWND hwnd,
	UINT uMsg,
	WPARAM wParam,
	LPARAM lParam){
	switch (uMsg){
	case WM_DESTROY:
		ExitThread(0);//终止线程
		return 0;
	default:
		return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}
