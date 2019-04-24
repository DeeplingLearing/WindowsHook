// hook_api.cpp : 定义 DLL 应用程序的导出函数。
//

#include "stdafx.h"
#include "hook_api.h"


HookApi::HookApi()
{}

HookApi::~HookApi()
{}


bool HookApi::Hook(wchar_t* moudleName, char* funName, FARPROC pFun)
{
	HMODULE hMod = GetModuleHandleW(moudleName);

	if (NULL == hMod)
	{
		return false;
	}

	_pNewFunEntry = (LPVOID)pFun;
	_pOldFunEntry = (LPVOID)GetProcAddress(hMod, funName);
	_bNewByte[0] = 0xe9; //??
	*(PDWORD)(&(_bNewByte[1])) = (DWORD)_pNewFunEntry - (DWORD)_pOldFunEntry - 5;

	DWORD dwProtect, dwWriteByte, dwReadByte;
	if (!VirtualProtect((LPVOID)_pOldFunEntry, 5, PAGE_READWRITE, &dwProtect))
	{
		return false;
	}

	if (!ReadProcessMemory(GetCurrentProcess(), (LPVOID)_pOldFunEntry, _bOldByte, 5, &dwReadByte))
	{
		return false;
	}

	if (!WriteProcessMemory(GetCurrentProcess(), (LPVOID)_pOldFunEntry, _bNewByte, 5, &dwWriteByte))
	{
		return false;
	}

	if (!VirtualProtect((LPVOID)_pOldFunEntry, 5, dwProtect, NULL))
	{
		return false;
	}

	return true;
}

void HookApi::ReHook()
{
	DWORD dwProtect, dwWriteByte;
	VirtualProtect(_pOldFunEntry, 5, PAGE_READWRITE, &dwProtect);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)_pOldFunEntry, _bNewByte, 5, &dwWriteByte);
	VirtualProtect(_pOldFunEntry, 5, dwProtect, NULL);
}

void HookApi::UnHook()
{
	DWORD dwProtect, dwWriteByte;
	VirtualProtect(_pOldFunEntry, 5, PAGE_READWRITE, &dwProtect);
	WriteProcessMemory(GetCurrentProcess(), (LPVOID)_pOldFunEntry, _bOldByte, 5, &dwWriteByte);
	VirtualProtect(_pOldFunEntry, 5, dwProtect, NULL);
}