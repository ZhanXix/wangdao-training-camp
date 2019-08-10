#include <string.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class String
{
public:
	String()
		: _pstr(new char[1]())
	{
		cout << "String()" << endl;
	}

	String(const char* pstr)
		:_pstr(new char[strlen(pstr) + 1]())
	{
		cout << "String(const char*)" << endl;
		strcpy(_pstr, pstr);
	}

	//��const��ֵ������Ϊһ���βΣ��޷����ֳ������ݹ�����ʵ������ֵ������ֵ
	//
	//���и��ƿ�������ĺ���
	//���ƹ��캯��
	String(const String& rhs)
		: _pstr(new char[strlen(rhs._pstr) + 1]())
	{
		cout << "String(const String&)" << endl;
		strcpy(_pstr, rhs._pstr);
	}

	//��ֵ���������
	String& operator=(const String& rhs)
	{
		cout << "String& operator=(const String&)" << endl;
		if (this != &rhs) {
			delete[] _pstr;
			_pstr = new char[strlen(rhs._pstr) + 1]();
			strcpy(_pstr, rhs._pstr);
		}
		return *this;
	}

	//�����ƶ�����ĺ�����ִ��Ҫ�����ھ��и��ƿ������庯����ִ�У�ʹ����ֵʱ�͵��ƶ�����ĺ�����
	//�ƶ����캯��
	String(String&& rhs)
		: _pstr(rhs._pstr) //ʹ��ǳ���������ת��
	{
		cout << "String(String&&)" << endl;
		rhs._pstr = nullptr;
	}

	//�ƶ���ֵ����
	String& operator=(String&& rhs)
	{
		cout << "String& operator=(String&&)" << endl;
		delete[] _pstr;
		_pstr = rhs._pstr;
		rhs._pstr = nullptr;
		return *this;
	}

	~String()
	{
		cout << "~String()" << endl;
		if (_pstr) {
			delete[] _pstr;
		}
	}

	friend std::ostream& operator<<(std::ostream& os, const String& rhs);

private:
	char* _pstr;
};

std::ostream& operator<<(std::ostream& os, const String& rhs)
{
	os << rhs._pstr;
	return os;
}

String str("hello,world");

//�������ķ���ֵ�Ƕ���ʱ��������صĶ�����һ��
//�ֲ������������ٵģ�����ִ��return���ʱ��
//������ƶ����캯���������صĶ���������������
//���ں���ʱ��ִ��return���ʱ������ø��ƹ���
//����
String getString()
{
	String str("hello,world");
	cout << "strs =" << str << endl;
	return str;
}

int test0()
{
	vector<String> strs;
	strs.push_back("hello,world");
	cout << "strs[0] = " << strs[0] << endl << endl;

	String s1 = "hello";
	s1 = String("world");

	String s2 = "shenzhen";
	cout << "s2 = " << s2 << endl;
	//&s2;
	s1 = std::move(s2);//��ʽ��һ����ֵת������ֵ
						//һ���ʾ�ڸ����֮�󣬲�����ʹ�øö���
	cout << "s1 = " << s2 << endl;
	//cout << "s2 = " << s2 << endl;//error
	cout << "......" << endl;

	return 0;
}

void test1()
{
	getString();
}

//��ֵ������һ����ֵ
String&& func()
{
	String str("hello");
	return std::move(str);
}

int main()
{
	test1();
	//func();//��ֵ

	return 0;
}