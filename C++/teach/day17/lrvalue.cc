#include <vector>
#include <string>
using std::vector;
using std::string;

int main()
{
	int a = 1, b = 2;
	int* p = &a;
	vector<int> numbers;
	numbers.push_back(1);

	//&(a + b);//error ��ֵ
	//&(a++);//error ��ֵ
	&(++a);

	&p;
	&*p;
	&numbers[10];
	//&100;//error ��ֵ������ֵ����

	//&string("hello");//error ��ʱ������ֵ
	string s1 = "hello";
	string s2 = "world";

	//&(s1 + s2);//error ��ʱ������ֵ

	int& ref1 = a;
	//int& ref2 = 100;//error 
	const int& ref3 = 100;//const��ֵ���ÿ��԰󶨵���ֵ
	const int& ref4 = b;
	//��const��ֵ������Ϊһ���������޷����ֳ������ݹ����Ĳ�������ֵ������ֵ

	return 0;
}