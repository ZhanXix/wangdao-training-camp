#include <iostream>
#include <functional>
using std::cout;
using std::endl;

void display()
{
	cout << "display()" << endl;
}

void print()
{
	cout << "print()" << endl;
}

int add(int x, int y)
{
	return x + y;
}

//函数类型
typedef void(*Function)();

class Example
{
public:
	Example() = default;

	void display()
	{
		cout << "Example::display()" << endl;
	}

	int add(int x, int y)
	{
		return x + y;
	}

	int _data = 10;

};

int test0()
{
	void(*f)() = display;
	f();

	f = print;
	f();

	return 0;
}

int test1()
{
	Function f = display;
	f();

	f = print;
	f();

	return 0;
}

void test2()
{
	//函数的容器
	std::function<void()> f = display;
	f();

	f = print;
	f();

	Example e;
	f = std::bind(&Example::display, e);
	f();
}

void test3()
{
	auto f = std::bind(add, 1, 2);
	cout << "f()=" << f() << endl;
	cout << "f(2)=" << f(2) << endl;
	cout << "f(2,3,4)=" << f(2,3,4) << endl;//无效参数

	//占位符
	auto f2 = std::bind(add, 1, std::placeholders::_1);
	cout << "f2(100)=" << f2(100) << endl;

	auto f3 = std::bind(add, std::placeholders::_1, 10);
	cout << "f3(100)=" << f3(100) << endl;
}

int main()
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}