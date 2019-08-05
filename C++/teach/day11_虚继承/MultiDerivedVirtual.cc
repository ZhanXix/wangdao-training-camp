 ///
 /// @file    MultiDerivedVirtual.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 15:48:49
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class A
{
public:
	virtual void a() {	cout << "A::a()" << endl;	}
	virtual void b() {	cout << "A::b()" << endl;	}
	virtual void c() {	cout << "A::c()" << endl;	}
};


class B
{
public:
	virtual void a() {	cout << "B::a()" << endl;	}
	virtual void b() {	cout << "B::b()" << endl;	}
	void c() {	cout << "B::c()" << endl;	}
	void d() {	cout << "B::d()" << endl;	}
};

class C
: public A
, public B
{
public:
	virtual void a() {	cout << "C::a()" << endl;	}

	void c() {	cout << "C::c()" << endl;	}
	void d() {	cout << "C::d()" << endl;	}
};
 
int main(void)
{
	C c;
	//c.b();//error

	A * pA = &c;//pA + 1
	pA->a();
	pA->b();
	pA->c();
	cout << endl;

	B * pB = &c;
	pB->a();
	pB->b();
	pB->c();
	pB->d();
	cout << "sizeof(A) = " << sizeof(A) << endl;
	cout << "sizeof(B) = " << sizeof(B) << endl;
	cout << "sizeof(C) = " << sizeof(C) << endl;
	cout << "pA = " << pA << endl;
	cout << "pB = " << pB << endl;
 
	cout << endl;
#if 1
	C * pC = &c;//pC + 1
	cout << "pC = " << pC << endl;
	pC->a();
	//pC->b();//error
	pC->c();
	pC->d();
#endif

	return 0;
}
