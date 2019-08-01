 ///
 /// @file    VirtualFunction1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 15:51:02
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	//virtual //构造函数不能设计成虚函数
	Base(long base)
	: _base(base)
	{}
	
	//1. 虚函数的实现:
	//当基类定义了虚函数之后，在其存储布局的开始位置会多一个
	//虚函数指针, 该虚函数指针指向了一张虚函数表，虚函数表中
	//存放的是虚函数的入口地址
	//
	//2. 虚函数(动态多态)机制被激活的条件:
	//> a. 基类有定义虚函数，派生类覆盖基类虚函数
	//> b. 创建派生类对象
	//> c. 用基类的指针或者引用指向派生类对象
	//> d. 用基类指针或者引用调用虚函数
	virtual 
	void print() const 
	{
		cout << ">> _base = " << _base << endl;
	}


private:
	long _base;
};

class Derived
: public Base
{
public:
	Derived(long base, long derived)
	: Base(base)
	, _derived(derived)
	{}

	//当基类定义了虚函数时，如果派生类重定义虚函数，
	//即使没有显式加上virtual关键字，也是虚函数
	//
	//如果派生类要覆盖基类的虚函数，必须要与基类的虚函数
	//在形式上保持一致
	//
#if 1
	//virtual 
	void print() const
	{
		cout << ">> _derived = " << _derived << endl;
	}
#endif

	virtual 
	void print(int x) const
	{
		cout << " x = " << x << endl;
	}
private:
	long _derived;
};

class GrandSon
: public Derived
{

};

class Derived2
: public Base
{
public:
	Derived2(long base, long derived)
	: Base(base)
	, _derived2(derived)
	{}

	//virtual 
	void print() const
	{
		cout << ">> _derived2 = " << _derived2 << endl;
	}

private:
	long _derived2;
};

void print(Base * base)
{
	base->print();
	//base->print(1);//error
}

void print(Base & ref)
{
	ref.print();
}

 
int main(void)
{
	cout << "sizeof(Base) = " << sizeof(Base) << endl;
	cout << "sizeof(Derived) = " << sizeof(Derived) << endl;
	cout << "sizeof(Derived2) = " << sizeof(Derived2) << endl;

	Base base(1);
	Derived derived(11, 12);
	Derived2 derived2(21, 22);

	print(&base);
	print(&derived);
	print(&derived2);
 
	cout << endl;
	print(base);
	print(derived);
	print(derived2);
	return 0;
}
