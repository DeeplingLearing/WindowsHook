#include "hook_call_wnd_proc.h"



WINAPIEXPORT bool SetHook(const Callback & callback)
{
	HINSTANCE hMode = GetModuleHandleW(L"HookCallWndProc.dll");

	g_hhk = SetWindowsHookExW(WH_CALLWNDPROC, CallWndProc, hMode, 0);

	if (NULL != g_hhk)
	{
		g_callback = callback;
	}

	return NULL != g_hhk;
}

WINAPIEXPORT bool UnHook()
{
	BOOL ret = FALSE;
	if (NULL != g_hhk)
	{
		ret = UnhookWindowsHookEx(g_hhk);

		g_hhk = NULL;
	}
	return NULL != ret;
}

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	LPCREATESTRUCT lpcw = reinterpret_cast<LPCREATESTRUCT>(lParam);

	if (lpcw && g_callback)
	{
		g_callback(lpcw);
	}

	return CallNextHookEx(g_hhk, nCode, wParam, lParam);
}
