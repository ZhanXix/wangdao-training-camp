#include <math.h>
#include <iostream>
#include <unordered_map>
#include <string>
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::pair;

//unordered_map �ص����±������������÷�

template <class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	for (; cit != c.end(); ++cit) {
		cout << cit->first << " ---> " << cit->second << endl;
	}
}

void test0()
{
	unordered_map<int, string> cities;
	cities.insert(pair<int, string>(1, "����"));
	cities.insert(pair<int, string>(2, "�Ϻ�"));
	cities.insert(pair<int, string>(3, "�Ϻ�"));
	cities.insert(pair<int, string>(4, "����"));
	cities.insert(pair<int, string>(4, "����"));

	display(cities);
}

void test1()
{
	//unordered_map�ڲ����ܴ�Źؼ�����ͬ��Ԫ��
	//Ĭ������»ذ��ؼ�������ķ�ʽ��������
	//
	//�ײ�ʵ����Ȼ�Ǻ����
	//
	unordered_map<int, string> cities = {
		pair<int, string>(1, "����"),
		std::make_pair(2, "�Ϻ�"),
		std::make_pair(4, "����"),
		std::make_pair(4, "����"),
		std::make_pair(3, "�Ϻ�")
	};

	display(cities);

	std::pair<unordered_map<int, string>::iterator, bool> ret
		= cities.insert(std::make_pair(5, "�人"));
	if (ret.second) {
		cout << "Ԫ�����ӳɹ���" << endl;
		cout << ret.first->first << " --> "
			<< ret.first->second << endl;
	}
	else {
		cout << "Ԫ������ʧ�ܣ�unordered_map�����йؼ�����ͬ��Ԫ��" << endl;
	}
	display(cities);

	//ͨ���ؼ���key���ʶ�Ӧ��value
	cout << cities[1] << endl;//ʱ�临�Ӷ�ΪO(logN)
	cout << cities[2] << endl;

	cities[1] = "����";//�޸Ķ�Ӧvalue�ķ�ʽ
	display(cities);
	cout << endl;

	//���ؼ��ִ�����Ԫ�ز�����ʱ��ֱ�Ӵ���һ����Ԫ��
	//��Ӧ��value�����Ĭ��ֵ
	cout << cities[6] << endl;
	display(cities);
	cout << endl;

	cities[7] = "����";//������Ԫ��
	display(cities);

	//�����ǲ���Ԫ��  O(logN)
	unordered_map<int, string>::iterator it = cities.find(8);
	if (it != cities.end()) {
		cout << "����Ԫ�سɹ�" << endl;
		cout << it->first << " --> "
			<< it->second << endl;
	}
	else {
		cout << "����ʧ��" << endl;//���������µ�Ԫ��
	}
	display(cities);
}

void test2()
{
	unordered_map<string, string> cities = {
		pair<string, string>("0755", "����"),
		std::make_pair("010", "����"),
		std::make_pair("021", "�Ϻ�"),
		std::make_pair("0755", "����"),
	};

	display(cities);

	std::pair<unordered_map<string, string>::iterator, bool> ret
		= cities.insert(std::make_pair("027", "�人"));
	if (ret.second) {
		cout << "Ԫ�����ӳɹ���" << endl;
		cout << ret.first->first << " --> "
			<< ret.first->second << endl;
	}
	else {
		cout << "Ԫ������ʧ�ܣ�unordered_map�����йؼ�����ͬ��Ԫ��" << endl;
	}
	display(cities);

	//ͨ���ؼ���key���ʶ�Ӧ��value
	cout << cities["010"] << endl;//ʱ�临�Ӷ�ΪO(logN)
	cout << cities["0755"] << endl;

	cities["010"] = "����";//�޸Ķ�Ӧvalue�ķ�ʽ
	display(cities);
	cout << endl;

	//���ؼ��ִ�����Ԫ�ز�����ʱ��ֱ�Ӵ���һ����Ԫ��
	//��Ӧ��value�����Ĭ��ֵ
	cout << cities["023"] << endl;
	display(cities);
	cout << endl;

	cities["029"] = "����";//������Ԫ��
	display(cities);

	//�����ǲ���Ԫ��
	unordered_map<string, string>::iterator it = cities.find("0728");
	if (it != cities.end()) {
		cout << "����Ԫ�سɹ�" << endl;
		cout << it->first << " --> "
			<< it->second << endl;
	}
	else {
		cout << "����ʧ��" << endl;//���������µ�Ԫ��
	}
	display(cities);
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

	~Point() { cout << "~Point()" << endl; }

	double getDistance() const
	{
		return sqrt(_ix * _ix + _iy * _iy);
	}

	int getx() const { return _ix; }
	int gety() const { return _iy; }

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
	bool operator()(const Point& lhs, const Point& rhs) const
	{
		return lhs.getDistance() < rhs.getDistance();
	}
};

namespace std
{
	template<>
	struct hash<Point>
	{
		size_t operator()(const Point& pt) const
		{
			return (pt.getx() * pt.getx() - 1) ^
				(pt.gety() * pt.gety() - 1);
		}
	};
}//end of namespace std

struct PointHasher
{
	size_t operator()(const Point& pt) const
	{
		return (pt.getx() * pt.getx() - 1) ^
			(pt.gety() * pt.gety() - 1);
	}
};

struct PointEqual
{
	bool operator()(const Point& lhs, const Point& rhs) const
	{
		return (lhs.getx() == rhs.getx()) && (lhs.gety() == rhs.gety());
	}
};

void test3()
{
	//unordered_map<Point, int> points = {
	unordered_map<Point, int, PointHasher, PointEqual> points = {
		std::make_pair(Point(1,2),1),
		std::make_pair(Point(2,2),1),
		std::make_pair(Point(3,2),1),
		std::make_pair(Point(4,2),1)
	};

	display(points);
}

int main()
{
	//test0();
	//test1();
	//test2();
	test3();
	return 0;
}