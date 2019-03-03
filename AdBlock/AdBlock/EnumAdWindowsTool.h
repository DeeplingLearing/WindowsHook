#pragma once
#include "common.h"

class EnumAdWindowsTool
{
public:
	EnumAdWindowsTool();
	virtual ~EnumAdWindowsTool();
public:
	//brief:����ö�ٴ��ڻص�����
	static void SetCallback(const EnumTopLevelWindowsCallback& callback);
	//brief:ö�����������ж�������
	static void EnumTopLevelWindows();
	//brief:ͨ�����ھ����ȡ��������
	static WndParamter GetWindowParamter(HWND hwnd);
	//brief:��ȡ�����������ϵ�λ��
	static bool CaputureWindows(HWND hwnd, std::wstring filename);
	//brief:�ر�ָ������
	//note: ���ڴ��ڻ�����WM_CLOSE��Ϣ������ֻҪ���������رգ�һ������WM_DESTORY��Ϣ
	static void CloseWindows(HWND hwnd);

	//brief:����ö�ٻص�����
	static EnumTopLevelWindowsCallback _callback;
};

