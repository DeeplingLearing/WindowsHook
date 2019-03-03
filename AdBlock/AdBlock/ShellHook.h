#pragma once

#include "common.h"

//安装窗口钩子
static UINT WM_SHELLHOOKMESSAGE;    //自定义消息

class ShellHook
{
public:
	ShellHook();
	virtual ~ShellHook();
public:
	//安装shellhook钩子
	bool SetShellHook(HINSTANCE hInstance);
private:
	//卸载shellhook钩子
	void UnSetShellHook();
public:
	static CreateWndowsCallback _callback;
private:
	HWND _hwndHook; //需要安装钩子的窗口
};

