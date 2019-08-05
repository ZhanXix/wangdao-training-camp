 ///
 /// @file    VirtualAccess2.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 11:06:41
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Grandpa
{
public:
	Grandpa(long d1)
	: _d1(d1)
	{	
		cout << "Grandpad(long)" << endl;
	}

	virtual
	void func1() {	cout << "Grandpa::func1()" << endl;}
	virtual
	void func2() {	cout << "Grandpa::func2()" << endl;}

	~Grandpa() {	cout << "~Grandpa()" << endl;	}

private:
	long _d1;
};

class Son
: public Grandpa
{
public:
	Son(long d1, long d2)
	: Grandpa(d1)
	, _d2(d2)
	{	
		cout << "Son(long)" << endl;
		func1();//静态联编
	}

#if 0
	virtual
	void func1() {	cout << "Son::func1()" << endl;}
	virtual
	void func2() {	cout << "Son::func2()" << endl;}
#endif

	~Son()
	{
		cout << "~Son()" << endl;
		func2();//静态联编, 不会展现动态多态特性
	}

private:
	long _d2;
};

class GrandSon
: public Son
{
public:
	GrandSon(long d1, long d2, long d3)
	: Son(d1, d2)
	, _d3(d3)
	{
		cout << "GrandSon()" << endl;
	}


	virtual
	void func1() {	cout << "GrandSon::func1()" << endl;}
	virtual
	void func2() {	cout << "GrandSon::func2()" << endl;}

	~GrandSon() {	cout << "~GrandSon()" << endl;	}

private:
	long _d3;
};
 
int main(void)
{
	GrandSon gs(1, 2, 3);
 
	return 0;
}
