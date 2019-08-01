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

protected:
	int getY() const {	return _iy;	}


protected:
	int _ix;

private:
	int _iy;
};

class Point3D
: protected Point  
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
		//display(); //protected
		cout << "(" << _ix
		     //<< "," << _iy //在派生类内部，不管以哪种方式继承，基类的私有成员都不能在派生类直接访问
		     << "," << getY()//对于基类的非私有成员，如果以protected方式继承时，在派生类内部的访问权限都变成protected
			 << "," << _iz
			 << ")" << endl; }

private:
	int _iz;
};
 
class Point4D
: public Point3D
{

	void show() const
	{
		cout << _ix 
			 << getY() ;
	}
	//派生类内部可以直接访问顶层基类的非私有成员
};
int main(void)
{
	Point3D pt(1, 2, 3);
	pt.display();//error 对于派生类对象而言，只能访问以public继承的基类的public成员
	//pt.getX();//error
	//pt._ix = 10;//error
 
	return 0;
}
