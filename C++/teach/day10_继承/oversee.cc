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
	Base(long data)
	: _data(data)
	{
		cout << "Base(long)" << endl;
	}

	void print(int x) const 
	{	
		cout << "Base::_data: " << _data << ", x : " << x << endl;
	}

protected:
	long _data;
};

class Derived
: public Base
{
public:
	Derived(long base, long derived)
	: Base(base) //显式调用基类有参构造函数
	, _data(derived)
	{
		cout << "Derived(long,long)" << endl;
	}
	
	void display() const
	{
		cout << "_data:" << Base::_data << endl;
		cout << "Derived::_data " << _data << endl;//隐藏基类同名成员
	}

	void print() const//基类同名成员函数也会被派生类隐藏起来
	{				  //即使参数不同，也会被隐藏
		cout << "Derived::_data " << _data << endl;//隐藏基类同名成员
	}

private:
	long _data;
};
 
int main(void)
{
	Derived derived(10, 11);
	//derived.display();
	derived.print();
	//derived.print(100);//基类函数无法直接调用, oversee
	derived.Base::print(100);//如果通过派生类对象就要调用基类同名函数
			                 //则必须要加上基类类名进行调用

	return 0;
}
