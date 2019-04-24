// demo.cpp : �������̨Ӧ�ó������ڵ㡣
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

	//��ȡԭʼAPI
	LPMESSAGEBOXW lpMessageBoxW = (LPMESSAGEBOXW)(g_hookItem._pOldFunEntry);

	int ret = lpMessageBoxW(hWnd, L"���Ǳ�HOOK���ĺ���", L"[����]", uType);

	g_hookItem.ReHook();

	return ret;
}

int main()
{
	//ԭʼAPI
	MessageBoxW(NULL, L"����ԭʼAPI����", L"[����1]", MB_OK);

	//hook api
	bool ret = g_hookItem.Hook(L"user32.dll", "MessageBoxW", (FARPROC)NewMessageBoxW);

	//����HOO API
	MessageBoxW(NULL, L"����ԭʼAPI����", L"[����2]", MB_OK);

	g_hookItem.UnHook();

    return 0;
}

