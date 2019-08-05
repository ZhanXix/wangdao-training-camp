 ///
 /// @file    Figure.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 14:31:16
 ///
 
#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

//遵循开闭原则: 对修改关闭(不需要修改原来的代码), 对扩展开放

class Figure
{
public://提供统一的接口
	virtual void display() const =0;
	virtual double area() const=0;
};

void display(Figure * fig)
{
	fig->display();
	cout << "的面积是:" << fig->area() << endl;
}

class Rectangle
: public Figure
{
public:
	Rectangle(double length, double width)
	: _length(length)
	, _width(width)
	{
		cout << "Rectangle()" << endl;
	}

	void display() const
	{
		cout << "rectangle";
	}

	double area() const
	{	
		return _length * _width;
	}
private:
	double _length;
	double _width;
};


class Circle
: public Figure
{
public:
	Circle(double radius)
	: _radius(radius)
	{
		cout << "Circle()" << endl;
	}

	void display() const
	{	cout << "circle";	}

	double area() const
	{
		return 3.14159 * _radius * _radius;
	}

private:
	double _radius;
};

class Triangle
: public Figure
{
public:
	Triangle(double a, double b, double c)
	: _a(a)
	, _b(b)
	, _c(c)
	{
		cout << "Triangle()" << endl;
	}

	void display() const
	{
		cout << "triangle";
	}

	double area() const
	{
		double p = (_a + _b + _c)/2;
		return sqrt(p * (p - _a) * (p - _b) * (p - _c));
	}

private:
	double _a;
	double _b;
	double _c;
};


class Cube
: public Figure
{
public:
	Cube(double a)
	: _a(a)
	{
		cout << "Cube()" << endl;
	}

	void display() const
	{	cout << "cube";}

	double area() const
	{
		return 6 * _a * _a;
	}

private:
	double _a;
};

 
int main(void)
{
	Rectangle rectangle(3, 4);
	Circle circle(10);
	Triangle triangle(3, 4, 5);

	display(&rectangle);
	display(&circle);
	display(&triangle);

	Cube cube(10);
	display(&cube);

	return 0;
}
