#include <windows.h>
#include <iostream>
#include <thread>

using namespace std;


void GloabKeyboardHook()
{
	HMODULE hDll = LoadLibrary(L"GHookDll");

	if (NULL == hDll)
	{
		cout << "load library fail" << endl;
		return;
	}

	typedef BOOL(*LPSETHOOK)();
	typedef void(*LPUNHOOK)();

	LPSETHOOK SetHook = (LPSETHOOK)GetProcAddress(hDll, "SetHook");
	LPUNHOOK UnHook = (LPUNHOOK)GetProcAddress(hDll, "UnHook");

	if (SetHook == NULL || UnHook == NULL)
	{
		cout << "SetHook or UnHook function fail" << endl;
		return;
	}

	if (!SetHook())
	{
		cout << "set hook fail" << endl;
		return;
	}
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
	thread t(GloabKeyboardHook);

	t.join();
}