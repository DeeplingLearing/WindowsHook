#include <windows.h>
#include <iostream>
#include <string>
#include <thread>

using namespace std;

HHOOK g_hook = NULL;


//ʹ�ÿ���̨�̴߳����ֲ�WH_KEBOARD �� WH_MOUSE �󣬲��񲻵���Ӧ����Ϣ ��������Ϊ���߳�û�д�������
//���ǿ�������WH_KEBOARD_LL �� WH_MOUSE_LL ����ȫ�ֵ���Ϣ��
LRESULT CALLBACK KeyboardProC(int nCode, WPARAM wParam, LPARAM lParam)
{
	if (nCode < 0)
	{
		return CallNextHookEx(g_hook, nCode, wParam, lParam);
	}

	//hook �س�������Ϣ
	if (wParam & VK_RETURN)
	{
		MessageBoxW(NULL, L"Hook �س���", L"�ڸý��̷�Χ�ڰ��»س���", MB_OK);
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
		MessageBoxW(NULL, L"Hook ������", L"������������", MB_OK);
		return 1;
	}
	return CallNextHookEx(g_hook, nCode, wParam, lParam);
}


void SetKeyBoardHook()
{
	HINSTANCE hInst = GetModuleHandleW(NULL);

	g_hook = SetWindowsHookExW(WH_KEYBOARD, KeyboardProC, hInst, GetCurrentThreadId()); //��װ�����ڼ��̹���

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
	//g_hook = SetWindowsHookExW(WH_MOUSE_LL, MouseProc, NULL, 0/*GetCurrentThreadId()*/); //��װ�����ڼ��̹���

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