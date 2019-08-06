#include <iostream>
#include <unordered_set>
#include <string>
using std::cout;
using std::endl;
using std::unordered_set;
using std::string;

template <class Container>
void display(const Container& c)
{
	for (auto& elem : c) {
		cout << elem << " ";
	}
	cout << endl;
}

void test0()
{
	//unordered_setԪ���������
	//�ڲ����ܴ�Źؼ�����ͬ��Ԫ��
	int array[10] = { 8,7,1,2,5,9,0,8,7,3 };
	unordered_set<int> numbers(array, array + 10);
	display(numbers);

	auto it = numbers.begin();
	cout << *it << endl;
	++it;//ǰ����ʵ�������ֻ����ǰ����(++)���������(--)
	cout << *it << endl;
	//--it;//error  ��ʵ��֤������windows�����ǿ���--�ģ�linux��ᱨ��
	//cout << *it << endl;

	auto it2 = numbers.find(9);
	if (it2 != numbers.end()) {
		cout << *it2 << endl;
	}
	else {
		cout << "����Ԫ��ʧ��" << endl;
	}
}

int main()
{
	test0();
	//test1();
	//test2();
	//test3();
	return 0;
}