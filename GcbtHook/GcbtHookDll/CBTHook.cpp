#include "CBTHook.h"
#include <sstream>



HHOOK g_hook = NULL;
Callback g_callback = nullptr;

LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	OutputDebugStringW(L"WH_CALLWNDPROCRET\n");
	if (nCode >= 0)
	{
		if (nCode == HSHELL_WINDOWCREATED)
		{
			HWND hwnd = (HWND)(lParam);
			std::wostringstream os;
			os << L"Hwnd:" << hwnd << L"\n";
			OutputDebugStringW(os.str().c_str());
			return 0;  //这里要返回0,否则会导致创建的窗口返回NULL;
		}
	}

	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}



BOOL SetHook()
{
	g_hook = SetWindowsHookExW(WH_SHELL, ShellProc, GetModuleHandleW(L"GcbtHookDll"), 0); //全局CBT钩子

	DWORD dwError = GetLastError();

	std::wstringstream wss;
	wss << L"SetWindowsHookExW nError: " << dwError;

	OutputDebugStringW(wss.str().c_str());

	return g_hook != NULL ? TRUE : FALSE;
}

void UnHook()
{
	BOOL ret = UnhookWindowsHookEx(g_hook);

	std::wstringstream wss;
	wss << L"UnhookWindowsHookEx ret: " << ret;

	OutputDebugStringW(wss.str().c_str());
}

void SetCallback(const Callback& callback)
{
	g_callback = callback;
}