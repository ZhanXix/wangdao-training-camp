 ///
 /// @file    PureVirtualFunction.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 11:39:49
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	//定义了纯虚函数的类称为抽象类
	//纯虚函数的特点：没有实现，作为接口存在
	//
	//开闭原则: 对修改关闭，对扩展开放
	//
	virtual void display()=0;
	virtual void print()=0;
};

class Child1
: public Base
{
public:
	//派生类继承基类之后，当基类中有多个纯虚函数时，
	//派生类必须实现所有的纯虚函数，此时才能正常创建对象
	//
	//只要有一个纯虚函数没有实现，该派生类也会成为抽象类
	void display() override
	{
		cout << "Child1::display()" << endl;
	}
};


class Child2
: public Child1
{
public:
	void print() override
	{
		cout << "Child2::print()" << endl;
	}
};

 
int main(void)
{
	//Base base;//error
	//Child1 child1;//error
	Child2 child2;

	//Base * pbase = &child1;
	Base * pbase = &child2;
	pbase->display();
	pbase->print();

	return 0;
}
