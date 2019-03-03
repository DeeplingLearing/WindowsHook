#include "Hook.h"


HHOOK g_hook = NULL;

LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam)
{
	if (code >= 0)
	{
		if (wParam & VK_RETURN)
		{
			MessageBox(NULL, L"VK_RETURN", L"VK_RETURN", MB_OK);

			return TRUE;
		}
	}

	return CallNextHookEx(g_hook, code, wParam, lParam);
}

BOOL SetHook()
{
	g_hook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProc, GetModuleHandleW(L"GHookDll"), 0);

	if(NULL == g_hook)
	{
		return FALSE;
	}

	return  TRUE;
}

void UnHook()
{
	UnhookWindowsHookEx(g_hook);
	g_hook = NULL;
}
