//回避多线程安全问题
#include <iostream>
#include <map>
#include <stdio.h>
using namespace std;

class Singleton2;

static auto myMap = map<string, Singleton2*>();

//懒汉延迟加载

class Singleton2 {
private:
	Singleton2() {
		cout << "Single2()" << endl;
		m_single = nullptr;
	}
private:
	static Singleton2* m_single;
	static string DEFAULT_KEY;
public:
	static Singleton2* getIntance() {
		//auto it = myMap.find(DEFAULT_KEY);
		if (myMap.find(DEFAULT_KEY) != myMap.end())
		{
			return myMap.find(DEFAULT_KEY)->second;
		}
		if (nullptr == m_single)
		{
			m_single = new Singleton2();
			myMap[DEFAULT_KEY] = m_single;
		}
		return m_single;
	}
};

Singleton2* Singleton2::m_single = nullptr;
string Singleton2::DEFAULT_KEY = "one";

int main11() {
	Singleton2 *p1 = Singleton2::getIntance();
	Singleton2 *p2 = Singleton2::getIntance();
	printf("p1=%x,p2=%x\n", p1, p2);
	system("pause");
	return 0;
}