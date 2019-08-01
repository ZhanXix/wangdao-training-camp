 ///
 /// @file    String.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-31 09:36:24
 ///
 
#include <stdio.h>

#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector; 
class String
{
public:
	String()=default;
	//String()
	//: _pstr(nullptr)
	//{}

	String & operator=(const char *);
	void print() const
	{
		printf("_pstr = %p\n", _pstr);	
		cout << _pstr << endl;
	}

	friend std::istream & operator>>(std::istream & is, String & rhs);

private:
	char * _pstr = nullptr;
};
 
std::istream & operator>>(std::istream & is, String & rhs)
{
	vector<char> buff;
	buff.reserve(65535);

	char ch ;
	while((ch = is.get()) != '\n') {
		buff.push_back(ch);
	}

	rhs = &buff[0];
	
	return is;
}

int main(void)
{
	String s1;
	s1.print();

	String s2("hello");

	String s3("world");

	//s2 = s3;
	s2.operator=(s3);

	//s2 = s2;
	//s2.operator=(s2);

	return 0;
}
