#include <math.h>
#include <iostream>
#include <queue>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::priority_queue;

void test0()
{
	vector<int> numbers { 8,1,6,3,7,2,5,9,4 };
	priority_queue<int> que(numbers.begin(), numbers.end());

	while (!que.empty()) {
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
}

//排序：
//>外部排序
//	>hash方式
//>内部排序
//	八大排序算法
//		冒泡排序
//		快速排序
//		插入排序
//		希尔排序
//		选择排序
//		堆排序 ==> 海量数据处理
//		归并排序
//		基数排序

void test1()
{
	//默认情况下，采用的是小于符号的比较方式
	//得到的序列是一个降序序列 ==> 大顶堆
	//
	//底层实现：堆排序
	//	大顶堆 ==> 父结点的值一定大于左右孩子的值
	//
	//可以理解成：
	//	每一次都是用堆顶元素与新来的元素进行比较，
	//	如果返回值为true，则将新来的元素放在堆顶的
	//	位置，并将原来堆顶的元素进行堆的调整
	//
	priority_queue<int> que;
	vector<int> numbers{ 5,1,6,3,7,2,8,9,4 };
	for (size_t idx = 0; idx != numbers.size(); ++idx) {
		que.push(numbers[idx]);
		cout << "当前队列中优先级最高的元素是" << que.top() << endl;
	}

	while (!que.empty()) {
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
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

#if 0
bool operator<(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() < rhs.getDistance();
}

bool operator>(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() > rhs.getDistance();
}
#endif

struct Comparator
{
	bool operator()(const Point& lhs, const Point& rhs) const
	{
		return lhs.getDistance() > rhs.getDistance();
	}
};

void test2()
{
	vector<Point> points{
		Point(1,2),
		Point(10,2),
		Point(11,2),
		Point(1,12),
		Point(1,22),
		Point(11,22),
	};
	priority_queue<Point, vector<Point>, Comparator>
		que(points.begin(), points.end());

	while (!que.empty()) {
		cout << que.top() << " ";
		que.pop();
	}
	cout << endl;
}

int main()
{
	//test0();
	//test1();
	test2();
	return 0;
}