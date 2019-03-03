#include "AdModel.h"


AdModel::AdModel()
	: _state(MonitorState::STOP)
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);
}


AdModel::~AdModel()
{
	if (_adMonitor.joinable())
	{
		_adMonitor.join();
	}

	Gdiplus::GdiplusShutdown(_gdiplusToken);
}

void AdModel::Start()
{
	//���غڰ�����
	//LoadBlackAndWhiteList();
	//�������������ǰ�Ĺ�洰��
	ClearAdWindows();

	//�������洰�ڼ�����
	HINSTANCE hInstance = GetModuleHandleW(NULL);
	_adMonitor = std::thread(std::bind(&AdModel::SetupAdMonitor, this, hInstance));
}

void AdModel::SetAdMonitorState(const MonitorState & state)
{
	std::lock_guard<std::mutex> lock(_stateMutex);
	_state = state;
}

void AdModel::ClearAdWindows()
{
	//ö��EnumWindowsΪ��������
	EnumAdWindowsTool::SetCallback(std::bind(&AdModel::EnumTopLevelWindows, this, std::placeholders::_1));
	EnumAdWindowsTool::EnumTopLevelWindows();
}

void AdModel::HandleWindows(const WndParamter & wp)
{
	//1���Ƿ��ڰ�������

	//2���Ƿ��ں�������

	//3���жϴ����Ƿ�Ϊ���ɴ���
}

void AdModel::GetCreateWindowsParamter(const WndParamter & wp)
{
	//�жϴ����Ƿ���Ҫ����
	HandleWindows(wp);

}

void AdModel::EnumTopLevelWindows(const WndParamter & wp)
{
	//�жϴ����Ƿ���Ҫ����
	HandleWindows(wp);
}

void AdModel::SetupAdMonitor(HINSTANCE hInstance)
{
	if (MonitorState::STOP != _state)
	{
		OutputDebugStringW(L"���������Ѿ�����!");
		return;
	}

	ShellHook shellHook;
	if (!shellHook.SetShellHook(hInstance))
	{
		OutputDebugStringW(L"��װ����ʧ��!");
		return;
	}
	
	shellHook._callback = std::bind(&AdModel::GetCreateWindowsParamter, this, std::placeholders::_1);

	_state = MonitorState::START;

	MSG msg;
	while (GetMessageW(&msg, NULL, 0, 0)) //�����������ģ����д�����Ϣ��ʱ��Ż᷵��
	{
		if (MonitorState::RUNNING == _state)
		{
			//��������
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else if (MonitorState::START == _state || MonitorState::SUSPEND == _state)
		{
			//��������������δ�������ػ���ͣ����

		}
		else
		{
			//�رչ�浯��������
			break;
		}
	}
}
