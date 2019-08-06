#include <math.h>
#include <iostream>
#include <unordered_map>
#include <string>
using std::cout;
using std::endl;
using std::unordered_map;
using std::string;
using std::pair;

//unordered_map 重点是下标访问运算符的用法

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
	cities.insert(pair<int, string>(1, "北京"));
	cities.insert(pair<int, string>(2, "上海"));
	cities.insert(pair<int, string>(3, "上海"));
	cities.insert(pair<int, string>(4, "深圳"));
	cities.insert(pair<int, string>(4, "广州"));

	display(cities);
}

void test1()
{
	//unordered_map内部不能存放关键字相同的元素
	//默认情况下回按关键字升序的方式进行排列
	//
	//底层实现依然是红黑树
	//
	unordered_map<int, string> cities = {
		pair<int, string>(1, "北京"),
		std::make_pair(2, "上海"),
		std::make_pair(4, "深圳"),
		std::make_pair(4, "广州"),
		std::make_pair(3, "上海")
	};

	display(cities);

	std::pair<unordered_map<int, string>::iterator, bool> ret
		= cities.insert(std::make_pair(5, "武汉"));
	if (ret.second) {
		cout << "元素添加成功！" << endl;
		cout << ret.first->first << " --> "
			<< ret.first->second << endl;
	}
	else {
		cout << "元素添加失败，unordered_map中已有关键字相同的元素" << endl;
	}
	display(cities);

	//通过关键字key访问对应的value
	cout << cities[1] << endl;//时间复杂度为O(logN)
	cout << cities[2] << endl;

	cities[1] = "杭州";//修改对应value的方式
	display(cities);
	cout << endl;

	//当关键字代表的元素不存在时，直接创建一个新元素
	//对应的value会采用默认值
	cout << cities[6] << endl;
	display(cities);
	cout << endl;

	cities[7] = "西安";//添加新元素
	display(cities);

	//仅仅是查找元素  O(logN)
	unordered_map<int, string>::iterator it = cities.find(8);
	if (it != cities.end()) {
		cout << "查找元素成功" << endl;
		cout << it->first << " --> "
			<< it->second << endl;
	}
	else {
		cout << "查找失败" << endl;//不会添加新的元素
	}
	display(cities);
}

void test2()
{
	unordered_map<string, string> cities = {
		pair<string, string>("0755", "深圳"),
		std::make_pair("010", "北京"),
		std::make_pair("021", "上海"),
		std::make_pair("0755", "广州"),
	};

	display(cities);

	std::pair<unordered_map<string, string>::iterator, bool> ret
		= cities.insert(std::make_pair("027", "武汉"));
	if (ret.second) {
		cout << "元素添加成功！" << endl;
		cout << ret.first->first << " --> "
			<< ret.first->second << endl;
	}
	else {
		cout << "元素添加失败，unordered_map中已有关键字相同的元素" << endl;
	}
	display(cities);

	//通过关键字key访问对应的value
	cout << cities["010"] << endl;//时间复杂度为O(logN)
	cout << cities["0755"] << endl;

	cities["010"] = "杭州";//修改对应value的方式
	display(cities);
	cout << endl;

	//当关键字代表的元素不存在时，直接创建一个新元素
	//对应的value会采用默认值
	cout << cities["023"] << endl;
	display(cities);
	cout << endl;

	cities["029"] = "西安";//添加新元素
	display(cities);

	//仅仅是查找元素
	unordered_map<string, string>::iterator it = cities.find("0728");
	if (it != cities.end()) {
		cout << "查找元素成功" << endl;
		cout << it->first << " --> "
			<< it->second << endl;
	}
	else {
		cout << "查找失败" << endl;//不会添加新的元素
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