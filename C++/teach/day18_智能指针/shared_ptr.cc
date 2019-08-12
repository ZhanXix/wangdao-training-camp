#include <iostream>
using std::cout;
using std::endl;
using std::shared_ptr;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
		: _ix(ix)
		, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	~Point() { cout << "~Point()" << endl; }

	void print() const
	{
		cout << "(" << _ix
			<< "," << _iy
			<< ")" << endl;
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& rhs);
private:
	int _ix;
	int _iy;
};

std::ostream& operator<<(std::ostream& os, const Point& rhs)
{
	os << "(" << rhs._ix
		<< "," << rhs._iy
		<< ")";
	return os;
}

void test0()
{
	shared_ptr<Point> sp(new Point(1, 2));
	(*sp).print();
	sp->print();
	cout << "sp' use_count = " << sp.use_count() << endl;

	shared_ptr<Point> sp2(sp);
	cout << "sp' use_count = " << sp.use_count() << endl;
	cout << "sp2' use_count = " << sp2.use_count() << endl;
	(*sp).print(); 
	sp->print();

	(*sp2).print();
	sp2->print();
}

int main()
{
	test0();
	return 0;
}