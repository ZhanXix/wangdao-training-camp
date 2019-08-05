#include "add.h"
#include <iostream>
using std::cout;
using std::endl;

void test0()
{
	int a = 3, b = 4;
	cout << "add(a, b) = " << add(a, b) << endl;
}

int main()
{
	test0();
	return 0;
}