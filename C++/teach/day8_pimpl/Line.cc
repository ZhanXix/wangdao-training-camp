 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 09:54:40
 ///
 
#include "Line.h"
#include <iostream>
using std::cout;
using std::endl;

class Line::LineImpl//外部类
{
	class Point//内部类Point只为Line进行服务
	{
	public:
		Point(int ix = 0, int iy = 0)
		: _ix(ix)
		, _iy(iy)
		{
			cout << "Point(int,int)" << endl;
		} 

		void print() const 
		{
			cout << "(" << _ix
				 << "," << _iy
				 << ")";
		}

		~Point() {	cout << "~Point()" << endl;}

	private:
		int _ix;
		int _iy;
	};

public:
	LineImpl(int x1, int y1, int x2, int y2)
	: _pt1(x1, y1)
	, _pt2(x2, y2)
	{	cout << "LineImpl(int,int,int,int)" << endl;}

	~LineImpl() {	cout << "~LineImpl()" << endl;	}

	void printLine() const;
private:
	Point _pt1;
	Point _pt2;
};

Line::Line(int x1, int y1, int x2, int y2)
: _pimpl(new LineImpl(x1, y1, x2, y2))
{
	cout << "Line(...)" << endl;
}

Line::~Line()
{
	if(_pimpl)
		delete _pimpl;
	cout << "~Line()" << endl;
}

void Line::printLine() const
{
	_pimpl->printLine();
}
 
void Line::LineImpl::printLine() const
{
	_pt1.print();
	cout << " ---> ";
	_pt2.print();
	cout << endl;
}
