/*实现基本的COW(Copy On Write)的CowString*/

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class CowString
{
public:
	//构造
	CowString()
		: _pstr(new char[4 + 1]() + 4)
	{
		cout << "CowString()" << endl;
		Init_RefCount();
	}

	CowString(const char* pstr)
		: _pstr(new char[4 + strlen(pstr) + 1]() + 4)
	{
		cout << "CowString(const char*)" << endl;
		Init_RefCount();
		strcpy(_pstr, pstr);
	}

	CowString(const CowString& rhs)
		: _pstr(rhs._pstr)
	{
		cout << "CowString(const CowString&)" << endl;
		Increase_RefCount();//增加计数
	}

	//析构
	~CowString()
	{
		cout << "~CowString()" << endl;
		Release_CowString();
	}

	//得到数据
	int get_refcount() const
	{
		return *(int*)(_pstr - 4);
	}

	int get_size() const
	{
		return strlen(_pstr);
	}

	const char* c_str() const
	{
		return _pstr;
	}

	//运算符
	CowString& operator=(const CowString& rhs)
	{
		cout << "CowString& operator=(const CowString&)" << endl;
		if (this != &rhs) {
			Release_CowString();
			_pstr = rhs._pstr;
			Increase_RefCount();
		}
		return *this;
	}

	friend std::ostream& operator<<(std::ostream&, const CowString&);

private:
	void Init_RefCount()	//初始化引用计数
	{
		*(int*)(_pstr - 4) = 1;
	}

	void Reduce_RefCount()
	{
		--(*(int*)(_pstr - 4));
	}

	void Increase_RefCount()
	{
		++(*(int*)(_pstr - 4));
	}

	void Release_CowString()
	{
		Reduce_RefCount();
		if (0 == get_refcount()) {
			delete[](_pstr - 4);
			cout << "delete[](_pstr - 4)" << endl;
		}
	}

	//private data
	char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const CowString& rhs)
{
	os << rhs._pstr;
	return os;
}

int main()
{
	cout << ">> s1 = Welcome!" << endl;
	CowString s1 = "Welcome!";
	cout << "s1 = " << s1 << endl;
	cout << "s1.refcount = " << s1.get_refcount() << endl;

	cout << endl << ">> s2 = Welcome!" << endl;
	CowString s2 = "Welcome!";
	cout << "s2 = " << s2 << endl;
	cout << "s1.refcount = " << s1.get_refcount() << endl;
	cout << "s2.refcount = " << s2.get_refcount() << endl;

	cout << endl << ">> s3 = s1" << endl;
	CowString s3 = s1;
	cout << "s3 = " << s3 << endl;
	cout << "s1.refcount = " << s1.get_refcount() << endl;
	cout << "s2.refcount = " << s2.get_refcount() << endl;
	cout << "s3.refcount = " << s3.get_refcount() << endl;

	cout << endl << ">> s2 = s1" << endl;
	s2 = s1;
	cout << "s2 = " << s2 << endl;
	cout << "s1.refcount = " << s1.get_refcount() << endl;
	cout << "s2.refcount = " << s2.get_refcount() << endl;
	cout << "s3.refcount = " << s3.get_refcount() << endl;

	cout << endl << ">> s3 = Hello!" << endl;
	s3 = "Hello!";
	cout << "s2 = " << s2 << endl;
	cout << "s1.refcount = " << s1.get_refcount() << endl;
	cout << "s2.refcount = " << s2.get_refcount() << endl;
	cout << "s3.refcount = " << s3.get_refcount() << endl;
	
	cout << endl << ">> return" << endl;
	return 0;
}
