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
	Base()
	{
		cout << "Base()" << endl;
	}

	~Base() {	cout << "~Base()" << endl;	}
};


//当派生类对象被销毁时，先调用派生类析构函数，然后再自动调用
//基类的析构函数
class Derived
: public Base
{
public:
	Derived(long derived)
	: Base() //基类成员初始化
	, _derived(derived)
	, _pint(new int(100))
	{
		cout << "Derived(long)" << endl;
	}

	~Derived() 
	{	
		cout << "~Derived()" << endl;	
		if(_pint)
			delete _pint;
	}

private:
	int * _pint;
	long _derived;
};
 
int main(void)
{
	Derived derived(10);

	return 0;
}
