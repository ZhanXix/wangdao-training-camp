#include <iostream>
#include <memory>
using std::cout;
using std::endl;
using std::shared_ptr;
using std::weak_ptr;

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

int main()
{
	weak_ptr<Point> wp;

	{
		shared_ptr<Point> sp(new Point(1, 2));
		wp = sp;

		cout << "sp's use_count = " << sp.use_count() << endl;
		cout << "wp's use_count = " << wp.use_count() << endl;
		cout << "wp's expired = " << wp.expired() << endl;
	
		shared_ptr<Point> sp2 = wp.lock();
		//shared_ptr<Point> sp3；
		cout << "sp2's use_count = " << sp2.use_count() << endl;

		if (sp2) {
			cout << "*sp2 = ";
			sp2->print();
			cout << "weak_ptr提升成功！" << endl;
		}
		else {
			cout << "weak_ptr提升失败，被托管的资源已经被销毁！" << endl;
		}
	}

	//weak_ptr知道所托管的资源是否存在
	//weak_ptr不能直接访问资源的
	cout << "wp's expired = " << wp.expired() << endl;

	shared_ptr<Point> sp2 = wp.lock();
	//shared_ptr<Point> sp3；
	cout << "sp2's use_count = " << sp2.use_count() << endl;

	if (sp2) {
		cout << "*sp2 = ";
		sp2->print();
		cout << "weak_ptr提升成功！" << endl;
	}
	else {
		cout << "weak_ptr提升失败，被托管的资源已经被销毁！" << endl;
	}

	return 0;
}