#include <Windows.h>
#include <sstream>
#include <thread>
#include <iostream>
#include <fstream>
#include <vector>
#include <mutex>

using namespace std;

static UINT WM_SHELLHOOKMESSAGE;    //自定义消息


struct CreateWndParamter
{
	HWND _hwnd;
	wstring _class;
	wstring _title;
	bool _isVisible;
};

vector<CreateWndParamter> g_vec;
mutex g_vecMutex;

BOOL SetShellHook(HWND hwndHook)    //需要安装钩子的窗口句柄
{
	WM_SHELLHOOKMESSAGE = RegisterWindowMessage(L"SHELLHOOK");
	return WM_SHELLHOOKMESSAGE && RegisterShellHookWindow(hwndHook);
}

BOOL UnSetShellHook(HWND hwndHook)  //卸载钩子
{
	return DeregisterShellHookWindow(hwndHook);
}

static void GetCreateWndParamter(HWND hwndNew)
{
	BOOL isVisibe = IsWindowVisible(hwndNew);

	wchar_t szCls[128] = { 0 }, szText[128] = { 0 };
	GetWindowTextW(hwndNew, szText, sizeof(szText));
	GetClassNameW(hwndNew, szCls, sizeof(szCls));

	wostringstream os;
	os << L"新创建的窗口句柄:" << hwndNew << L"\t\t 窗口类名:" << szCls << L"\t\t 窗口标题:" << szText << L"\t\t 可见:" << isVisibe << L"\n";
	OutputDebugStringW(os.str().c_str());
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
	if (uMsg == WM_SHELLHOOKMESSAGE) 
	{
			if (HSHELL_WINDOWCREATED == wParam)
			{
				GetCreateWndParamter((HWND)lParam);
			}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


void MonitorCreateWndTask(HINSTANCE hInstance)
{
	HWND hWnd;
	MSG msg;
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"shell_wnd_class";

	if (!RegisterClassEx(&wc))
		return;

	hWnd = CreateWindowW(L"shell_wnd_class", L"Shell Hook Demo", WS_POPUP,
		0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	if (!hWnd) 
	{
		return;
	}

	if (!SetShellHook(hWnd))
	{
		return;
	}

	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnSetShellHook(hWnd);
}


void main()
{
	HINSTANCE hInstance = GetModuleHandleW(NULL);
	thread task(MonitorCreateWndTask, hInstance);

	task.join();

	//while (true)
	//{
	//	vector<CreateWndParamter> vec;
	//	{
	//		lock_guard<mutex> lock(g_vecMutex);
	//		vec = g_vec;
	//		g_vec.clear();
	//	}

	//	for (auto wnd : vec)
	//	{
	//		
	//		wcout << "窗口类名:" << wnd._class << endl;
	//		wcout << "窗口标题:" << endl;
	//		wcout << wnd._title << endl;
	//		wcout << "可见:" << wnd._isVisible << endl;
	//	}
	//	//output.flush();
	//	this_thread::sleep_for(chrono::seconds(5));
	//}

	
}

