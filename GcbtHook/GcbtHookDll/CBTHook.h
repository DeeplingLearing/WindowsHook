#pragma once

#ifndef DLL_EXPORT_FUNC
#define DLL_EXPORT_FUNC extern "C" __declspec(dllexport)
#endif


#include <windows.h>
#include <functional>

struct CreatWndParamter
{
	HWND _hwnd; //�´������ڵľ��
	LPCREATESTRUCTA _cs; //�´������ڵ�����
};

typedef std::function<void(const CreatWndParamter& cwp)> Callback;

LRESULT CALLBACK ShellProc(int nCode, WPARAM wParam, LPARAM lParam);
DLL_EXPORT_FUNC BOOL SetHook();
DLL_EXPORT_FUNC void UnHook();

DLL_EXPORT_FUNC void SetCallback(const Callback& callback);



