#pragma once

#include "common.h"

//��װ���ڹ���
static UINT WM_SHELLHOOKMESSAGE;    //�Զ�����Ϣ

class ShellHook
{
public:
	ShellHook();
	virtual ~ShellHook();
public:
	//��װshellhook����
	bool SetShellHook(HINSTANCE hInstance);
private:
	//ж��shellhook����
	void UnSetShellHook();
public:
	static CreateWndowsCallback _callback;
private:
	HWND _hwndHook; //��Ҫ��װ���ӵĴ���
};

