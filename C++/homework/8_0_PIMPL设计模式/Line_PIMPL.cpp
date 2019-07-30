//Line_PIMPL.cpp
#include "Line_PIMPL.h"

#include <iostream>
using std::cout;
using std::endl;

class Line::LineIMPL
{
	class Point
	{
	public:
		Point(int ix, int iy)
			: _ix(ix)
			, _iy(iy)
		{
			cout << "Point()" << endl;
		}

		~Point()
		{
			cout << "~Point()" << endl;
		}

		void print() const
		{
			cout << "(" << _ix << "," << _iy << ")";
		}

	private:
		int _ix;
		int _iy;
	};

public:
	LineIMPL(int ix1, int iy1, int ix2, int iy2)
		: _point1(ix1, iy1)
		, _point2(ix2, iy2)
	{
		cout << "LineIMPL()" << endl;
	}

	~LineIMPL()
	{
		cout << "~LineIMPL()" << endl;
	}

	void printLine() const
	{
		_point1.print();
		cout << " ---> ";
		_point2.print();
		cout << endl;
	}

private:
	Point _point1;
	Point _point2;
};

Line::Line(int ix1, int iy1, int ix2, int iy2)
	:_pLineIMPL(new LineIMPL(ix1, iy1, ix2, iy2))
{
	cout << "Line()" << endl;
}

Line::~Line()
{
	cout << "~Line()" << endl;
	if (_pLineIMPL) {
		delete _pLineIMPL;
	}
}

void Line::print() const
{
	_pLineIMPL->printLine();
}