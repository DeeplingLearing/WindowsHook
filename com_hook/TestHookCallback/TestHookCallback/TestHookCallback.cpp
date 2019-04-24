// TestHookCallback.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>

using namespace std;



int main()
{
	HMODULE hDll = LoadLibraryW(L"hook.dll");

	if (NULL == hDll)
	{
		cout << "load library fail." << endl;

		return 1;
	}

	HOOKPROC lpHookFn = (HOOKPROC)GetProcAddress(hDll, "CallWndProc");

	if (NULL == lpHookFn)
	{
		cout << "get call wnd proc fail." << endl;
		return 1;
	}

	HHOOK hook = SetWindowsHookExW(WH_CALLWNDPROC, lpHookFn, hDll, 0);

	if (NULL == hook)
	{
		cout << "set windows hook fail." << endl;
		return 1;
	}

	system("pause");

	UnhookWindowsHookEx(hook);

    return 0;
}

