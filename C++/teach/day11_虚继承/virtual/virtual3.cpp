#pragma vtordisp(off)
#include <iostream>

// 测试三：多重继承（带虚函数）
//　１.　每个基类都有自己的虚函数表
//  ２.　派生类如果有自己的虚函数，会被加入到第一个虚函数表之中
//	３.  内存布局中，　其基类的布局按照基类被声明时的顺序进行排列
//　４.　派生类会覆盖基类的虚函数，只有第一个虚函数表中存放的是
//		真实的被覆盖的函数的地址；其它的虚函数表中存放的并不是真实的
//		对应的虚函数的地址，而只是一条跳转指令

using std::cout;
using std::endl;

class Base1
{
public:
	Base1() : _iBase1(10) {}
	virtual void f()
	{
		cout << "Base1::f()" << endl;
	}

	virtual void g()
	{
		cout << "Base1::g()" << endl;
	}

	virtual void h()
	{
		cout << "Base1::h()" << endl;
	}
private:
	int _iBase1;
};

class Base2
{
public:
	Base2() : _iBase2(100) {}
	virtual void f()
	{
		cout << "Base2::f()" << endl;
	}

	virtual void g()
	{
		cout << "Base2::g()" << endl;
	}

	virtual void h()
	{
		cout << "Base2::h()" << endl;
	}
private:
	int _iBase2;
};

class Base3
{
public:
	Base3() : _iBase3(1000) {}
	virtual void f()
	{
		cout << "Base3::f()" << endl;
	}

	virtual void g()
	{
		cout << "Base3::g()" << endl;
	}

	virtual void h()
	{
		cout << "Base3::h()" << endl;
	}
private:
	int _iBase3;
};


class Derived
	: virtual public Base1
	, public Base2
	, public Base3
{
public:
	Derived() : _iDerived(10000) {}
	void f()
	{
		cout << "Derived::f()" << endl;
	}

	virtual void g1()
	{
		cout << "Derived::g1()" << endl;
	}

private:
	int _iDerived;
};

int main(void)
{
	Derived d;
	Base2 * pBase2 = &d;
	Base3 * pBase3 = &d;
	Derived * pDerived = &d;

	pBase2->f();
	cout << "sizeof(d) = " << sizeof(d) << endl;

	cout << "&Derived = " << &d << endl;   // 这三个地址值是不一样的
	cout << "pBase2 = " << pBase2 << endl; //
	cout << "pBase3 = " << pBase3 << endl; //

	return 0;
}
