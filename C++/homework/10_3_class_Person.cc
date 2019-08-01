/* 
 *	����һ����person�������ַ�����Աname�����������������ݳ�Աage�����䣩��
	��Ա����display�����������name��age�����캯����������������������name��age��ʼ����    
 *	����һ����employee��person����������department�����ţ���ʵ�����ݳ�Աsalary�����ʣ�, 
	��Ա����display�����������ְ�����������䡢���š����ʣ�������Ա������Ҫ�Լ��趨��    
 *	�������ж���3��employee����������Լ��趨��
	�������������䡢���š�������������������ǵ�ƽ�����ʡ�
 */

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Person
{
public:
	//����
	Person(const char* name, int age)
		: _name(new char[strlen(name) + 1]())
		, _age(age)
	{
		cout << "Person(const char*, int)" << endl;
		strcpy(_name, name);
	}

	//����
	~Person()
	{
		cout << "~Person()" << endl;
		delete[] _name;
	}

	//��Ա����
	void display() const
	{
		cout << "name = " << _name
			<< ", age = " << _age << endl;
	}

private:
	char* _name;	//����
	int _age;	//����
};


//���Դ���
int main()	
{
	Person ps("Xiaoming", 20);
	ps.display();

	return 0;
}