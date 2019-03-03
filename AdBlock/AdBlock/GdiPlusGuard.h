#pragma once

#include "common.h"
//using namespace Gdiplus;

//GdiPlus库的自动启动和卸载
//Gdiplus比Gdi的功能强调很多，且为c++实现的类库。更加详细的内容参考：https://docs.microsoft.com/zh-cn/windows/desktop/api/_gdiplus/

class AutoGidPlus
{
public:
	AutoGidPlus();
	virtual ~AutoGidPlus();
private:
	ULONG_PTR _gdiplusToken;
};

