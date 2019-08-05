//#include "add.h"

#include <iostream>
using std::cout;
using std::endl;

template <class T>
T add(T x, T y)
{
	return x + y;
}

#if 0
void test1()
{
	int d1 = 1, d2 = 2;
	cout << "add(d1, d2) = " << add(d1, d2) << endl;
}
#endif
