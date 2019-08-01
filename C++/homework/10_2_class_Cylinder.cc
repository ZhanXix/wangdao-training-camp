/* 
 * 编写一个圆柱体类Cylinder，它继承于上面的Circle类，还拥有：    
 *	① 1个成员变量，圆柱体的高；    
 *	② 构造方法               
 *			Cylinder (double r, double  h) //创建Circle对象时将半径初始化为r             
 *	③ 成员方法    
 *			double getVolume( )   //获取圆柱体的体积                 
 *			void  showVolume( )   //将圆柱体的体积输出到屏幕      
 *		编写应用程序，创建类的对象，分别设置圆的半径、圆柱体的高，    
 *		计算并分别显示圆半径、圆面积、圆周长，圆柱体的体积。    
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

class Cylinder
	: public Circle
{
public:
	//构造
	Cylinder(double r, double h)
		: Circle(r)
		, _h(h)
	{
		cout << "Cylinder(double,double)" << endl;
	}

	//析构
	~Cylinder()
	{
		cout << "~Cylinder()" << endl;
	}

	//成员方法
	double getVolume() const   //获取圆柱体的体积
	{
		return getArea() * _h;
	}

	void  showVolume() const   //将圆柱体的体积输出到屏幕
	{
		cout << "volume = " << getVolume() << endl;
	}

private:
	double _h;	//圆柱体的高
};


//测试代码
int main()	
{
	Cylinder cl1(1, 1);
	Cylinder cl2(3, 2);

	cout << "Cylinder(1, 1) " << endl;
	cl1.show();
	cl1.showVolume();

	cout << "Cylinder(3, 2) " << endl;
	cl2.show();
	cl2.showVolume();

	return 0;
}