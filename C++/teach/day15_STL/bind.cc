#include <iostream>
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

//º¯ÊýÀàÐÍ
typedef void(*Function)();

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

int main()
{
	test0();
	test1();
	return 0;
}