 ///
 /// @file    AbstractClass.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 14:46:48
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Base
{
public:
	Base(const char * base)
	: _pbase(new char[strlen(base) + 1]())
	{
		cout << "Base(long)" << endl;
		strcpy(_pbase, base);
	}

	virtual void display() const
	{
		cout << "_pbase " << _pbase << endl;
	}

	//析构函数只有一个
	//
	//当某一个类中定义了一个虚函数时，都要将其析构函数设为虚函数
	//

	virtual
	~Base() 
	{
		if(_pbase)
			delete [] _pbase;
		cout << "~Base()" << endl;
	}

private:
	char * _pbase;
};

class Derived
: public Base
{
public:
	Derived(const char * base, const char * derived)
	: Base(base)
	, _pderived(new char[strlen(derived) + 1]())
	{
		cout << "Derived(long,long)" << endl;
		strcpy(_pderived, derived);
	}

	//virtual 
	void display() const
	{
		cout << "_pderived = " << _pderived << endl;
	}

	//当基类析构函数设置为虚函数之后，其派生类析构函数会
	//自动成为虚函数，会将其加入虚函数表中，即使没有加上virtual
	//
	//如果接下来要调用析构函数，就会走虚函数的机制
	//virtual
	~Derived()
	{
		if(_pderived)
			delete [] _pderived;
		cout << "~Derived()" << endl;
	}


private:
	char * _pderived;
};
 
int main(void)
{
	Base * pbase = new Derived("hello", "world");
	pbase->display();

	delete pbase;//
 
	return  0;
}
