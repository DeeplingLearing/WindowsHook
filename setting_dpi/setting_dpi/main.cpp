#include "setting_dpi.h"
#include "my_wnd.h"
#include <iostream>

#include <atlimage.h>
#include "gdiplus.h" 
using namespace Gdiplus;
#pragma comment(lib,"gdiplus.lib")


using namespace std;


void main()
{
	//::SetProcessDPIAware();

	DpiTools dpi;
	dpi.Init();

	cout << "dpi base:" << dpi.GetDPIBaseLine() << "\t dpiX:" << dpi.GetDPIX() << "\t dpiY:" << dpi.GetDPIY() << endl;

	HWND hwnd = FindWindowW(L"OrayUI", L"向日葵客户端");

	MyWnd* wnd1 = nullptr;
	MyWnd* wnd2 = nullptr;
	int tipWndWidth = 100;
	int tipWndHeight = 50;

	if (hwnd)
	{
		WINDOWINFO wi;
		wi.cbSize = sizeof(wi);
		GetWindowInfo(hwnd, &wi);
		int left1 = wi.rcWindow.left;
		int top1 = wi.rcWindow.top;
		int w1 = wi.rcWindow.right - wi.rcWindow.left;
		int h1 = wi.rcWindow.bottom - wi.rcWindow.top;
		wstring title1 = L"T1";
		wstring className1 = L"demo1";
		wnd1 = new MyWnd(left1 + w1 - tipWndWidth, top1 - tipWndHeight, tipWndWidth, tipWndHeight, title1, className1);

		if (wnd1->Create())
		{
			wnd1->Show();
		}

		cout << "(" << wi.rcWindow.left << ", " << wi.rcWindow.top << ", " << wi.rcWindow.right << ", " << wi.rcWindow.bottom << ")" << endl;
		RECT ret = wi.rcWindow;
		dpi.UnScaleRect(ret);

		int left2 = ret.left;
		int top2 = ret.top;
		int w2 = ret.right - ret.left;
		int h2 = ret.bottom - ret.top;
		wstring title2 = L"T2";
		wstring className2 = L"demo2";
		wnd2 = new MyWnd(left2 + w2 - tipWndWidth, top2 - tipWndHeight, tipWndWidth, tipWndHeight, title2, className2);

		if (wnd2->Create())
		{
			wnd2->Show();
		}
		cout << "(" << ret.left << ", " << ret.top << ", " << ret.right << ", " << ret.bottom << ")" << endl;
	}

	system("pause");

	if (wnd1)
	{
		delete wnd1;
		wnd1 = nullptr;
	}

	if (wnd2)
	{
		delete wnd2;
		wnd2 = nullptr;
	}
}

//int GetEncoderClsid(const WCHAR* format, CLSID* pClsid)
//{
//	UINT     num = 0;                     //   number   of   image   encoders 
//	UINT     size = 0;                   //   size   of   the   image   encoder   array   in   bytes 
//
//	ImageCodecInfo*   pImageCodecInfo = NULL;
//
//	GetImageEncodersSize(&num, &size);
//	if (size == 0)
//		return   -1;     //   Failure 
//
//	pImageCodecInfo = (ImageCodecInfo*)(malloc(size));
//	if (pImageCodecInfo == NULL)
//		return   -1;     //   Failure 
//
//	GetImageEncoders(num, size, pImageCodecInfo);
//
//	for (UINT j = 0; j < num; ++j)
//	{
//		if (wcscmp(pImageCodecInfo[j].MimeType, format) == 0)
//		{
//			*pClsid = pImageCodecInfo[j].Clsid;
//			free(pImageCodecInfo);
//			return   j;     //   Success 
//		}
//	}
//
//	free(pImageCodecInfo);
//	return   -1;     //   Failure 
//}
//
//void CaptureWndImage(int left, int top, int w, int h, WCHAR* path)
//{
//	//先截取桌面的图片
//	HDC dcScreen = GetDC(NULL);
//	HDC hScreenMem = NULL;
//
//	int cx = GetSystemMetrics(SM_CXSCREEN);
//	int cy = GetSystemMetrics(SM_CYSCREEN);
//
//	hScreenMem = CreateCompatibleDC(dcScreen);
//
//	HBITMAP hScreenBitmap = NULL, hScreenOldBitmap = NULL;
//
//	hScreenBitmap = CreateCompatibleBitmap(dcScreen, w, h);
//
//	hScreenOldBitmap = (HBITMAP)SelectObject(hScreenMem, hScreenBitmap);
//	BitBlt(hScreenMem, 0, 0, w, h, dcScreen, left, top, SRCCOPY);
//
//	//将截图标识出来
//	HPEN hPen = CreatePen(PS_SOLID, 1, RGB(255, 0, 0));
//	HPEN hOldPen = (HPEN)SelectObject(hScreenMem, hPen);
//	MoveToEx(hScreenMem, 0, 0, NULL);
//	LineTo(hScreenMem, w - 1, 0);
//	LineTo(hScreenMem, w - 1, h - 1);
//	LineTo(hScreenMem, 1, h - 1);
//	LineTo(hScreenMem, 0, 0);
//
//
//	Bitmap bitmap(hScreenBitmap, NULL);
//	CLSID clsId;
//	GetEncoderClsid(L"image/png", &clsId);
//	bitmap.Save(path, &clsId);
//
//	//释放掉设备资源
//	SelectObject(hScreenMem, hOldPen);
//	DeleteObject(hPen);
//	SelectObject(hScreenMem, hScreenOldBitmap);
//
//	DeleteObject(hScreenMem);
//	DeleteObject(hScreenBitmap);
//
//	ReleaseDC(NULL, dcScreen);
//}
//
//
//void main()
//{
//	GdiplusStartupInput gdiplusStartupInput;
//	ULONG_PTR _gdiplusToken;
//	GdiplusStartup(&_gdiplusToken, &gdiplusStartupInput, NULL);
//	HWND hWnd = FindWindowW(L"WeChatLoginWndForPC", L"登录");
//
//	if (hWnd)
//	{
//		WINDOWINFO wi;
//		GetWindowInfo(hWnd, &wi);
//		int left = wi.rcWindow.left;
//		int top = wi.rcWindow.top;
//		int width = wi.rcWindow.right - wi.rcWindow.left;
//		int height = wi.rcWindow.bottom - wi.rcWindow.top;
//
//		SetWindowPos(hWnd, HWND_TOPMOST, NULL, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//		CaptureWndImage(left, top, width, height, L"screen1.png");
//		SetWindowPos(hWnd, HWND_NOTOPMOST, NULL, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
//		cout << "error:" << GetLastError() << endl;
//	}
//
//
//	GdiplusShutdown(_gdiplusToken);
//
//	getchar();
//
//}



