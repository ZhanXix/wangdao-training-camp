/* 
 * ��дһ��Բ������Cylinder�����̳��������Circle�࣬��ӵ�У�    
 *	�� 1����Ա������Բ����ĸߣ�    
 *	�� ���췽��               
 *			Cylinder (double r, double  h) //����Circle����ʱ���뾶��ʼ��Ϊr             
 *	�� ��Ա����    
 *			double getVolume( )   //��ȡԲ��������                 
 *			void  showVolume( )   //��Բ���������������Ļ      
 *		��дӦ�ó��򣬴�����Ķ��󣬷ֱ�����Բ�İ뾶��Բ����ĸߣ�    
 *		���㲢�ֱ���ʾԲ�뾶��Բ�����Բ�ܳ���Բ����������    
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

class Cylinder
	: public Circle
{
public:
	//����
	Cylinder(double r, double h)
		: Circle(r)
		, _h(h)
	{
		cout << "Cylinder(double,double)" << endl;
	}

	//����
	~Cylinder()
	{
		cout << "~Cylinder()" << endl;
	}

	//��Ա����
	double getVolume() const   //��ȡԲ��������
	{
		return getArea() * _h;
	}

	void  showVolume() const   //��Բ���������������Ļ
	{
		cout << "volume = " << getVolume() << endl;
	}

private:
	double _h;	//Բ����ĸ�
};


//���Դ���
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