 ///
 /// @file    cow_string.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 15:49:29
 ///
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class CowString
{
	//设计模式之代理模式
	class CharProxy
	{
	public:
		CharProxy(CowString & self, int idx)
		: _self(self)
		, _idx(idx)
		{}

		//CharProxy & operator=(const char & ch);
		//CharProxy & operator=(const CharProxy & rhs);
		//执行写操作
		char & operator=(const char & ch);

		//执行读操作
		operator char() {	
			//cout << "operator char()" << endl;	
			return _self._pstr[_idx]; 
		}
		//friend std::ostream & operator<<(std::ostream & os, const CharProxy & rhs);
	
	private:
		CowString & _self;
		int _idx;
	};
public:
	CowString()
	: _pstr(new char[1 + 4]() + 4)
	{
		initRefcount();
		cout << "CowString()" << endl;
	}

	CowString(const char * pstr)
	: _pstr(new char[strlen(pstr) + 5]() + 4)
	{
		cout << "CowString(const char *)" << endl;
		initRefcount();
		strcpy(_pstr, pstr);
	}

	CowString(const CowString & rhs)
	: _pstr(rhs._pstr)
	{	//O(1)时间复杂度
		cout << "CowString(const CowString & )" << endl;
		increaseRefcount();
	}

	CowString & operator=(const CowString & rhs)
	{	//O(1)时间复杂度
		cout << "CowString & operator=(const CowString &)" << endl;
		if(this != &rhs) {
			release();

			_pstr = rhs._pstr;
			increaseRefcount();
		}
		return *this;
	}

	const char * c_str() const
	{	return _pstr;	}

	int size() const 
	{	return strlen(_pstr);	}


	~CowString()
	{
		release();
	}

	int refcount() const 
	{	return *(int *)(_pstr - 4);	}

	//char & operator[](int idx);
	CharProxy operator[](int idx);

#if 1
	const char & operator[](int idx) const
	{	
		cout << "const char & operator[](int idx) const" << endl;
		return _pstr[idx]; 
	}
#endif
	
	friend std::ostream & operator<<(std::ostream & os, const CowString & rhs);

private:
	void initRefcount()  // ==> 更能表达语义
	{	*(int*)(_pstr - 4) = 1;}

	void increaseRefcount()
	{	++*(int*)(_pstr - 4);}

	void decreaseRefcount()
	{	--*(int*)(_pstr - 4);}

	void release()
	{
		decreaseRefcount();
		if(0 == refcount()) {
			delete [] (_pstr - 4);	
			cout << ">> delete heap data!" << endl;
		}
	}
private:
	char * _pstr;// 指向的字符串的首地址
};
 
std::ostream & operator<<(std::ostream & os, const CowString & rhs)
{
	os << rhs._pstr;
	return os;
}


CowString::CharProxy CowString::operator[](int idx)
{
	return CharProxy(*this, idx);
}

//写操作
//CowString::CharProxy & CowString::CharProxy::operator=(const char & ch)
char & CowString::CharProxy::operator=(const char & ch)
{
	if(_idx >=0 && _idx < _self.size()) {
		if(_self.refcount() > 1) {
			_self.decreaseRefcount();
			
			char * ptmp = new char[_self.size() + 5]() + 4;
			strcpy(ptmp, _self._pstr);
			_self._pstr = ptmp;
			_self.initRefcount();
		}
		_self._pstr[_idx] = ch;
		return _self._pstr[_idx];
	} else {
		static char nullchar = '\0';
		return nullchar;
	}
}

//只要字符串的引用计数大于1， 就会进行深拷贝
// 
//问题：下标访问运算符无法区分出接下来的操作是读操作还是写操作
//
//
#if 0
char & CowString::operator[](int idx)
{
	if(idx >=0 && idx < size()) {
		if(refcount() > 1) {
			decreaseRefcount();
			
			char * ptmp = new char[size() + 5]() + 4;
			strcpy(ptmp, _pstr);
			_pstr = ptmp;
			initRefcount();
		}
		return _pstr[idx];
	} else {
		static char nullchar = '\0';
		return nullchar;
	}
}
#endif

void func(const CowString & str)
{
	cout << str[0] << endl;
}


int main(void)
{
	CowString s1 = "hello,world";

	//CowString s2 = "hello,world";
	CowString s2 = s1;

	CowString s3 = "shenzhen";
	cout << "s3 = " << s3 << endl;
	s3 = s1;
 
	cout << "执行赋值操作之后:" << endl;
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	printf("s1's address is %p\n", s1.c_str());
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	cout << "s1's refcount = " << s1.refcount() << endl;
	cout << "s2's refcount = " << s2.refcount() << endl;
	cout << "s3's refcount = " << s3.refcount() << endl;

	cout << "\n 修改共享字符串的内容之后:" << endl;
	s3[0] = 'X';
				// CharProxy = char;
				// CharProxy ch;
				// ch.operaotr=(char);
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	printf("s1's address is %p\n", s1.c_str());
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	cout << "s1's refcount = " << s1.refcount() << endl;
	cout << "s2's refcount = " << s2.refcount() << endl;
	cout << "s3's refcount = " << s3.refcount() << endl;

	cout << "\n 执行读操作之后:" << endl;
	cout << "s1[0] = " << s1[0] << endl;//CharProxy ==> char
	// cout << CharProxy
	cout << "s1 = " << s1 << endl;
	cout << "s2 = " << s2 << endl;
	cout << "s3 = " << s3 << endl;
	printf("s1's address is %p\n", s1.c_str());
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	cout << "s1's refcount = " << s1.refcount() << endl;
	cout << "s2's refcount = " << s2.refcount() << endl;
	cout << "s3's refcount = " << s3.refcount() << endl;

	return 0;
}
