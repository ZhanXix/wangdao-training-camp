 ///
 /// @file    AbstractClass.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 14:46:48
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	virtual void display() const
	{
		cout << "_base " << _base << endl;
	}
protected://定义了protected型构造函数的类称为抽象类
//private:
	Base(long base)
	: _base(base)
	{
		cout << "Base(long)" << endl;
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
	{
		cout << "Derived(long,long)" << endl;
	}

	virtual void display() const
	{
		cout << "_derived = " << _derived << endl;
	}


private:
	long _derived;
};
 
int main(void)
{
	//Base base(1);//error
	Derived derived(1, 2);
	Base * pbase = &derived;
	pbase->display();
 
	return  0;
}
