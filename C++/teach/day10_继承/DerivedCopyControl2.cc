 ///
 /// @file    DerivedCopyControl.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 14:50:18
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class Noncopyable
{
protected:
	Noncopyable(){}
	~Noncopyable() {}

	Noncopyable(const Noncopyable & )=delete;
	Noncopyable & operator=(const Noncopyable &)=delete;
};



class Base
: Noncopyable
{
public:
	Base(const char * data1)
	: _data1(new char[strlen(data1) + 1]())
	{
		strcpy(_data1, data1);
		cout << "Base(const char * data1)" << endl;
	}

#if 0
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
#endif

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

//2. 当派生类部分显式定义复制控制函数，基类有显式定义
//   复制控制函数，当执行派生类对象的复制控制操作时，不会
//   自动调用基类相应的复制控制函数, 必须手动调用

class Derived
: public Base
{
public:
	Derived(const char * data1, const char * data2)
	: Base(data1)
	, _data2(new char[strlen(data2) + 1])
	{
		cout << "Derived(const char *)" << endl;
		strcpy(_data2, data2);
	}

	//Derived(const Derived & rhs) = delete;
	//Derived & operator=(const Derived & rhs) = delete;

#if 0
	Derived(const Derived & rhs)
	: Base(rhs) //显式调用
	, _data2(new char[strlen(rhs._data2) + 1]())
	{
		cout << "Derived(const Derived &)" << endl;
		strcpy(_data2, rhs._data2);
	}

	Derived & operator=(const Derived & rhs)
	{
		cout << "Derived & operator=(const Derived &)" << endl;
		if(this != &rhs) {
			Base::operator=(rhs);//显式调用基类赋值函数
			delete [] _data2;

			_data2 = new char[strlen(rhs._data2) + 1]();
			strcpy(_data2, rhs._data2);
		}
		return *this;
	}
#endif

	~Derived()
	{	
		cout << "~Derived()" << endl;	
		delete [] _data2;
	}	

	friend std::ostream & operator<<(std::ostream & os, const Derived & rhs);
private:
	char * _data2;
};

std::ostream & operator<<(std::ostream & os, const Derived & rhs)
{
	const Base & ref = rhs;
	os << "Base: " << ref << ",";
	os << "Derived:" << rhs._data2;
	return os;
}
 
int main(void)
{
	Derived d1("hello", "world");
	cout << "d1 = " << d1 << endl;

	Derived d2 = d1;//自动调用基类的拷贝构造函数，完成基类部分的复制
	cout << "d2 = " << d1 << endl << endl;
 
#if 1
	Derived d3("shenzhen", "wangdao");
	cout << "d3 = " << d3 << endl;

	d3 = d1;
	cout << "d3 = " << d3 << endl;
#endif


	return 0;
}
