 ///
 /// @file    DerivedConstruct.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 10:50:00
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	void print() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")";
	}

	~Point() {	cout << "~Point()" << endl;	}

private:
	int _ix;
	int _iy;
};

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
	Derived(long derived, int ix, int iy)
	: Base() //基类成员初始化
	, _pt(ix, iy)
	, _pint(new int(100))
	, _derived(derived)
	{
		cout << "Derived(long)" << endl;
	}

	void print() const
	{
		_pt.print();
		cout << "*_pint = " << *_pint << endl;
		cout << "_derived = " << _derived << endl;
	}

	~Derived() 
	{	
		cout << "~Derived()" << endl;	
		if(_pint)
			delete _pint;
	}

private:
	Point _pt;
	int * _pint;
	long _derived;
};
 
int main(void)
{
	Derived derived(10, 1, 2);
	derived.print();

	return 0;
}
