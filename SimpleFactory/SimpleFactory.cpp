#include <iostream>
#include <string>

using namespace std;

class API {
public:
	virtual void test(string) = 0;
protected:
	//API();
	// ����Ĺ��췽����Ҫʵ��
	API() {}
};

class IMPL :public API {
public:
	void test(string s) {
		cout << "impl test" << s << endl;
	}
};

int main_() {
	API* api = new IMPL();
	api->test("hello");
	
	system("pause");
	return 0;
}