// 测试一：单个虚继承，不带虚函数
//	虚继承与继承的区别
//	１.　多了一个虚基指针
//	２.　虚基类位于派生类存储空间的最末尾

// 测试二：单个虚继承，带虚函数
//   1.如果派生类没有自己的虚函数，此时派生类对象不会产生
//　   虚函数指针
//   2.如果派生类拥有自己的虚函数，此时派生类对象就会产生自己本身的虚函数指针，
//     并且该虚函数指针位于派生类对象存储空间的开始位置
//

#pragma vtordisp(off)
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	A() : _ia(10) {}

	virtual
	void f()
	{
		cout << "A::f()" << endl;
	}
private:
	int _ia;
};

class B
: virtual public A
{
public:
	B() : _ib(20) {}

	void fb()
	{
		cout << "A::fb()" << endl;
	}


	/*virtual*/ void f()
	{
		cout << "B::f()" << endl;
	}

	virtual void fb2()
	{
		cout << "B::fb2()" << endl;
	}

private:
	int _ib;
};

int main(void)
{
	cout << sizeof(A) << endl;
	cout << sizeof(B) << endl;
	B b;
	return 0;
}