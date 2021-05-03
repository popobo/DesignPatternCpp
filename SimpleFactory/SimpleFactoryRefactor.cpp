#include <iostream>
#include <string>
#include "DynOBJ.h"

using namespace std;

class API {
public:
	virtual void test(string s) = 0;
protected:
	API() {}
};

class IMPL1 :public API {
public:
	void test(string s) {
		cout << "impl_1 test" << s << endl;
	}
};

class IMPL2 :public API {
public:
	void test(string s) {
		cout << "impl_2 test" << s << endl;
	}
};


// 传入参数1，从数据库中读取，传入参数2，从文本中读取
// 实现了客户端调用与IMPL1与IMPL2的隔离
class Factory {
public:
	static API* createAPI(int type) {
		API* api = nullptr;
		switch (type)
		{
		case 1:
			api = new IMPL1();
			break;
		case 2:
			api = new IMPL2();
			break;
		default:
			break;
		}
		return api;
	}

	static API* createAPI() {
		return new IMPL2();
	}
};

int main1() {
	API* api = Factory::createAPI(2); //客户端还是知道工厂细节, 知道使用1或2
	api->test("hello world 现在是使用简单工厂重构");


	system("pause");
	return 0;
}

//问题需求：
/*
static API* createAPI() {
	return new IMPL2();
}

//动态创建
*/


/*class IMPL2Helper {
public:
	IMPL2Helper() {
		CObjectFactory::registerClass("IMPL2", IMPL2Helper::createObjectFunc);
	}

	static void* createObjectFunc() {
		return new IMPL2();
	}
};*/

REG_CLASS(IMPL1)
REG_CLASS(IMPL2)

int main2() {
	//IMPL2 * p2 = static_cast<IMPL2*>(IMPL2Helper::createObjectFunc());
	//p2->test("p2");
	IMPL2* p2 = static_cast<IMPL2*>(CObjectFactory::createObject("IMPL2"));
	p2->test("p2");
	system("pause");
	return 0;
}

class AutoFactory {
public:
	static API* createApi() {
		API* pApi = nullptr;
		pApi = static_cast<API*>(CObjectFactory::createObject("IMPL2"));
		return pApi;
	}
};

int main() {
	API* api = AutoFactory::createApi();
	api->test("No idea what is inside");
	system("pause");
	return 0;
}