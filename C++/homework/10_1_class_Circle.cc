/* 编写一个圆类Circle，该类拥有：
 *	① 1个成员变量，存放圆的半径；
 *	② 两个构造方法
 * 			Circle( )              // 将半径设为0
 * 			Circle(double  r )     //创建Circle对象时将半径初始化为r
 *	③ 三个成员方法
 *			double getArea( )      //获取圆的面积
 *			double getPerimeter( ) //获取圆的周长
 *			void  show( )          //将圆的半径、周长、面积输出到屏幕
 */

#include <iostream>
using std::cout;
using std::endl;

constexpr double Pi = 3.1415926;

class Circle
{
public:
	//构造
	Circle()
		: _r(0)
	{
		cout << "Circle()" << endl;
	}

	Circle(double r)
		: _r(r)
	{
		cout << "Circle(double)" << endl;
	}

	//析构
	~Circle()
	{
		cout << "~Circle()" << endl;
	}

	//成员方法
	double getArea() const     //获取圆的面积
	{
		return Pi * _r * _r;
	}

	double getPerimeter() const	//获取圆的周长
	{
		return 2 * Pi * _r;
	}

	void show() const         //将圆的半径、周长、面积输出到屏幕
	{
		cout << "radius = " << _r
			<< ", perimeter = " << getPerimeter()
			<< ", area = " << getArea() << endl;
	}

private:
	double _r;	//圆的半径
};


//测试代码
int main()	
{
	Circle c1;
	Circle c2(3);

	cout << "c1: ";
	c1.show();
	cout << "c2: ";
	c2.show();
	cout << "c2.getArea() = " << c2.getArea() << endl;
	cout << "c2.getPerimeter() = " << c2.getPerimeter() << endl;

	return 0;
}