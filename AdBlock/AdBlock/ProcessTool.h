#pragma once
#include "common.h"

//���̴������� zeus�Ѿ��и÷���

class ProcessTool
{
public:
	ProcessTool();
	virtual ~ProcessTool();
public:
	//brief:��ȡ���ڽ���Id
	static void GetWindowsProcessId(HWND hwnd);
	//brief:��ȡ������
	static void GetProcessName(const DWORD dwPId, std::wstring& processName);
	//brief:��ȡ��Ʒ��
	static void GetProductNanme();
	//brief:��ȡ����ͼ��
	static void GetProcessIcon(const DWORD dwPId, std::wstring& filename);
private:
	//brief:
};

