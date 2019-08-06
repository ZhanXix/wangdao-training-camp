#include <math.h>
#include <iostream>
#include <unordered_set>
#include <string>
using std::cout;
using std::endl;
using std::unordered_set;
using std::string;

template <class Container>
void display(const Container& c)
{
	for (auto& elem : c) {
		cout << elem << " ";
	}
	cout << endl;
}

void test0()
{
	//unordered_setԪ���������
	//�ڲ����ܴ�Źؼ�����ͬ��Ԫ��
	int array[10] = { 8,7,1,2,5,9,0,8,7,3 };
	unordered_set<int> numbers(array, array + 10);
	display(numbers);

	auto it = numbers.begin();
	cout << *it << endl;
	++it;//ǰ����ʵ�������ֻ����ǰ����(++)���������(--)
	cout << *it << endl;
	//--it;//error  ��ʵ��֤������windows�����ǿ���--�ģ�linux��ᱨ��
	//cout << *it << endl;

	auto it2 = numbers.find(9);
	if (it2 != numbers.end()) {
		cout << *it2 << endl;
	}
	else {
		cout << "����Ԫ��ʧ��" << endl;
	}
}

class Point
{
public:
	Point(int ix, int iy)
		: _ix(ix)
		, _iy(iy)
	{
		cout << "Point(int, int)" << endl;
	}

	double getDistance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}

	friend std::ostream& operator<<(std::ostream& os, const Point& rhs);
	friend bool operator==(const Point& lhs, const Point& rhs);

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

bool operator<(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() < rhs.getDistance();
}

bool operator>(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() > rhs.getDistance();
}

bool operator==(const Point& lhs, const Point& rhs)
{
	return (lhs._ix == rhs._ix) && (lhs._iy == rhs._iy);
}

struct Comparator
{
	bool operator()(const Point& lhs, const Point& rhs)
	{
		return lhs.getDistance() < rhs.getDistance();
	}
};

void test3()
{
	unordered_set<Point> points{
		Point(5,6),
		Point(2,3),
		Point(1,2),
		Point(2,2),
		Point(4,3),
		Point(7,8)
	};
}

int main()
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}