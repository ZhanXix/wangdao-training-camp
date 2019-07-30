 ///
 /// @file    sso_string.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 15:11:45
 ///
 
#include <stdio.h>
#include <iostream>
#include <string>
using std::cout;
using std::endl;
using std::string;
 
int main(void)
{
	int a = 1;
	string s1 = "hello";
	string s2 = "hello,worldaaaa";
	string s3 = "fjaslkfdjslakjfklasdjfklsadjfklfjaljfklsadjfklsdjflkjskfsaklfjklsdjfkljsadklfsklfjlskadflksajf";
	int * pint = new int(1);

	string s4 = s3;

	cout << "sizeof(s1) = " << sizeof(s1) << endl;
	cout << "sizeof(s2) = " << sizeof(s2) << endl;
	cout << "sizeof(s3) = " << sizeof(s3) << endl;
	printf("&a = %p\n", &a);
	printf("pint = %p\n", pint);
	printf("s1's address is %p\n", s1.c_str());
	printf("s2's address is %p\n", s2.c_str());
	printf("s3's address is %p\n", s3.c_str());
	printf("s4's address is %p\n", s4.c_str());
 

	return 0;
}
