#include <iostream>
using std::cout;
using std::endl;

//       ʵ����
//����ģ�� ==> ģ�庯��
//     ģ������Ƶ� ==> ����������
template <class T>
T add(T x, T y);//����ģ�������

//����ģ���뺯��ģ��֮��Ҳ���Խ�������
template <class T>
T add(T x, T y, T z)
{
	return x + y + z;
}

//ģ�庯��
//
//��ͨ�����뺯��ģ���ǿ��Խ������ص�
//������ͨ������ִ��Ҫ�����ں���ģ��
//
#if 1
int add(int x, int y)
{
	cout << "int add(int,int)" << endl;
	return x + y;
}
#endif

int main()
{
	int d1 = 1, d2 = 2;
	double d3 = 1.1, d4 = 2.2;
	char d5 = 'a', d6 = 1;
	cout << "add(d1, d2) = " << add(d1, d2) << endl;
	cout << "add(d3, d4) = " << add(d3, d4) << endl;
	cout << "add(d5, d6) = " << add(d5, d6) << endl;

	int d7 = 3;
	cout << "add(d1, d2, d7) = " << add(d1, d2, d7) << endl;

	return 0;
}

template <class T>
T add(T x, T y)//����ģ���ʵ��
{
	cout << "T add(T x, T y)" << endl;
	return x + y;
}
