#include <Windows.h>
#include <iostream>

using namespace std;

enum Awareness
{
	Aware_Unknown = -1,
	Aware_AccessDenied = -2,
	Process_DPI_Unaware = 0,
	Process_System_DPI_Aware = 1,
	Process_Per_Monitor_DPI_Aware = 2,
};

typedef HRESULT(WINAPI* GetProcessDPIAwareness_t)(HANDLE hprocess, Awareness *value);


//检测进程DPI类型
//参考资料：https://docs.microsoft.com/zh-cn/windows/desktop/hidpi/high-dpi-desktop-application-development-on-windows

void main()
{
	HMODULE hdll = LoadLibraryW(L"SHCore.dll");

	GetProcessDPIAwareness_t getProcessDPIAwareness = hdll ? (GetProcessDPIAwareness_t)GetProcAddress(hdll, "GetProcessDpiAwareness") : NULL;

	if (getProcessDPIAwareness)
	{
		HWND hwnd = FindWindowW(L"WeChatLoginWndForPC", L"登录");

		if (hwnd)
		{
			DWORD pId = 0;
			GetWindowThreadProcessId(hwnd, &pId);

			HANDLE h = OpenProcess(PROCESS_QUERY_INFORMATION, FALSE, pId);
			if (h && (h != INVALID_HANDLE_VALUE))
			{
				Awareness awareness;
				HRESULT ret = getProcessDPIAwareness(h, &awareness);
				if (FAILED(ret))
				{
					awareness = Aware_AccessDenied;
				}	
				CloseHandle(h);

				cout << "pID:" << pId << "awareness:" << awareness << endl;
			}
		}
	}
	else
	{
		cout << "get process dpi awareness." << endl;
	}

	system("pause");
}