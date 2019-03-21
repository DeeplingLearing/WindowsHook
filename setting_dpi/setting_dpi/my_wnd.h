#pragma once
#include <Windows.h>
#include <string>
using namespace std;


class MyWnd
{
public:
	MyWnd(int left, int top, int w, int h, const wstring& title, wstring& className);
	~MyWnd();
public:
	bool Create(HWND hParent = NULL);
	bool Show();
	bool Close();
private:
	HWND _hwnd;
	int _left;
	int _top;
	int _width;
	int _height;
	wstring _title;
	wstring _className;
};