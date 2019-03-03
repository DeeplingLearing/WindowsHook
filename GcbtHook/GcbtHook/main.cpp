#include <windows.h>
#include <iostream>
#include <thread>
#include <functional>
#include <sstream>

using namespace std;

struct CreatWndParamter
{
	HWND _hwnd; //新创建窗口的句柄
	LPCREATESTRUCTA _cs; //新创建窗口的数据
};

typedef std::function<void(const CreatWndParamter& cwp)> Callback;


void GetCreateWndParamter(const CreatWndParamter& cwp)
{
	wstringstream wss;

	wss << L"Hwnd:" << cwp._hwnd << L"\t className:" << cwp._cs->lpszClass << L"\t title:" << cwp._cs->lpszName;
	OutputDebugStringW(wss.str().c_str());
}

void GloabCBTHook()
{
	HMODULE hDll = LoadLibrary(L"GcbtHookDll");

	if (NULL == hDll)
	{
		cout << "load library fail" << endl;
		return;
	}

	typedef BOOL(*LPSETHOOK)();
	typedef void(*LPUNHOOK)();
	typedef void(*LPSETCALLBACK)(const Callback&);

	LPSETHOOK SetHook = (LPSETHOOK)GetProcAddress(hDll, "SetHook");
	LPUNHOOK UnHook = (LPUNHOOK)GetProcAddress(hDll, "UnHook");
	LPSETCALLBACK SetCallback = (LPSETCALLBACK)GetProcAddress(hDll, "SetCallback");

	if (SetHook == NULL || UnHook == NULL || SetCallback == NULL)
	{
		cout << "SetHook or UnHook or SetCallback function fail" << endl;
		return;
	}

	if (!SetHook())
	{
		cout << "set hook fail" << endl;
		return;
	}

	SetCallback(bind(GetCreateWndParamter, placeholders::_1));

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnHook();
}



void main()
{
	thread t(GloabCBTHook);

	t.join();
}