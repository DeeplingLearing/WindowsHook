#pragma once
#include "common.h"

class EnumAdWindowsTool
{
public:
	EnumAdWindowsTool();
	virtual ~EnumAdWindowsTool();
public:
	//brief:设置枚举窗口回调函数
	static void SetCallback(const EnumTopLevelWindowsCallback& callback);
	//brief:枚举桌面上所有顶级窗口
	static void EnumTopLevelWindows();
	//brief:通过窗口句柄获取窗口数据
	static WndParamter GetWindowParamter(HWND hwnd);
	//brief:截取窗口在桌面上的位置
	static bool CaputureWindows(HWND hwnd, std::wstring filename);
	//brief:关闭指定窗口
	//note: 存在窗口会屏蔽WM_CLOSE消息，但是只要窗口真正关闭，一定会走WM_DESTORY消息
	static void CloseWindows(HWND hwnd);

	//brief:窗口枚举回调函数
	static EnumTopLevelWindowsCallback _callback;
};

