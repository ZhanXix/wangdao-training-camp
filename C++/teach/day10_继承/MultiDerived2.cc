 ///
 /// @file    MultiDerived2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 10:16:23
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	void print() const {	cout << _a << endl;}

private:
	long _a;
};

class B
: virtual public A
{
};

class C
: virtual public A
{};

class D
: public B
, public C
{};
 
int main(void)
{
	cout << "sizeof(A) = " << sizeof(A) << endl;
	cout << "sizeof(B) = " << sizeof(B) << endl;
	cout << "sizeof(C) = " << sizeof(C) << endl;
	cout << "sizeof(D) = " << sizeof(D) << endl;
	D d;
	d.print();//存储二义性问题: 采用虚拟继承
	d.B::print();
	d.C::print();
	d.A::print();
 
}
