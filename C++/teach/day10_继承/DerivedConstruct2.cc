 ///
 /// @file    DerivedConstruct.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 10:50:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
#if 1
	Base()
	{
		cout << "Base()" << endl;
	}
#endif

	Base(long base)
	: _base(base)
	{	cout << "Base(long)" << endl;	}

	void print() const 
	{	cout << "Base::_base = " << _base << endl;}

private:
	long _base;
};


//对于派生类对象的创建，当派生类没有显式定义构造函数时，
//不管基类是什么情况，基类必须要提供一个默认构造函数
	

class Derived
: public Base
{
public:
	Derived()
	//: Base()
	{
		cout << "Derived()" << endl;
	}

private:
	long _derived;
};
 
int main(void)
{
	Derived derived;

	return 0;
}
