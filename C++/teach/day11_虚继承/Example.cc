 ///
 /// @file    Example.cc
 /// @author  lemon(haohb13@gmail.com)
 /// @date    2019-08-02 11:21:37
 ///
 
#include <iostream>
using std::cout;
using std::endl;


#pragma pack(push)//改变字节对齐的方式
#pragma pack(4) //按4字节对齐

class Base
{
public:
	virtual void dispay() const
	{
		cout << "Base::dispay()" << endl;
	}
};


//默认情况下按8字节对齐



class Example
: public Base
{
public:
	virtual void display() const
	{	cout << "display()" << endl;	}


	int _d1;              //4
	double _d2;			  //8
	char _d3;			  //1
	short _d4[5];		  //10
	int & _d5;	          //8
	static double _d6;    //8
};
#pragma pack(pop)
 
int main(void)
{
	cout << sizeof(Base) << endl;
	cout << sizeof(Example) << endl;

	return 0;
}
