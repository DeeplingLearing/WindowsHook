// demo.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "hook_api.h"
#pragma comment(lib, "hook_api.lib")

#include <windows.h>


HookApi g_hookItem;

typedef int (WINAPI* LPMESSAGEBOXW)(HWND, LPCWSTR, LPCWSTR, UINT);


int WINAPI NewMessageBoxW(HWND hWnd, LPCWSTR lpText, LPCWSTR lpCaption, UINT uType)
{
	g_hookItem.UnHook();

	//获取原始API
	LPMESSAGEBOXW lpMessageBoxW = (LPMESSAGEBOXW)(g_hookItem._pOldFunEntry);

	int ret = lpMessageBoxW(hWnd, L"这是被HOOK过的函数", L"[测试]", uType);

	g_hookItem.ReHook();

	return ret;
}

int main()
{
	//原始API
	MessageBoxW(NULL, L"这是原始API函数", L"[测试1]", MB_OK);

	//hook api
	bool ret = g_hookItem.Hook(L"user32.dll", "MessageBoxW", (FARPROC)NewMessageBoxW);

	//测试HOO API
	MessageBoxW(NULL, L"这是原始API函数", L"[测试2]", MB_OK);

	g_hookItem.UnHook();

    return 0;
}

