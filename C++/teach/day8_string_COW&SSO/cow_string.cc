/*最简单的深拷贝就是直接new一个对象，然后把数据复制一遍，不过这样做效率很低，STL中对此进行了优化，
对string的实现有两种不同的优化策略，即COW(Copy On Write)和SSO(Small String Optimization)*/
 
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;


class CowString
{
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
	{
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

	char & operator[](int idx);

#if 1
	const char & operator[](int idx) const
	{	
		cout << "const char & operator[](int idx) const" << endl;
		return _pstr[idx]; 
	}
#endif
	
	friend std::ostream & operator<<(std::ostream & os, const CowString & rhs);

private:
	void initRefcount()
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
	char * _pstr;
};
 
std::ostream & operator<<(std::ostream & os, const CowString & rhs)
{
	os << rhs._pstr;
	return os;
}

//只要字符串的引用计数大于1， 就会进行深拷贝
// 
//问题：下标访问运算符无法区分出接下来的操作是读操作还是写操作
//
//
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
	cout << "s1[0] = " << s1[0] << endl;
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
