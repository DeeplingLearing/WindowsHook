#pragma once
#ifdef HOOK_API_EXPORTS
#define HOOK_API_API __declspec(dllexport)
#else
#define HOOK_API_API __declspec(dllimport)
#endif

#include <windows.h>
// 此类是从 hook_api.dll 导出的
extern "C" class HOOK_API_API HookApi {
public:
	HookApi();
	~HookApi();
public:
	//brief:实现HOOK API
	bool Hook(wchar_t* moudleName, char* funName, FARPROC  pFun);
	//brief:重新HOOK
	void ReHook();
	//biref:撤销HOOK
	void UnHook();
public:
	LPVOID _pOldFunEntry; //初始函数地址
	LPVOID _pNewFunEntry; //HOOK后的函数地址

	BYTE _bOldByte[5]; //原始字节
	BYTE _bNewByte[5]; //目标字节
};
