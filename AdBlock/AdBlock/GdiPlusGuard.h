#pragma once

#include "common.h"
//using namespace Gdiplus;

//GdiPlus����Զ�������ж��
//Gdiplus��Gdi�Ĺ���ǿ���ܶ࣬��Ϊc++ʵ�ֵ���⡣������ϸ�����ݲο���https://docs.microsoft.com/zh-cn/windows/desktop/api/_gdiplus/

class AutoGidPlus
{
public:
	AutoGidPlus();
	virtual ~AutoGidPlus();
private:
	ULONG_PTR _gdiplusToken;
};

