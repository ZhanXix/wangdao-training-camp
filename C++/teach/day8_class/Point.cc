 ///
 /// @file    Point.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-30 09:54:40
 ///
 
#include <iostream>
using std::cout;
using std::endl;

//class Point;

class Complex
{
public:
	Complex(double dreal = 0, double dimag = 0)
	: _dreal(dreal)
	, _dimag(dimag)
	{
		cout << "Complex(double,double)" << endl;
	}


	Complex & operator++()
	{
		++_dreal;
		++_dimag;
		return *this;
	}

	Complex operator++(int)  
	{					     
		Complex tmp(*this);
		++_dreal;
		++_dimag;
		return tmp;
	}

	//表达式执行结束之后，对象本身发生变化
	//
	//复合赋值运算符都推荐以成员函数形式重载
	// -= *= /=  %=
	Complex & operator+=(const Complex & rhs)
	{
		_dreal += rhs._dreal;
		_dimag += rhs._dimag;
	
		return *this;
	}

	//运算符重载之友元(普通)函数
	friend Complex operator+(const Complex & lhs, const Complex & rhs );
	friend bool operator==(const Complex & lhs, const Complex & rhs);

	//输出流运算符的要求是:左操作数为流对象，右操作数为输出的内容
	//
	//因此输出流运算符不能作为成员函数形式存在
	//
	//std::ostream & operator<<(std::ostream & os);
	
	friend std::ostream & operator<<(std::ostream & os, const Complex & rhs);

	//friend Point;
	friend class Point;
private:
	double _dreal;
	double _dimag;
};

std::ostream & operator<<(std::ostream &os, const Complex & rhs)
{
	//os << rhs._dreal << " + " << rhs._dimag << "i";
	if(rhs._dimag == 0)
		os << rhs._dreal;
	else {
		if(rhs._dreal == 0) {
			if(rhs._dimag == 1)
				os << "i";
			else if(rhs._dimag == -1)
				os << "-i";
			else 
				os << rhs._dimag << "i";
		}
		else {
			os << rhs._dreal;
			if(rhs._dimag > 0) {
				os << " + " << rhs._dimag << "i";
			} else if(rhs._dimag < 0) {
				os << " - " << rhs._dimag * (-1) << "i";
			}
		}
	}
	return os;
}

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
	} 

	explicit //禁止隐式转换
	Point(const Complex & rhs)
	: _ix(rhs._dreal)
	, _iy(rhs._dimag)
	{
		cout << "Point(const Complex & )" << endl;
	}



	friend std::ostream & operator<<(std::ostream & os, const Point & rhs);
private:
	int _ix;
	int _iy;
};
 
std::ostream & operator<<(std::ostream & os, const Point & rhs)
{
	os << "(" << rhs._ix
	   << "," << rhs._iy
	   << ")";
	return os;
}

int main(void)
{
	Point pt1(12, 11);
	cout << "pt1 = " << pt1 << endl;

	Complex c1(1, 2);
	cout << "c1 = " << c1 << endl;

	pt1 = c1;//将其他类型向自定义类型转换
			 //执行构造函数
	cout << "pt1 = " << pt1 << endl;
 
	return 0;
}
