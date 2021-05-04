#include <iostream>
#include <map>
#include <stdio.h>
#include <string>
using namespace std;

//»º´æÊµÀý¸öÊý
const static int NUM_MAX = 5;

class Singleton3;
static auto myMap = map<int, Singleton3*>();

class Singleton3 {
private:
	Singleton3() {
		cout << "Singleton3()" << endl;
		m_single = nullptr;
	}
private:
	static Singleton3* m_single;
	static int m_IntanceCount;

public:
	static Singleton3* getInstance() {
		m_single = myMap[m_IntanceCount];
		if (nullptr == m_single)
		{
			m_single = new Singleton3;
			myMap[m_IntanceCount] = m_single;
		}
		m_IntanceCount++;
		if (m_IntanceCount > NUM_MAX)
		{
			m_IntanceCount = 1;
		}
		return m_single;
	}
};

Singleton3* Singleton3::m_single = nullptr;
int Singleton3::m_IntanceCount = 1;

int main() {
	Singleton3* p1 = Singleton3::getInstance();
	Singleton3* p2 = Singleton3::getInstance();
	Singleton3* p3 = Singleton3::getInstance();
	Singleton3* p4 = Singleton3::getInstance();
	Singleton3* p5 = Singleton3::getInstance();
	printf("p1=%x,p2=%x,p3=%x,p4=%x,p5=%x\n", p1, p2, p3, p4, p5);

	Singleton3* p6 = Singleton3::getInstance();
	Singleton3* p7 = Singleton3::getInstance();
	Singleton3* p8 = Singleton3::getInstance();
	Singleton3* p9 = Singleton3::getInstance();
	Singleton3* p10 = Singleton3::getInstance();
	printf("p6=%x,p7=%x,p8=%x,p9=%x,p10=%x\n", p6, p7, p8, p9, p10);

	system("pause");
	return 0;
}