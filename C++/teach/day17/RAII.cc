#include <iostream>
using std::cout;
using std::endl;

template<class T>
class RAII
{
public:
	RAII(T *p)
		: _p(p)
	{}

	~RAII()
	{
		if (_p) {
			delete _p;
		}
	}

	T* operator->()
	{
		return _p;
	}

	T operator*()
	{
		return *_p;
	}

private:
	T* _p;
};

class Point
{
public:
	Point(int ix = 0, int iy = 0)
		: _ix(ix)
		, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	}

	~Point()
	{
		cout << "~Point()" << endl;
	}

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
	//ÖÇÄÜÖ¸Õë
	RAII<Point> pointer(new Point(1, 2));
	cout << *pointer << endl;
	pointer->print();

	return 0;
}