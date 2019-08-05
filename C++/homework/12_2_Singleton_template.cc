/*ʵ��һ��ģ����ʽ�ĵ����࣬
Ҫ������������͵��ྭ��Singleton�Ĵ���֮��
���ܻ�ȡһ���������󣬲��ҿ��Դ����������*/
#include <stdlib.h>
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Point;
class Computer;

template<class T>
class Singleton
{
public:
	template<typename... Args>
	static T* getInstance(Args... args)
	{
		if (nullptr == _pInstance) {
			::atexit(destory);
			_pInstance = new T(args...);
		}
		return _pInstance;
	}

	static void destory()
	{
		if (_pInstance) {
			delete _pInstance;
		}
	}

private:
	Singleton() {}
	~Singleton() {}

private:
	static T* _pInstance;
};

class Point
{
public:
	Point(int ix = 0, int iy = 0)
		: _ix(ix)
		, _iy(iy)
	{}

	~Point() {}

	//������Ա����
	//����

private:
	int _ix;
	int _iy;
};

class Computer
{
public:
	Computer(const char* name, int price)
		: _name(new char[strlen(name) + 1]())
		, _price(price)
	{
		strcpy(_name, name);
	}

	~Computer()
	{
		if (_name) {
			delete[] _name;
		}
	}

	//������Ա����
	//����

private:
	char* _name;
	int _price;
};

Point* Singleton<Point>::_pInstance = nullptr;
Computer* Singleton<Computer>::_pInstance = nullptr;


int main()
{
	Computer* p1 = Singleton<Computer>::getInstance("Xiaomi", 6666);
	Computer* p2 = Singleton<Computer>::getInstance("Xiaomi", 6666);

	Point* p3 = Singleton<Point>::getInstance(1, 2);
	Point* p4 = Singleton<Point>::getInstance(1, 2);

	cout << "p1 = " << p1 << endl;
	cout << "p2 = " << p2 << endl;
	cout << "p3 = " << p3 << endl;
	cout << "p4 = " << p4 << endl;
	
	return 0;
}