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

//����
//>�ⲿ����
//	>hash��ʽ
//>�ڲ�����
//	�˴������㷨
//		ð������
//		��������
//		��������
//		ϣ������
//		ѡ������
//		������ ==> �������ݴ���
//		�鲢����
//		��������

void test1()
{
	//Ĭ������£����õ���С�ڷ��ŵıȽϷ�ʽ
	//�õ���������һ���������� ==> �󶥶�
	//
	//�ײ�ʵ�֣�������
	//	�󶥶� ==> ������ֵһ���������Һ��ӵ�ֵ
	//
	//�������ɣ�
	//	ÿһ�ζ����öѶ�Ԫ����������Ԫ�ؽ��бȽϣ�
	//	�������ֵΪtrue����������Ԫ�ط��ڶѶ���
	//	λ�ã�����ԭ���Ѷ���Ԫ�ؽ��жѵĵ���
	//
	priority_queue<int> que;
	vector<int> numbers{ 5,1,6,3,7,2,8,9,4 };
	for (size_t idx = 0; idx != numbers.size(); ++idx) {
		que.push(numbers[idx]);
		cout << "��ǰ���������ȼ���ߵ�Ԫ����" << que.top() << endl;
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