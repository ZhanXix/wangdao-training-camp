 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 09:54:40
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	} 

	operator int()
	{
		cout << "operator int()" << endl;
		return _ix * _iy;
	}

#if 0
	operator double()
	{
		return _ix + _iy;
	}
#endif

private:
	int _ix;
	int _iy;
};
 
int main(void)
{
	Point pt1(12, 11);
	cout << "pt1 = " << pt1 << endl;
 
	return 0;
}
