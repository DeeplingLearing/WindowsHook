// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

//#pragma comment(linker, "/export:CallWndProc=CallWndProc")

BOOL APIENTRY DllMain( HMODULE hModule,
                       DWORD  ul_reason_for_call,
                       LPVOID lpReserved
					 )
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


__declspec(dllexport) LRESULT CALLBACK CallWndProc(int code, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"CallWndProc\n");

	DWORD tId = (DWORD)(wParam);
	LPCWPSTRUCT lpcw = (LPCWPSTRUCT)(lParam);

	
	if (lpcw)
	{
		wchar_t buf[1024] = { 0 };

		HWND hwnd = lpcw->hwnd;
		UINT msg = lpcw->message;

		wchar_t className[1024] = { 0 }, titleName[1024] = { 0 };

		GetClassNameW(hwnd, className, 1024);
		GetWindowTextW(hwnd, titleName, 1024);

		wsprintf(buf, L"tId:%d\t hwnd:%d\t message:%d class name:%s\t title name:%s\n", tId, hwnd, msg, className, titleName);

		OutputDebugStringW(buf);
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}


__declspec(dllexport) LRESULT CALLBACK GetMsgProc(int code, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"GetMsgProc\n");

	LPMSG lpMsg = (LPMSG)(lParam);

	if (lpMsg)
	{
		wchar_t buf[1024] = { 0 };
		HWND hwnd = lpMsg->hwnd;
		UINT msg = lpMsg->message;

		wsprintf(buf, L"hwnd:%d\t message:%d\n", hwnd, msg);

		OutputDebugStringW(buf);
	}

	return CallNextHookEx(NULL, code, wParam, lParam);
}

__declspec(dllexport) LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"KeyboardProc\n");

	return CallNextHookEx(NULL, code, wParam, lParam);
}