#pragma vtordisp(off)
#include <iostream>

// �����������ؼ̳У����麯����
//����.��ÿ�����඼���Լ����麯����
//  ��.��������������Լ����麯�����ᱻ���뵽��һ���麯����֮��
//	��.  �ڴ沼���У��������Ĳ��ְ��ջ��౻����ʱ��˳���������
//����.��������Ḳ�ǻ�����麯����ֻ�е�һ���麯�����д�ŵ���
//		��ʵ�ı����ǵĺ����ĵ�ַ���������麯�����д�ŵĲ�������ʵ��
//		��Ӧ���麯���ĵ�ַ����ֻ��һ����תָ��

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

	cout << "&Derived = " << &d << endl;   // ��������ֵַ�ǲ�һ����
	cout << "pBase2 = " << pBase2 << endl; //
	cout << "pBase3 = " << pBase3 << endl; //

	return 0;
}
