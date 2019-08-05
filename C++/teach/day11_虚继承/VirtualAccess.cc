 ///
 /// @file    VirtualAccess.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 10:55:55
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base()=default;

	Base(long base)
	: _base(base)
	{
		cout << "Base(long)" << endl;
	}
	
	//成员函数内部调用虚函数，会展现动态多态特性
	void func1() 
	{
		this->display();
	}

	void func2()
	{
		Base::display();
	}

	virtual void display() const
	{
		cout << " _base = " << _base << endl;
	}

//private:
protected:
	long _base = 0;
};

class Derived
: public Base
{
public:
	Derived(long base, long derived)
	: Base(base)
	//: _base(base)  //error
	, _derived(derived)
	{}

	void display() const override
	{
		cout << "_derived = " << _derived << endl;
	}

private:
	long _derived;
};
 
int main(void)
{
	Base base(1);
	base.func1();

	Derived derived(11, 12);
	derived.func1();

	cout << endl;
	base.func2();
	derived.func2();

	return 0;
}
