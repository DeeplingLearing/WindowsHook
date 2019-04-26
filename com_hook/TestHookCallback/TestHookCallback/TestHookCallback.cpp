// TestHookCallback.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
#include <functional>
//#include "hook.h"
//
//#pragma comment(lib, "hook.lib")
using namespace std;

static void PrintWindowInfo(DWORD iscurrentThread, HWND hwnd)
{
    //判断下是否为子窗口 还是拥有者窗口
    DWORD dwStyle = GetWindowLongPtrW(hwnd, GWL_STYLE);
    wchar_t buf[1024] = { 0 };
    if (WS_CHILD & dwStyle || WS_CHILDWINDOW & dwStyle)
    {
        wsprintfW(buf, L"is current thread:%d\t window is child.\n", iscurrentThread);
        OutputDebugStringW(buf);
        return;
    }

    if (WS_VISIBLE & dwStyle)
    {
        wsprintfW(buf, L"is current thread:%d\t window is not visible.\n", iscurrentThread);
        OutputDebugStringW(buf);
        return;
    }

    RECT rect;
    GetWindowRect(hwnd, &rect);

    wchar_t className[1024] = { 0 }, titleName[1024] = { 0 };
    DWORD dwPid = 0;
    DWORD dwTid = GetWindowThreadProcessId(hwnd, &dwPid);

    GetClassNameW(hwnd, className, 1024);
    GetWindowTextW(hwnd, titleName, 1024);
    wsprintf(buf, L"is current thread%d\t pId:%d\t tId:%d\t hwnd:%d\t class name:%s\t title name:%s\t rect:(%d, %d, %d, %d)\n",
             iscurrentThread, dwPid, dwTid, hwnd, className, titleName, rect.left, rect.top, rect.right, rect.bottom);

    OutputDebugStringW(buf);
}

#define UM_CALLWNDPROC WM_USER + 110 //自定义消息

static LRESULT CALLBACK WndProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    return DefWindowProc(hwnd, message, wParam, lParam);
}

int main()
{
    WNDCLASSEXW wcex = { 0 };
    wcex.cbSize = sizeof(wcex);

    wcex.hInstance = GetModuleHandleW(NULL);
    wcex.lpfnWndProc = WndProc;
    wcex.lpszClassName = L"message";

    if (!RegisterClassExW(&wcex))
    {
        cout << "register class fail. error:" << GetLastError() << endl;
        return 1;
    }

    HWND hwnd = CreateWindowW(L"message", NULL, 0, 0, 0, 0, 0, HWND_MESSAGE, NULL, wcex.hInstance, NULL);
    if (NULL == hwnd)
    {
        cout << "create window fail. error:" << GetLastError() << endl;
    }

    HMODULE hDll = LoadLibraryW(L"hook.dll");
    if (NULL == hDll)
    {
        cout << "get dll module fail." << endl;

        return 1;
    }

    DWORD dwTID = GetWindowThreadProcessId(hwnd, NULL);
    typedef void(__stdcall * LPSETTHREADID)(DWORD);
    LPSETTHREADID lpSetThreadId = (LPSETTHREADID)GetProcAddress(hDll, "SetThreadId");
    if (NULL == lpSetThreadId)
    {
        cout << "get call wnd proc fail." << endl;

        return 1;
    }

    lpSetThreadId(dwTID);
    //SetThreadId(dwTID);

    HOOKPROC lpHookFn1 = (HOOKPROC)GetProcAddress(hDll, "CallWndProc");

    if (NULL == lpHookFn1)
    {
        cout << "get call wnd proc fail." << endl;
        return 1;
    }

    HHOOK hook1 = SetWindowsHookExW(WH_CALLWNDPROC, lpHookFn1, hDll, 0);
    if (NULL == hook1)
    {
        cout << "set windows hook fail." << endl;
        return 1;
    }

    DWORD dwCurrentThreadId = GetCurrentThreadId();

    MSG msg;
    while (GetMessage(&msg, 0, 0, 0))
    {
        if (UM_CALLWNDPROC == msg.message) //接收非窗口进程POST的消息 这里hwnd 为空.
        {
            DWORD tId = (DWORD)(msg.wParam);
            HWND hwnd = (HWND)(msg.lParam);
            PrintWindowInfo(tId, hwnd);
        }
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    UnhookWindowsHookEx(hook1);

    return 0;
}
