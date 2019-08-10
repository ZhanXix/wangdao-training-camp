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
	String(const String& rhs)
		: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String&)" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	String(String&& rhs)
		: _pstr(rhs._pstr) //使用浅拷贝，完成转移
	{
		cout << "String(String&&)" << endl;
		rhs._pstr = nullptr;
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

int main()
{
	vector<String> strs;
	strs.push_back("hello,world");

	return 0;
}