 ///
 /// @file    Point3D.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-01 09:35:34
 ///
 
#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:// 该类提供的功能、接口、服务
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{	cout << "Point(int,int)" << endl;	}

	void display() const
	{
		cout << "(" << _ix
			 << "," << _iy
			 << ")" << endl;
	}

	int getX() const {	return _ix;	}
	int getY() const {	return _iy;	} 

private:
	int _ix;
	int _iy;
};

class Point3D
: public Point  //接口继承
{
public:
	Point3D(int ix, int iy, int iz)
	: Point(ix, iy)
	, _iz(iz)
	{
		cout << "Point3D(int,int,int)" << endl;
	}

	void print() const
	{
		cout << "(" << getX() 
			 << "," << getY()
			 << "," << _iz
			 << ")" << endl;
	}

private:
	int _iz;
};
 
int main(void)
{
	Point pt(11, 12);
	cout << "pt = ";
	pt.display();
	Point3D pt2(1, 2, 3);
	cout << "pt2 = ";
	pt2.print();

	//向上转型(合法)
	//
	//
	//派生类对象能赋值给基类对象
	pt = pt2;//Point & operator=(const Point &rhs)
			// const Point & rhs = pt2;
	cout << "pt = ";
	pt.display();

	//基类对象不能赋值给派生类对象
	//pt2 = pt;//error, Point3D & operator=(const Point3D & rhs)
			 // const Point3D & rhs = pt;
	
	//基类的引用可以绑定到派生类对象
	Point & ref1 = pt2;
	cout << "ref1 = ";
	ref1.display();

	//基类指针可以指向派生类对象
	Point * p1 = &pt2;
	p1->display();

	//
	//向下转型(合法)
	Point3D * pp1 = (Point3D *)p1;
	pp1->print();

	//向下转型(不合法)
	Point * p2 = &pt;
	Point3D * pp2 = (Point3D *)p2;
	pp2->print();


	//Point3D * p2 = &pt;//error

 
	return 0;
}
