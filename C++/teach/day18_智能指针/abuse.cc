#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::unique_ptr;
using std::shared_ptr;

class Point
	: public std::enable_shared_from_this<Point>
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

	//Point* addPoint(Point* pt)
	shared_ptr<Point> addPoint(Point* pt)
	{//在成员函数内部获取本对象的shared_ptr指针
		_ix += pt->_ix;
		_iy += pt->_iy;
		//return shared_ptr<Point>(this);
		return shared_from_this();
	}

private:
	int _ix;
	int _iy;
};

void test0()
{//误用：把一个原生裸指针交给不同的智能指针进行托管
	Point* pt = new Point(1, 2);
	unique_ptr<Point> up1(pt);
	unique_ptr<Point> up2(pt);
}

void test1()
{
	Point* pt = new Point(1, 2);
	shared_ptr<Point> sp1(pt);
	shared_ptr<Point> sp2(pt);
}

void test2()
{
	//Point* pt = new Point(1, 2);
	shared_ptr<Point> sp1(new Point(1, 2));
	shared_ptr<Point> sp2(new Point(3, 2)); 
	sp2.reset(sp1.get());
}

void test3()
{
	shared_ptr<Point> sp1(new Point(1, 2));
	shared_ptr<Point> sp2(new Point(3, 2));
	shared_ptr<Point> sp3(sp1->addPoint(sp2.get()));

	cout << "sp3's use_count = " << sp3.use_count() << endl;
}

int main()
{
	//test0();
	//test1();
	//test2();
	test3();

	return 0;
}