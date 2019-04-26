// dllmain.cpp : 定义 DLL 应用程序的入口点。
#include "stdafx.h"

#define UM_CALLWNDPROC WM_USER + 110 //自定义消息

#pragma data_seg("MySection")
DWORD g_threadId = 0; //共享启动钩子的线程ID 只能由启动线程设置 其他进程向该线程发送消息.
#pragma data_seg()

#pragma comment(linker, "/SECTION:MySection,RWS") //设置共享数据段可读可写.

BOOL APIENTRY DllMain(HMODULE hModule,
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

__declspec(dllexport) void __stdcall SetThreadId(DWORD tID)
{
    g_threadId = tID;
}

__declspec(dllexport) LRESULT CALLBACK CallWndProc(int code, WPARAM wParam, LPARAM lParam)
{
    DWORD tId = (DWORD)(wParam);
    LPCWPSTRUCT lpcw = (LPCWPSTRUCT)(lParam);

    if (lpcw)
    {
        HWND hwnd = lpcw->hwnd;
        UINT msg = lpcw->message;
        if (WM_SHOWWINDOW == msg || WM_CLOSE == msg || WM_ACTIVATE == msg)
        {
            wchar_t buf[1024] = { 0 };
            wsprintfW(buf, L"threadID:%d\t hwnd:%d\n", g_threadId, hwnd);
            OutputDebugStringW(buf);
            PostThreadMessageW(g_threadId, UM_CALLWNDPROC, wParam, (WPARAM)(hwnd));
            OutputDebugStringW(L"PostThreadMessageW end\n");
        }
    }

    return CallNextHookEx(NULL, code, wParam, lParam);
}
