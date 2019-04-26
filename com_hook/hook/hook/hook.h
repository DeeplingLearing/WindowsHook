#pragma once
#include <Windows.h>
#include <string>

__declspec(dllexport) void __stdcall SetThreadId(DWORD tID);

__declspec(dllexport) LRESULT CALLBACK CallWndProc(int code, WPARAM wParam, LPARAM lParam);
