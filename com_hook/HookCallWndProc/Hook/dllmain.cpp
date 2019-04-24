// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

HHOOK g_hhk;

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

extern "C" __declspec(dllexport) LRESULT CALLBACK CallWndProHook(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPCWPRETSTRUCT lpcw = reinterpret_cast<LPCWPRETSTRUCT>(lParam);

	if (lpcw)
	{
		OutputDebugStringW(L"CallWndProHook\n");
		if (lpcw->message == WM_CREATE)
		{
			HWND hwnd = lpcw->hwnd;
			wchar_t buf[1024] = { 0 };

			wsprintfW(buf, L"hwnd:%d\t message:%d\n", hwnd, lpcw->message);

			OutputDebugStringW(buf);
		}
	}

	return CallNextHookEx(g_hhk, nCode, wParam, lParam);
}