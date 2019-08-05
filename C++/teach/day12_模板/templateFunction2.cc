#include <iostream>
using std::cout;
using std::endl;

#define MAX 10


//ģ���β��б��ǿ��Դ�Ŷ��������
//
//ģ���βε���������������
//1.���Ͳ���
//2.�����Ͳ������������ʽ��������(bool/char/short/int/long)
//
//ģ���βο�������Ĭ��ֵ��C++11֮����﷨��
//
template <class T1, class T2>
void func(T1 t1, T2 t2)
{
	cout << "t1 = " << t1 << endl
		<< "t2 = " << t2 << endl;
}

template <class T, int NUMBER = 10>
T func1(T t)
{
	return NUMBER * t;
}

int main()
{
	int d1 = 2;
	double d2 = 1.1;

	func<int, double>(d1, d2);
	cout << func1<int>(d1) << endl;
	cout << func1<int, 20>(d1) << endl;

	return 0;
}
