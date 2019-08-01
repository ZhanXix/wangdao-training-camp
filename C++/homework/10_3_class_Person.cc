/* 
 *	构建一个类person，包含字符串成员name（姓名），整型数据成员age（年龄），
	成员函数display（）用来输出name和age。构造函数包含两个参数，用来对name和age初始化。    
 *	构建一个类employee由person派生，包含department（部门），实型数据成员salary（工资）, 
	成员函数display（）用来输出职工姓名、年龄、部门、工资，其他成员根据需要自己设定。    
 *	主函数中定义3个employee类对象，内容自己设定，
	将其姓名、年龄、部门、工资输出，并计算他们的平均工资。
 */

#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Person
{
public:
	//构造
	Person(const char* name, int age)
		: _name(new char[strlen(name) + 1]())
		, _age(age)
	{
		cout << "Person(const char*, int)" << endl;
		strcpy(_name, name);
	}

	//析构
	~Person()
	{
		cout << "~Person()" << endl;
		delete[] _name;
	}

	//成员方法
	void display() const
	{
		cout << "name = " << _name
			<< ", age = " << _age << endl;
	}

private:
	char* _name;	//姓名
	int _age;	//年龄
};

class Employee
	: public Person
{
public:
	//构造
	Employee(const char* name, int age, const char* department, float salary)
		: Person(name, age)
		, _department(new char[strlen(department) + 1]())
		, _salary(salary)
	{
		cout << "Employee(const char*, int, const char*, float)" << endl;
		strcpy(_department, department);
	}

	//析构
	~Employee()
	{
		cout << "~Employee()" << endl;
		delete[] _department;
	}

	//成员方法
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
	char* _department;	//部门
	float _salary;	//工资
};

//测试代码
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