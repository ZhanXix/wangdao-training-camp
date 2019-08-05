#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//       实例化
//函数模板 ==> 模板函数
//     模板参数推导 ==> 代码生成器
template <class T>
T add(T x, T y);//函数模板的声明

//函数模板与函数模板之间也可以进行重载
template <class T>
T add(T x, T y, T z)
{
	return x + y + z;
}

//模板函数
//
//普通函数与函数模板是可以进行重载的
//而且普通函数的执行要优先于函数模板
//
#if 0
int add(int x, int y)
{
	cout << "int add(int,int)" << endl;
	return x + y;
}
#endif

//模板的特化(specialization)
template<>
const char* add<const char*>(const char* pstr1, const char* pstr2)
{
	char* ptmp = new char[strlen(pstr1) + strlen(pstr2) + 1]();
	strcpy(ptmp, pstr1);
	strcat(ptmp, pstr2);
	return ptmp;
}

int main()
{
	int d1 = 1, d2 = 2;
	double d3 = 1.1, d4 = 2.2;
	char d5 = 'a', d6 = 1;

	cout << "add(d1, d2) = " << add(d1, d2) << endl;//隐式实例化
	cout << "add(d3, d4) = " << add<double>(d3, d4) << endl;//显式实例化
	cout << "add(d5, d6) = " << add(d5, d6) << endl;

	int d7 = 3;
	cout << "add(d1, d2, d7) = " << add(d1, d2, d7) << endl;

	const char* p1 = "hello";
	const char* p2 = "world";
	cout << "add(p1, p2) = " << add(p1, p2) << endl;

	return 0;
}

template <class T>
T add(T x, T y)//函数模板的实现
{
	//cout << "T add(T x, T y)" << endl;
	return x + y;
}
