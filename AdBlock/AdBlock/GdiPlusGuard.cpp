#include "GdiPlusGuard.h"



AutoGidPlus::AutoGidPlus()
{
	Gdiplus::GdiplusStartupInput gdiplusStartupInput;
	Gdiplus::GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);
}


AutoGidPlus::~AutoGidPlus()
{
	Gdiplus::GdiplusShutdown(_gdiplusToken);
}
