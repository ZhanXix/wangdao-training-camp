 ///
 /// @file    DerivedCopyControl.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 14:50:18
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Base
{
public:
	Base(const char * data1)
	: _data1(new char[strlen(data1) + 1]())
	{
		strcpy(_data1, data1);
		cout << "Base(const char * data1)" << endl;
	}

	Base(const Base & rhs)
	: _data1(new char[strlen(rhs._data1) + 1]())
	{
		cout << "Base(const Base &)" << endl;
		strcpy(_data1, rhs._data1);
	}

	Base & operator=(const Base & rhs)
	{
		cout << "Base & operator=(const Base & rhs)" << endl;
		if(this != &rhs) {
			delete [] _data1;

			_data1 = new char[strlen(rhs._data1) + 1]();
			strcpy(_data1, rhs._data1);
		}
		return *this;
	} 

	~Base()
	{
		cout << "~Base()" << endl;
		delete [] _data1;
	}

	friend std::ostream & operator<<(std::ostream & os, const Base & rhs);
private:
	char * _data1;
};

std::ostream & operator<<(std::ostream & os, const Base & rhs)
{
	os << rhs._data1;
	return os;
}

//1. 当派生类部分没有显式定义复制控制函数，基类有显式定义
//   复制控制函数，当执行派生类对象的复制控制操作时，会
//   自动调用基类相应的复制控制函数

class Derived
: public Base
{
public:
	Derived(const char * data)
	: Base(data)
	{
		cout << "Derived(const char *)" << endl;
	}


	~Derived()
	{	cout << "~Derived()" << endl;	}	
};

 
int main(void)
{
	Derived d1("hello");
	cout << "d1 = " << d1 << endl;

	Derived d2 = d1;//自动调用基类的拷贝构造函数，完成基类部分的复制
	cout << "d2 = " << d1 << endl << endl;
 
	Derived d3("world");
	cout << "d3 = " << d3 << endl;

	d3 = d1;
	cout << "d3 = " << d3 << endl;


	return 0;
}
