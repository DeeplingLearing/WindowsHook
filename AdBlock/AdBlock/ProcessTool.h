#pragma once
#include "common.h"

//进程处理工具类 zeus已经有该方法

class ProcessTool
{
public:
	ProcessTool();
	virtual ~ProcessTool();
public:
	//brief:获取窗口进程Id
	static void GetWindowsProcessId(HWND hwnd);
	//brief:获取进程名
	static void GetProcessName(const DWORD dwPId, std::wstring& processName);
	//brief:获取产品名
	static void GetProductNanme();
	//brief:获取进程图标
	static void GetProcessIcon(const DWORD dwPId, std::wstring& filename);
private:
	//brief:
};

