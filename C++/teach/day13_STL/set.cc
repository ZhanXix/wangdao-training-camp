#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::set;
using std::string;

template <class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	while (cit != c.end()) {
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}

void test0()
{
	set<int> numbers;
	cout << "numbers' size = " << numbers.size() << endl;

	numbers.insert(1);
	numbers.insert(2);
	numbers.insert(3);
	display(numbers);
}

void test1()
{
	int arr[10] = { 3,6,1,2,6,5,7,9,8,3 };

	//setĬ��������ǰ�������ʽ��������
	//set�в��ܴ�Źؼ�����ͬ��Ԫ��
	//
	//������ݽṹ������(skip-list)
	//
	//�ײ�ʵ�֣����ú����(rb-tree) ==> ����ƽ�������(AVL)
	//			==> ����һ��Ԫ�ص�ʱ�临�Ӷ�ΪO(logN) ==> ���ֲ���
	//
	//������ص㣺
	//	1.�ڵ㲻�Ǻ�ɫ���Ǻ�ɫ
	//	2.���ڵ��Ǻ�ɫ��
	//	3.Ҷ�ӽ�㶼�Ǻ�ɫ�ģ��ս�㣩
	//	4.��������������������Ǻ�ɫ��
	//	5.�Ӹ��ڵ㵽����һ����㣬·���ϵĺ�ɫ�ڵ���Ŀ��ͬ
	//
	//������˳ʱ����ת������ת�Ľ���Ϊ������
	//��������ʱ����ת������ת�Ľ���Ϊ������
	//
	set<int> numbers(arr, arr + 10);
	display(numbers);

	//set��֧���±���������
	//numbers[0];//error

	set<int>::iterator it = numbers.begin();
	//*it = 10;//error: ����set�е�Ԫ���޷������޸ģ�����ֻ����
	numbers.erase(it);//����ɾ��
	display(numbers);

	//���Ԫ��:
	std::pair<set<int>::iterator, bool> ret = numbers.insert(2);
	if (ret.second) {
		cout << "���Ԫ�سɹ���" << endl;
		cout << *ret.first << endl;
	}
	else {
		cout << "set��������ͬԪ�أ����ʧ�ܣ�" << endl;
		cout << *ret.first << endl;
	}
	//set������������ȥ��

	//����Ԫ�أ�
	if (numbers.count(1) > 0) {
		cout << "����Ԫ�سɹ�" << endl;
	}
	else {
		cout << "set��û�и�Ԫ��" << endl;
	}

	auto it2 = numbers.find(3);
	if (it2 == numbers.end()) {
		cout << "set��û�и�Ԫ��" << endl;
	}
	else {
		cout << "����Ԫ�سɹ�" << endl;
		cout << "*it2 = " << *it2 << endl;
	}
}

void test2()
{//pair���÷�
	std::pair<int, string> p(1, "����");
	cout << p.first << " --> " << p.second << endl;
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

bool operator<(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() < rhs.getDistance();
}

bool operator>(const Point& lhs, const Point& rhs)
{
	return lhs.getDistance() > rhs.getDistance();
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
	//set<Point> numbers{
	set<Point,std::greater<Point>>numbers{
		Point(1,2),
		Point(2,5),
		Point(-2,10),
		Point(2,2),
		Point(2,2),
		Point(3,2)
	};
	display(numbers);

	set<Point>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	numbers.erase(it);
	display(numbers);

	//���Ԫ��:
	std::pair<set<Point>::iterator, bool> ret = numbers.insert(Point(11,12));
	if (ret.second) {
		cout << "���Ԫ�سɹ���" << endl;
		cout << *ret.first << endl;
	}
	else {
		cout << "set��������ͬԪ�أ����ʧ�ܣ�" << endl;
		cout << *ret.first << endl;
	}

	//����Ԫ�أ�
	auto it2 = numbers.find(Point(11,12));
	if (it2 == numbers.end()) {
		cout << "set��û�и�Ԫ��" << endl;
	}
	else {
		cout << "����Ԫ�سɹ�" << endl;
		cout << "*it2 = " << *it2 << endl;
	}
}

int main()
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}