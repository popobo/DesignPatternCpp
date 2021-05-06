#include <string>
#include <map>
#include <memory>
#include <functional>
#include <iostream>

using namespace std;

template <class T>
class IocContainer {
public:
	IocContainer(void) {}
	~IocContainer() {}

	//注册需要创建对象的构造函数，通过一个唯一的标识，以便于以后查找
	template<class Drived>
	void RegisterType(string strKey) {
		function<T*()> function = [] {return new Drived(); };
		RegisterType(strKey, function);
	}
	//根据唯一的标识去查找对应的构造函数
	T* Resolve(string strKey) {
		if (m_createMap.find(strKey) == m_createMap.end())
		{
			return nullptr;
		}
		function<T* ()> function = m_createMap.find(strKey)->second;
		return function();
	}

	//创建智能指针
	shared_ptr<T> ResolveShared(string strKet) {
		T* prt = Resolve(strKet);
		return shared_ptr<T>(prt);
	}

private:
	void RegisterType(string strKey, function<T* ()> creator) {
		if (m_createMap.find(strKey) != m_createMap.end())
		{
			throw invalid_argument("key exists");
		}
		//m_createMap[strKey] = creator; //效率较低
		m_createMap.emplace(strKey, creator);
	}
	map<string, function<T* ()>> m_createMap;
};

class ICar {
public:
	virtual ~ICar() {}
	virtual void test() const = 0;
};

class Bus : public ICar {
public:
	Bus() {}
	void test() const { cout << "Bus::test()" << endl; }
};

class Track : public ICar {
public:
	Track() {}
	void test() const { cout << "Track::test()" << endl; }
};

int main() {
	IocContainer<ICar> carIOC;
	carIOC.RegisterType<Bus>("Bus");
	carIOC.RegisterType<Track>("Track");

	shared_ptr<ICar> bus = carIOC.ResolveShared("Bus");
	bus->test();
	shared_ptr<ICar> track = carIOC.ResolveShared("Track");
	track->test();

	system("pause");
	return 0;
}