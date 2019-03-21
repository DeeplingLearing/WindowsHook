#pragma once
#include <Windows.h>


class DpiTools
{
public:
	DpiTools();
	~DpiTools();
public:
	void Init();
	int GetDPIX();
	int GetDPIY();
	int GetDPIBaseLine();
	int GetResolutionX();
	int GetResolutionY();

	int ScaleX(int width);
	int ScaleY(int height);
	void ScaleRect(RECT& rect);
	int UnScaleX(int width);
	int UnScaleY(int height);
	void UnScaleRect(RECT& rect);
private:
	int _dpiBaseLine;
	int _dpiX;
	int _dpiY;

	int _resolutionX;
	int _resolutionY;
};