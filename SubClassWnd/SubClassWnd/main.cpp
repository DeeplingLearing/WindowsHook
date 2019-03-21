#include <windows.h>


//窗口子类化 只能在一个进程内进行替换

LRESULT CALLBACK SubClassWndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CLOSE:
	{
		MessageBox(NULL, L"tip", L"close", 0);
		break;
	}
	case WM_DESTROY:
	{
		MessageBox(nullptr, L"tip", L"destroy", 0);
		break;
	}
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}



void main()
{
	HWND hwnd = FindWindowW(L"{94104BD8-0C5F-49b8-8C0C-951E4AA7EF66}", L"");

	if (NULL == hwnd)
	{
		return;
	}

	//获取该窗口的窗口过程
	SetWindowLongPtrW(hwnd, GWL_WNDPROC, (LONG)SubClassWndProc);


	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return;
}