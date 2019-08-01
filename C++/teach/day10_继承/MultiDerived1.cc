 ///
 /// @file    MultiDerived1.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 10:11:42
 ///
 
#include <iostream>
using std::cout;
using std::endl;


class A
{
public:
	void print() const {	cout << "A::print()" << endl;	}
};

class B
{
public:
	void print() const {	cout << "B::print()" << endl;	}
};

class C
{
public:
	void print() const {	cout << "C::print()" << endl;	}
};

class D
: public A
, public B
, public C
{};

 
int main(void)
{
	D d;
	//d.print();//成员名访问冲突的二义性
	d.A::print();
	d.B::print();
	d.C::print();
 
	return 0;
}
