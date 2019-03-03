#include "EnumAdWindowsTool.h"



EnumTopLevelWindowsCallback EnumAdWindowsTool::_callback = nullptr; //初始化静态成员变量

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (!IsWindowVisible(hwnd))
	{
		OutputDebugStringW(L"EnumWindowsProc: windows is not visible!\n");
		return TRUE; //继续枚举
	}

	WndParamter wp = EnumAdWindowsTool::GetWindowParamter(hwnd);

	std::wostringstream os;
	os << L"新创建的窗口句柄:" << wp._hwnd << L"\t窗口类名:" << wp._class << L"\t窗口标题:" << wp._text << L"\t可见:"<< L"\t窗口坐标:(" << wp._rect.left 
	   << L", " << wp._rect.top << L")" << L"\t窗口大小:(" << (wp._rect.right - wp._rect.left) << L", " << (wp._rect.bottom - wp._rect.top) << L")" << L"\n";

	if (wp._class.empty() && wp._text.empty())
	{
		std::wstring str = L"classname and text both are empty!\t";
		str += os.str();
		OutputDebugStringW(str.c_str());
		return TRUE;
	}
	
	//计算顶级窗口在桌面的位置
	int width = wp._rect.right - wp._rect.left;
	int height = wp._rect.bottom - wp._rect.top;

	if (width <= 0 || height <= 0)
	{
		//窗口宽高有个一为0 在桌面上看不见的 可以过滤掉
		std::wstring str = L"窗口宽或高为零!\t";
		str += os.str();
		OutputDebugStringW(str.c_str());
		return TRUE;
	}

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	if (wp._rect.right <= 0 || wp._rect.left > cx || wp._rect.bottom <= 0 || wp._rect.top >= cy)
	{
		//窗口不在桌面范围内 过滤掉
		std::wstring str = L"窗口不在桌面范围内!\t";
		str += os.str();
		OutputDebugStringW(str.c_str());
		return TRUE;
	}

	if (EnumAdWindowsTool::_callback)
	{
		EnumAdWindowsTool::_callback(wp);
	}

	return TRUE;
}

EnumAdWindowsTool::EnumAdWindowsTool()
{
}


EnumAdWindowsTool::~EnumAdWindowsTool()
{
}

void EnumAdWindowsTool::SetCallback(const EnumTopLevelWindowsCallback & callback)
{
	assert(callback);

	_callback = callback;
}

void EnumAdWindowsTool::EnumTopLevelWindows()
{
	EnumWindows(EnumWindowsProc, NULL);
}

WndParamter EnumAdWindowsTool::GetWindowParamter(HWND hwnd)
{
	WndParamter wp;
	wp._hwnd = hwnd;
	wchar_t szClass[1024] = { 0 }, szText[1024] = { 0 };
	GetClassNameW(hwnd, szClass, 1024);
	GetWindowTextW(hwnd, szText, 1024);
	wp._class = std::wstring(szClass);
	wp._text = std::wstring(szText);
	WINDOWINFO wi;
	GetWindowInfo(hwnd, &wi);
	wp._rect = wi.rcWindow;

	return wp;
}

bool EnumAdWindowsTool::CaputureWindows(HWND hwnd, std::wstring filename)
{
	return false;
}

void EnumAdWindowsTool::CloseWindows(HWND hwnd)
{
}
