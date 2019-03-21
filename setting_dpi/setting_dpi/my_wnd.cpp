#include "my_wnd.h"

static LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	return DefWindowProc(hwnd, msg, wParam, lParam);
}

MyWnd::MyWnd(int left, int top, int w, int h, const wstring & title, wstring & className)
	: _left(left)
	, _top(top)
	, _width(w)
	, _height(h)
	, _title(title)
	, _className(className)
	, _hwnd(NULL)
{
}

MyWnd::~MyWnd()
{
	if (_hwnd)
	{
		Close();
	}
}

bool MyWnd::Create(HWND hParent /*= NULL*/)
{
	WNDCLASSEXW wcex = { 0 };

	wcex.cbSize = sizeof(wcex);
	wcex.hInstance = GetModuleHandleW(NULL);
	wcex.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wcex.hCursor = LoadCursorW(NULL, IDC_ARROW);
	wcex.lpfnWndProc = WndProc;
	wcex.lpszClassName = _className.c_str();

	if (!RegisterClassEx(&wcex))
	{
		return false;
	}

	_hwnd = ::CreateWindowW(_className.c_str(), _title.c_str(), WS_POPUP, _left, _top, _width, _height, hParent, NULL, wcex.hInstance, NULL);

	if (!_hwnd)
	{
		return false;
	}

	return true;
}

bool MyWnd::Show()
{
	return ::ShowWindow(_hwnd, SW_NORMAL);
}

bool MyWnd::Close()
{
	return DestroyWindow(_hwnd);
}
