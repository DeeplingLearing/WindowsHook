#pragma once


#define WINAPIEXPORT __declspec(dllexport)

#include <Windows.h>
#include <functional>
typedef std::function<void(LPCREATESTRUCT)> Callback;

extern HHOOK g_hhk = NULL;
extern Callback g_callback = nullptr;

WINAPIEXPORT bool SetHook(const Callback& callback);
WINAPIEXPORT bool UnHook();

LRESULT CALLBACK CallWndProc(int nCode, WPARAM wParam, LPARAM lParam);