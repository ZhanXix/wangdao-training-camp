 ///
 /// @file    Complex.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-07-29 11:20:57
 ///
 
#include <iostream>
#include <limits>
using std::cout;
using std::endl;

class Point
{
public:
	Point(int ix = 0, int iy = 0)
	: _ix(ix)
	, _iy(iy)
	{
		cout << "Point(int,int)" << endl;
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

class Complex
{
public:
	Complex(double dreal = 0, double dimag = 0)
	: _dreal(dreal)
	, _dimag(dimag)
	{
		cout << "Complex(double,double)" << endl;
	}

	// -1 = i^2    欧拉公式
	
	void display() const
	{
		cout << _dreal << " + " << _dimag << "i" << endl;
	}

	//前置形式
	//
	//前置形式的自增自减运算符效率高于后置形式
	//
	Complex & operator++()
	{
		++_dreal;
		++_dimag;
		return *this;
	}

	//后置形式
	Complex operator++(int)  //后置形式在其参数中多加一个int，该int不是要传递参数，
	{					     //只是为了前置形式进行区分
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

	//类型转换函数: 将自定义类型向其他类型转换
	//
	//特点: 成员函数
	//      没有返回值类型
	//      在函数执行体内必须以传值形式返回一个目标类型的变量(对象)
	//
	//      一般情况下，能不使用就不要使用
	//      
	operator int()
	{
		cout << "operator int()" << endl;
		return _dreal;
	}

	operator double()
	{
		cout << "operator double()" << endl;
		return _dreal * _dimag;
	}

	operator Point()
	{
		cout << "operator Point()" << endl;
		return Point(_dreal, _dimag);
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
	friend std::istream & operator>>(std::istream & is,  Complex & rhs);
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

void readDobuleValue(std::istream & is, double & number)
{
	cout << ">> pls input a valid double value:" << endl;
	while(is >> number, !is.eof()) {
		if(is.bad()) {
			cout << "istream has corrupted!" << endl;
			return;
		} else if(is.fail()) {
			is.clear();
			is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			cout << ">> pls input a valid double value:" << endl;
			continue;
		}
		break;
	}
}

//强调: 对于输入流要考虑特殊情况
std::istream & operator>>(std::istream & is,  Complex & rhs)
{
	readDobuleValue(is, rhs._dreal);
	readDobuleValue(is, rhs._dimag);
	return is;
}

Complex operator+(const Complex & lhs, const Complex & rhs )
{
	return Complex(lhs._dreal + rhs._dreal, 
				   lhs._dimag + rhs._dimag);
}

bool operator==(const Complex & lhs, const Complex & rhs)
{
	return (lhs._dreal == rhs._dreal) && 
		   (lhs._dimag == rhs._dimag);
}

bool operator!=(const Complex & lhs, const Complex & rhs)
{
	return !(lhs == rhs);
}

 

int main(void)
{
	Complex c1(1, 2);

	//违反常规思维
	int x = c1;
	cout << "x = " << x << endl;

	double y = c1;
	cout << "y = " << y << endl;

	Point pt = c1;
	cout << "pt = " << pt << endl;

	return 0;
}
