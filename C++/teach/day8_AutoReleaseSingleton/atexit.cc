 ///
 /// @file    atexit.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 14:33:31
 ///
 
#include <stdlib.h>

#include <iostream>
using std::cout;
using std::endl;

void display()
{
	cout << "display() " << endl;
}
 
int main(void)
{
	cout << "enter main function..." << endl;
	::atexit(display);
	::atexit(display);
 
	cout << "exit main function..." << endl;
	return 0;
}
