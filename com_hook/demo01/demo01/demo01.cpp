// demo01.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <Windows.h>
using namespace std;


//class A
//{
//public:
//	virtual void Test1() = 0;
//	virtual void Test2() = 0;
//};
//
//class B : public A
//{
//public:
//	virtual void Test1()
//	{
//		cout << "Test1" << endl;
//	}
//
//	virtual void Test2()
//	{
//		cout << "Test2" << endl;
//	}
//};
//
//
//
//int main()
//{
//	A* pA = new B();
//
//	_asm int 3; //break point
//
//
//	delete pA;
//	pA = nullptr;
//
//
//    return 0;
//}

//__stdcall:

//class A
//{
//public:
//	A()
//	{
//		_n = 0;
//	}
//public:
//	//void __stdcall Test1(void* this)
//	virtual void __stdcall Test1()
//	{
//		cout << "Test1. n = " << this->_n++ << endl;
//	}
//
//	virtual void __stdcall Test2()
//	{
//		cout << "Test2. n = " << _n++ << endl;
//	}
//private:
//	int _n;
//};
//
//int main()
//{
//	A* p = new A();
//
//	p->Test1();
//	p->Test2();
//
//	LPDWORD vtablePtr = LPDWORD((*(LPDWORD)p)); //ȡ�麯���׵�ַ
//
//	//ȡTest1��Test2������ַ
//	DWORD Func_1 = *(vtablePtr + 0);
//	DWORD Func_2 = *(vtablePtr + 1);
//
//	typedef void(__stdcall *FUN_MEMBER)(void*);
//
//	FUN_MEMBER fn1 = (FUN_MEMBER)(Func_1);
//	FUN_MEMBER fn2 = (FUN_MEMBER)(Func_2);
//
//	fn1(p);
//	fn2(p);
//
//	delete p;
//	p = nullptr;
//
//	return 0;
//}


//��Ad�ڴ�Ϊ�����ָ���ַ ��Ա������ַ
//class A
//{
//public:
//	A()
//	{
//		_n = 1;
//	}
//public:
//	virtual void __stdcall Test1()
//	{
//		cout << "A::Test1. n = " << _n++ << endl;
//	}
//
//	virtual void __stdcall Test2()
//	{
//		cout << "A::Test2. n = " << _n++ << endl;
//	}
//
//private:
//	int _n;
//};
//
//class B
//{
//public:
//	B()
//	{
//		_n = 2;
//	}
//
//public:
//	virtual void __stdcall Test1()
//	{
//		cout << "B::Test1. n = " << _n++ << endl;
//	}
//
//	virtual void __stdcall Test2()
//	{
//		cout << "B::Test2. n = " << _n++ << endl;
//	}
//private:
//	int _n;
//};
//
//void Exchange(void** p1, void** p2)
//{
//	void* temp = *p1;
//	*p1 = *p2;
//	*p2 = temp;
//}
//
//void main()
//{
//	A* pA = new A();
//	B* pB = new B();
//
//	pA->Test1();
//	pA->Test2();
//
//	pB->Test1();
//	pB->Test2();
//
//	Exchange((void**)&pA, (void**)&pB);
//	cout << "----------------------�ָ���-----------------" << endl;
//	pA->Test1();
//	pA->Test2();
//
//	pB->Test1();
//	pB->Test2();
//
//	delete pA;
//	delete pB;
//	pA = nullptr;
//	pB = nullptr;
//}

//class A
//{
//public:
//	A()
//	{
//		_n = 1;
//		_m = 2;
//	}
//
//public:
//	virtual void Test1()
//	{
//		cout << "A::Test1. n = " << _n++ << " m = " << _m++ << endl;
//	}
//
//	virtual void Test2()
//	{
//		cout << "A::Test2. n = " << _n++ << " m = " << _m++ << endl;
//	}
//private:
//	int _n;
//	int _m;
//};
//
//class B
//{
//public:
//	B()
//	{
//		_n = 3;
//		_m = 4;
//
//		_pA = new A();
//	}
//	~B()
//	{
//		if (_pA)
//		{
//			delete _pA;
//			_pA = nullptr;
//		}
//	}
//public:
//	//�滻��A::Test2�ķ���
//	void A_Test2()
//	{
//		cout << "replace A Test2." << endl;
//	}
//
//	template <typename T>
//	static DWORD GetMemberFxnAddr(T MemberFxnName)
//	{
//		union
//		{
//			T From;
//			DWORD To;
//		}union_cast;
//		union_cast.From = MemberFxnName;
//		
//		return union_cast.To;
//	}
//
//	void Test()
//	{
//		_pA->Test1();
//		_pA->Test2();
//
//		LPDWORD _vtableAddr = (LPDWORD)(*LPDWORD((LPVOID)_pA)); //��ȡ��A������ַ
//
//		//�������ɶ���д
//		DWORD dwOld = 0;
//		if (!VirtualProtect(_vtableAddr, sizeof(LONG) * 2, PAGE_READWRITE, &dwOld)) //�ڶ�������Ϊƫ���ֽ���
//		{
//			return;
//		}
//		//����A�ĵڶ����麯���滻Ϊ��B�ĺ���
//		_vtableAddr[1] = GetMemberFxnAddr(&B::A_Test2);
//		//�ָ���ԭ����ģʽ
//		if (!VirtualProtect(_vtableAddr, sizeof(LONG) * 2, dwOld, &dwOld))
//		{
//			return;
//		}
//
//		_pA->Test1();
//		_pA->Test2();
//	}
//private:
//	void* _vtableAddr; //ָ���麯����ָ��
//	//����A�ڴ�ṹ����.
//	int _n;
//	int _m;
//	A* _pA;
//};
//
//void main()
//{
//	B obj;
//	obj.Test();
//}

class A
{
public:
	A()
	{
		_n = 0;
	}
public:
	virtual void __stdcall Test1(int a)
	{
		cout << "A::Test1. a = " << a << "\t A::_n = " << _n++ << endl;
	}

	virtual void __stdcall Test2(int a)
	{
		cout << "A::Test2. a = " << a << "\t A::_n = " << _n++ << endl;
	}
public:
	int _n;
};

//�滻class A��Test2����
void __stdcall A_Test2(void* pThis, int a)
{
	cout << "Replace A::Test2. a = " << a << "\t this->_n = " << ((A*)pThis)->_n << endl;
}

void main()
{
	A* pA = new A();

	pA->Test1(1);
	pA->Test2(2);

	//��ȡ����ַ
	LPDWORD vtablePtr = (LPDWORD)(*LPDWORD((LPVOID)pA));

	DWORD dwOld;

	if (!VirtualProtect(vtablePtr, sizeof(LONG) * 2, PAGE_READWRITE, &dwOld))
	{
		return;
	}

	vtablePtr[1] = (DWORD)(LPVOID)A_Test2;

	if (!VirtualProtect(vtablePtr, sizeof(LONG) * 2, dwOld, &dwOld))
	{
		return;
	}

	pA->Test1(3);
	pA->Test2(4);

	delete pA;
	pA = nullptr;
}