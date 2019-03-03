#pragma once
#include <windows.h>
#include <string>
#include <sstream>
#include <functional>
#include <cassert>

//GDI+
#include <GdiPlus.h> 
#pragma comment(lib, "gdiplus.lib")

//���ڲ���
struct WndParamter
{
	HWND _hwnd; //���ھ��
	std::wstring _class; //������
	std::wstring _text; //���ڱ���
	RECT _rect;//�����������ϵ�λ��
};
//���̲���
struct ProcessInfo
{
	DWORD _dwPId; //���ڵĽ���Id;(�������ɴ����̴߳����ģ�һ������Ӧ��������һ�������߳�)
	std::wstring _processName; //������
	std::wstring _moudlePath; //���̿�ִ���ļ�·��
	std::wstring _producteName;//��Ʒ��
};
typedef std::function<void(const WndParamter&)> EnumTopLevelWindowsCallback;
typedef std::function<void(const WndParamter&)> CreateWndowsCallback;