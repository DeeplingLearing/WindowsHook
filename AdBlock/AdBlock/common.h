#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <functional>
#include <cassert>

//GDI+
#include <GdiPlus.h> 
#pragma comment(lib, "gdiplus.lib")

//窗口参数
struct WndParamter
{
	HWND _hwnd; //窗口句柄
	std::wstring _class; //窗口类
	std::wstring _text; //窗口标题
	RECT _rect;//窗口在桌面上的位置
};
//进程参数
struct ProcessInfo
{
	DWORD _dwPId; //窗口的进程Id;(窗口是由窗口线程创建的，一个窗口应用至少有一个窗口线程)
	std::wstring _processName; //进程名
	std::wstring _moudlePath; //进程可执行文件路径
	std::wstring _producteName;//产品名
};
typedef std::function<void(const WndParamter&)> EnumTopLevelWindowsCallback;
typedef std::function<void(const WndParamter&)> CreateWndowsCallback;