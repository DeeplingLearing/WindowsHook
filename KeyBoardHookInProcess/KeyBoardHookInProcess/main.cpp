#include <windows.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

HHOOK g_hook = NULL;


//使用控制台线程创建局部WH_KEBOARD 和 WH_MOUSE 后，捕获不到对应的消息 可能是因为该线程没有创建窗口
//但是可以设置WH_KEBOARD_LL 和 WH_MOUSE_LL 捕获全局的消息。
LRESULT CALLBACK KeyboardProC(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hook, nCode, wParam, lParam);
	}

	//hook 回车按键消息
	if (wParam & VK_RETURN)
	{
		MessageBoxW(NULL, L"Hook 回车键", L"在该进程范围内按下回车键", MB_OK);
		return 1;
	}

	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}

LRESULT CALLBACK MouseProc(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hook, nCode, wParam, lParam);
	}

	if (wParam & VK_LBUTTON)
	{
		MessageBoxW(NULL, L"Hook 鼠标左键", L"鼠标左键被按下", MB_OK);
		return 1;
	}
	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}


void SetKeyBoardHook()
{
	HINSTANCE hInst = GetModuleHandleW(NULL);

	g_hook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProC, hInst, GetCurrentThreadId()); //安装进程内键盘钩子

	if (NULL == g_hook)
	{
		cout << "set windows hook fail" << endl;
		return ;
	}

	MSG msg;

	while (GetMessageW(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	UnhookWindowsHookEx(g_hook);
}



void main()
{
	thread t(SetKeyBoardHook);

	t.detach();


	while (true)
	{
		string str;
		cout << "enter:";
		cin >> str;

		this_thread::sleep_for(chrono::seconds(10));
	}
	//g_hook = SetWindowsHookExW(WH_MOUSE_LL, MouseProc, NULL, 0/*GetCurrentThreadId()*/); //安装进程内键盘钩子

	//if (NULL == g_hook)
	//{
	//	cout << "set windows hook fail" << endl;
	//	return;
	//}

	//MSG msg;

	//while (GetMessageW(&msg, NULL, 0, 0))
	//{
	//	TranslateMessage(&msg);
	//	DispatchMessage(&msg);
	//}

	//UnhookWindowsHookEx(g_hook);

	return;
}