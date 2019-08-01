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

class Employee
	: public Person
{
public:
	//����
	Employee(const char* name, int age, const char* department, float salary)
		: Person(name, age)
		, _department(new char[strlen(department) + 1]())
		, _salary(salary)
	{
		cout << "Employee(const char*, int, const char*, float)" << endl;
		strcpy(_department, department);
	}

	//����
	~Employee()
	{
		cout << "~Employee()" << endl;
		delete[] _department;
	}

	//��Ա����
	void display() const
	{
		Person::display();
		cout << "department = " << _department
			<< ", salary = " << _salary << endl;
	}

	float getSalary() const
	{
		return _salary;
	}

private:
	char* _department;	//����
	float _salary;	//����
};

//���Դ���
int main()	
{
	//Person ps("Xiaoming", 20);
	//ps.display();

	Employee e1("XiaoMing", 22, "Research", 9234.3);
	cout << "e1:" << endl;
	e1.display();

	Employee e2("XiaoHong", 27, "Recruitment", 10043.6);
	Employee e3("XiaoGuang", 28, "Research", 14987.9);
	cout << "e2:" << endl;
	e2.display();
	cout << "e3:" << endl;
	e3.display();

	cout << "average wage = "
		<< (e1.getSalary() + e2.getSalary() + e3.getSalary()) / 3
		<< endl;

	return 0;
}