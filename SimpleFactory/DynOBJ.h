#pragma once

#include <string>
#include <map>


using namespace std;

typedef void* (*Contructor)();

class CObjectFactory {
public: 
	static void registerClass(std::string className, Contructor contructor) {
		contructors()[className] = contructor;
	}

	static void* createObject(const std::string& className) {
		Contructor contructor = nullptr;
		if (contructors().find(className) != contructors().end())
		{
			contructor = contructors().find(className)->second;
		}
		if (nullptr == contructor)
		{
			return nullptr;
		}
		return (*contructor)();
	}

private:
	// key是要动态创建的类的类名，value是构造函数
	inline static std::map<std::string, Contructor>& contructors() {
		static std::map<std::string, Contructor> instance;
		return instance;
	}
};

#define REG_CLASS(class_name) \
class class_name##Helper { \
public: \
	class_name##Helper() { \
		CObjectFactory::registerClass(#class_name, class_name##Helper::createObjectFunc); \
	} \
	static void* createObjectFunc() { \
		return new IMPL2(); \
	} \
}; \
class_name##Helper class_name##helper;