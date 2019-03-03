#include "EnumAdWindowsTool.h"



EnumTopLevelWindowsCallback EnumAdWindowsTool::_callback = nullptr; //��ʼ����̬��Ա����

static BOOL CALLBACK EnumWindowsProc(HWND hwnd, LPARAM lParam)
{
	if (!IsWindowVisible(hwnd))
	{
		OutputDebugStringW(L"EnumWindowsProc: windows is not visible!\n");
		return TRUE; //����ö��
	}

	WndParamter wp = EnumAdWindowsTool::GetWindowParamter(hwnd);

	std::wostringstream os;
	os << L"�´����Ĵ��ھ��:" << wp._hwnd << L"\t��������:" << wp._class << L"\t���ڱ���:" << wp._text << L"\t�ɼ�:"<< L"\t��������:(" << wp._rect.left 
	   << L", " << wp._rect.top << L")" << L"\t���ڴ�С:(" << (wp._rect.right - wp._rect.left) << L", " << (wp._rect.bottom - wp._rect.top) << L")" << L"\n";

	if (wp._class.empty() && wp._text.empty())
	{
		std::wstring str = L"classname and text both are empty!\t";
		str += os.str();
		OutputDebugStringW(str.c_str());
		return TRUE;
	}
	
	//���㶥�������������λ��
	int width = wp._rect.right - wp._rect.left;
	int height = wp._rect.bottom - wp._rect.top;

	if (width <= 0 || height <= 0)
	{
		//���ڿ���и�һΪ0 �������Ͽ������� ���Թ��˵�
		std::wstring str = L"���ڿ���Ϊ��!\t";
		str += os.str();
		OutputDebugStringW(str.c_str());
		return TRUE;
	}

	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	if (wp._rect.right <= 0 || wp._rect.left > cx || wp._rect.bottom <= 0 || wp._rect.top >= cy)
	{
		//���ڲ������淶Χ�� ���˵�
		std::wstring str = L"���ڲ������淶Χ��!\t";
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
