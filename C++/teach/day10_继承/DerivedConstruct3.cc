 ///
 /// @file    DerivedConstruct.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 10:50:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//派生类对象的构造: 先对基类成员进行初始化，再对派生类成员初始化
//
//误解: 创建派生类对象时，先调用基类构造函数，再调用派生类构造函数
//
//正确的说法: 创建派生类对象时，先调用派生类构造函数，在执行
//		     派生类构造函数过程中，要调用基类构造函数



class Base
{
public:
	Base()
	{
		cout << "Base()" << endl;
	}

	Base(long base)
	: _base(base)
	{
		cout << "Base(long)" << endl;
	}

	void print() const {	cout << "_base: " << _base << endl;}

private:
	long _base;
};
//对于派生类对象的创建，当派生类有显式定义构造函数时，
//基类成员的初始化，都要放在派生类初始化表达式中进行
class Derived
: public Base
{
public:
	Derived(long derived)
	: Base() //基类成员初始化
	, _derived(derived)
	{
		cout << "Derived(long)" << endl;
	}

	Derived(long base, long derived)
	: Base(base) //显式调用基类有参构造函数
	, _derived(derived)
	{
		cout << "Derived(long,long)" << endl;
	}
	
	void display() const
	{
		print();
		cout << " _derived: " << _derived << endl;
	}

private:
	long _derived;
};
 
int main(void)
{
	Derived derived(10, 11);
	derived.display();

	return 0;
}
