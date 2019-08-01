/* ��дһ��Բ��Circle������ӵ�У�
 *	�� 1����Ա���������Բ�İ뾶��
 *	�� �������췽��
 * 			Circle( )              // ���뾶��Ϊ0
 * 			Circle(double  r )     //����Circle����ʱ���뾶��ʼ��Ϊr
 *	�� ������Ա����
 *			double getArea( )      //��ȡԲ�����
 *			double getPerimeter( ) //��ȡԲ���ܳ�
 *			void  show( )          //��Բ�İ뾶���ܳ�������������Ļ
 */

#include <iostream>
using std::cout;
using std::endl;

constexpr double Pi = 3.1415926;

class Circle
{
public:
	//����
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

	//����
	~Circle()
	{
		cout << "~Circle()" << endl;
	}

	//��Ա����
	double getArea() const     //��ȡԲ�����
	{
		return Pi * _r * _r;
	}

	double getPerimeter() const	//��ȡԲ���ܳ�
	{
		return 2 * Pi * _r;
	}

	void show() const         //��Բ�İ뾶���ܳ�������������Ļ
	{
		cout << "radius = " << _r
			<< ", perimeter = " << getPerimeter()
			<< ", area = " << getArea() << endl;
	}

private:
	double _r;	//Բ�İ뾶
};


//���Դ���
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