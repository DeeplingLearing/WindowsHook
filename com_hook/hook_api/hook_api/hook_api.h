#pragma once
#ifdef HOOK_API_EXPORTS
#define HOOK_API_API __declspec(dllexport)
#else
#define HOOK_API_API __declspec(dllimport)
#endif

#include <windows.h>
// �����Ǵ� hook_api.dll ������
extern "C" class HOOK_API_API HookApi {
public:
	HookApi();
	~HookApi();
public:
	//brief:ʵ��HOOK API
	bool Hook(wchar_t* moudleName, char* funName, FARPROC  pFun);
	//brief:����HOOK
	void ReHook();
	//biref:����HOOK
	void UnHook();
public:
	LPVOID _pOldFunEntry; //��ʼ������ַ
	LPVOID _pNewFunEntry; //HOOK��ĺ�����ַ

	BYTE _bOldByte[5]; //ԭʼ�ֽ�
	BYTE _bNewByte[5]; //Ŀ���ֽ�
};
