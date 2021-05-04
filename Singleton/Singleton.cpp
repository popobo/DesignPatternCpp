#include <iostream>
#include <stdio.h>
#include <afxwin.h>
using namespace std;

CRITICAL_SECTION g_cs;

class Singleton {
private:
	Singleton() {
		m_single = nullptr;
		cout << "Singleton()" << endl;
	};
private:
	static Singleton* m_single;

public:
	static Singleton* getInstance() { //懒汉式:延迟加载
		::EnterCriticalSection(&g_cs);
		if (nullptr == m_single) 
		{
			m_single = new Singleton();	
		}
		::LeaveCriticalSection(&g_cs);
		return m_single;
	}
};

Singleton* Singleton::m_single = nullptr;//new Singleton; 在C++中构造函数不是线程安全的

UINT Func(LPVOID) {
	printf("%x\n", Singleton::getInstance());
	return 0;
}

int main1() {
	//Singleton *p1 = Singleton::getInstance();
	//Singleton *p2 = Singleton::getInstance();
	//printf("p1=%x,p2=%x\n", p1, p2);
	::InitializeCriticalSection(&g_cs);
	for (int i = 0;i < 10; i++)
	{
		AfxBeginThread(Func, nullptr);
	}
	::DeleteCriticalSection(&g_cs);
	system("pause");
	return 0;
}