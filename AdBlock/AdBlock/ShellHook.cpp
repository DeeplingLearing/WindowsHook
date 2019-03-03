#include "ShellHook.h"

static void GetCreateWndParamter(HWND hwndNew)
{
	BOOL isVisibe = IsWindowVisible(hwndNew);

	wchar_t className[128] = { 0 }, text[128] = { 0 };
	GetClassNameW(hwndNew, className, sizeof(className));
	GetWindowTextW(hwndNew, text, sizeof(text));
	WINDOWINFO wi;
	GetWindowInfo(hwndNew, &wi);
	WndParamter wp;
	wp._hwnd = hwndNew;
	wp._class = std::wstring(className);
	wp._text = std::wstring(text);
	wp._rect = wi.rcWindow;

	if (ShellHook::_callback)
	{
		ShellHook::_callback(wp);
	}
	std::wostringstream os;
	os << L"新创建的窗口句柄:" << hwndNew << L"\t窗口类名:" << className << L"\t窗口标题:" << text << L"\t可见:" << isVisibe 
	   << L"\t窗口坐标:(" << wi.rcWindow.left << L", " << wi.rcWindow.top << L")" 
	   << L"\t窗口大小:(" << (wi.rcWindow.right - wi.rcWindow.left)<< L", " << (wi.rcWindow.bottom - wi.rcWindow.top) << L")" << L"\n";
	OutputDebugStringW(os.str().c_str());
}

static LRESULT CALLBACK WndProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) 
{
	if (uMsg == WM_SHELLHOOKMESSAGE)
	{
		if (HSHELL_WINDOWCREATED == wParam)
		{
			GetCreateWndParamter((HWND)lParam);
		}
		return 0;
	}
	return DefWindowProc(hwnd, uMsg, wParam, lParam);
}


CreateWndowsCallback ShellHook::_callback = nullptr;

ShellHook::ShellHook()
	: _hwndHook(NULL)
{
}

ShellHook::~ShellHook()
{
	if (_hwndHook)
	{
		UnSetShellHook();
		_hwndHook = NULL;
	}
}

bool ShellHook::SetShellHook(HINSTANCE hInstance)
{
	WNDCLASSEX wc = { 0 };
	wc.cbSize = sizeof(wc);
	wc.hInstance = hInstance;
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = L"shell_wnd_class";

	if (!RegisterClassEx(&wc))
		return false;

	_hwndHook = CreateWindowW(L"shell_wnd_class", L"", WS_POPUP, 0, 0, 0, 0, NULL, NULL, hInstance, NULL);

	if (!_hwndHook)
	{
		OutputDebugStringW(L"创建安装钩子窗口失败!");
		return false;
	}

	WM_SHELLHOOKMESSAGE = RegisterWindowMessage(L"SHELLHOOK");

	return WM_SHELLHOOKMESSAGE && RegisterShellHookWindow(_hwndHook);
}

void ShellHook::UnSetShellHook()
{
	BOOL ret = DeregisterShellHookWindow(_hwndHook);

	OutputDebugStringW(ret ? L"卸载钩子成功!" : L"卸载钩子失败!");
}
