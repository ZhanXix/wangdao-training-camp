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
	Base(long base)
	: _base(base)
	{
		cout << "Base(long)" << endl;
	}

	virtual void func1() {	cout << "Base::func1()" << endl;	} 
	virtual void func2() {	cout << "Base::func2()" << endl;	} 
	virtual void func3() {	cout << "Base::func3()" << endl;	} 

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

private:
	long _derived;
};
 
int main(void)
{
	//验证虚函数表的存在
	Base base(10);
	cout << "sizeof(Base) = " << sizeof(Base) << endl;

	long * p = (long*)&base;
	cout << p[0] << endl;
	cout << p[1] << endl;

	typedef void (*Function)(void);

	long * p2 = (long*)p[0];
	Function f = (Function)p2[0];
	f();
	f = (Function)p2[1];
	f();
	f = (Function)p2[2];
	f();
	return  0;
}
