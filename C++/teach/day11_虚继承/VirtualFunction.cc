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
	virtual void display(int x = 0) const
	{
		cout << "_base " << _base << ", x = " << x << endl;
	}

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

	virtual void display(int x = 1) const
	{
		cout << "_derived = " << _derived << ", x = " << x << endl;
	}

private:
	long _derived;
};
 
int main(void)
{
	//Base base(1);//error
	Derived derived(1, 2);
	Base * pbase = &derived;
	pbase->display();//在编译时，传递默认过去,由于pbase是Base类型
					 //所以默认参数用的是0， 而不是1
 
	return  0;
}
