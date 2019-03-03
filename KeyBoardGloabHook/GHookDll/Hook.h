#pragma once
#include <windows.h>

#ifndef DLL_EXPORT_FUNC
#define DLL_EXPORT_FUNC extern "C" __declspec(dllexport)
#endif


LRESULT CALLBACK KeyboardProc(int code, WPARAM wParam, LPARAM lParam);
DLL_EXPORT_FUNC BOOL SetHook();
DLL_EXPORT_FUNC void UnHook();
