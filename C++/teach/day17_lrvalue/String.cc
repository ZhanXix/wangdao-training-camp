#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class String
{
public:
	String()
		: _pstr(new char[1]())
	{
		cout << "String()" << endl;
	}

	String(const char* pstr)
		:_pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char*)" << endl;
		strcpy(_pstr, pstr);
	}

	//当const左值引用作为一个形参，无法区分出来传递过来的实参是左值还是右值
	//
	//具有复制控制语义的函数
	//复制构造函数
	String(const String& rhs)
		: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String&)" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	//赋值运算符函数
	String& operator=(const String& rhs)
	{
		cout << "String& operator=(const String&)" << endl;
		if (this != &rhs) {
			delete[] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	//具有移动语义的函数，执行要优先于具有复制控制语义函数的执行（使用右值时就调移动语义的函数）
	//移动构造函数
	String(String&& rhs)
		: _pstr(rhs._pstr) //使用浅拷贝，完成转移
	{
		cout << "String(String&&)" << endl;
		rhs._pstr = nullptr;
	}

	//移动赋值函数
	String& operator=(String&& rhs)
	{
		cout << "String& operator=(String&&)" << endl;
		delete[] _pstr;
		_pstr = rhs._pstr;
		rhs._pstr = nullptr;
		return *this;
	}

	~String()
	{
		cout << "~String()" << endl;
		if (_pstr) {
			delete[] _pstr;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const String& rhs);

private:
	char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	os << rhs._pstr;
	return os;
}

String str("hello,world");

//当函数的返回值是对象时：如果返回的对象是一个
//局部（即将被销毁的）对象，执行return语句时，
//会调用移动构造函数；当返回的对象其声明周期是
//大于函数时，执行return语句时，会调用复制构造
//函数
String getString()
{
	String str("hello,world");
	cout << "strs =" << str << endl;
	return str;
}

int test0()
{
	vector<String> strs;
	strs.push_back("hello,world");
	cout << "strs[0] = " << strs[0] << endl << endl;

	String s1 = "hello";
	s1 = String("world");

	String s2 = "shenzhen";
	cout << "s2 = " << s2 << endl;
	//&s2;
	s1 = std::move(s2);//显式将一个左值转换成右值
						//一般表示在该语句之后，不会再使用该对象
	cout << "s1 = " << s2 << endl;
	//cout << "s2 = " << s2 << endl;//error
	cout << "......" << endl;

	return 0;
}

void test1()
{
	getString();
}

//右值引用是一个右值
String&& func()
{
	String str("hello");
	return std::move(str);
}

int main()
{
	test1();
	//func();//右值

	return 0;
}