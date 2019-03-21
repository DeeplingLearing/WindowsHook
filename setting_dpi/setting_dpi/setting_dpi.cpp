#include "setting_dpi.h"

DpiTools::DpiTools()
	: _dpiBaseLine(96)
	, _dpiX(96)
	, _dpiY(96)
{
}

DpiTools::~DpiTools()
{
}

void DpiTools::Init()
{
	HDC hScreenDc = ::GetDC(NULL);
	//��ȡʵ�ʵ��߼�����
	_dpiX = ::GetDeviceCaps(hScreenDc, LOGPIXELSX); 
	_dpiY = ::GetDeviceCaps(hScreenDc, LOGPIXELSY);
	::ReleaseDC(NULL, hScreenDc);

	//��ȡ��Ļ��С
	_resolutionX = ::GetSystemMetrics(SM_CXSCREEN);
	_resolutionY = ::GetSystemMetrics(SM_CYSCREEN);

}

int DpiTools::GetDPIX()
{
	return _dpiX;
}

int DpiTools::GetDPIY()
{
	return _dpiY;
}

int DpiTools::GetDPIBaseLine()
{
	return _dpiBaseLine;
}

int DpiTools::GetResolutionX()
{
	return _resolutionX;
}

int DpiTools::GetResolutionY()
{
	return _resolutionY;
}

int DpiTools::ScaleX(int width)
{
	return MulDiv(width, _dpiX, _dpiBaseLine); //����dpi����Ŀ��
}

int DpiTools::ScaleY(int height)
{
	return MulDiv(height, _dpiY, _dpiBaseLine); //����dpi����ĸ߶�
}

void DpiTools::ScaleRect(RECT & rect)
{
	rect.left = ScaleX(rect.left);
	rect.top = ScaleY(rect.top);
	rect.right = ScaleX(rect.right);
	rect.bottom = ScaleY(rect.bottom);
}

int DpiTools::UnScaleX(int width)
{
	return MulDiv(width, _dpiBaseLine, _dpiX);
}

int DpiTools::UnScaleY(int height)
{
	return MulDiv(height, _dpiBaseLine, _dpiY);
}

void DpiTools::UnScaleRect(RECT & rect)
{
	rect.left = UnScaleX(rect.left);
	rect.top = UnScaleY(rect.top);
	rect.right = UnScaleX(rect.right);
	rect.bottom = UnScaleY(rect.bottom);
}
