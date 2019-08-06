#include <iostream>
#include <set>
#include <string>
using std::cout;
using std::endl;
using std::multiset;
using std::string;

template <class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	while (cit != c.end()) {
		cout << *cit << " ";
		++cit;
	}
	cout << endl;
}

void test0()
{
	multiset<int> numbers;
	cout << "numbers' size = " << numbers.size() << endl;

	numbers.insert(1);
	numbers.insert(2);
	numbers.insert(3);
	display(numbers);
}

void test1()
{
	int arr[10] = { 3,6,1,2,6,5,7,9,8,3 };
	multiset<int> numbers(arr, arr + 10);
	display(numbers);


	multiset<int>::iterator it = numbers.begin();
	numbers.erase(it);//����ɾ��
	display(numbers);

	//���Ԫ��:
	//multiset�������ͬԪ�أ��������ʧ��
	auto ret = numbers.insert(2);
	cout << "���Ԫ�سɹ���" << endl;
	cout << *ret << endl;

	//����Ԫ�أ�
	if (numbers.count(1) > 0) {
		cout << "����Ԫ�سɹ�" << endl;
	}
	else {
		cout << "multiset��û�и�Ԫ��" << endl;
	}

	auto it2 = numbers.find(3);
	if (it2 == numbers.end()) {
		cout << "multiset��û�и�Ԫ��" << endl;
	}
	else {
		cout << "����Ԫ�سɹ�" << endl;
		cout << "*it2 = " << *it2 << endl;
	}

	//��Χ���ң�
	//lowerbound �±߽� [ 
	//upperbound �ϱ߽� )
	auto lowerbound = numbers.lower_bound(6);
	cout << "*lowerbound = " << *lowerbound << endl;
	auto upperbound = numbers.upper_bound(6);
	cout << "*upperbound = " << *upperbound << endl;
	while (lowerbound != upperbound) {
		cout << *lowerbound << " ";
		++lowerbound;
	}
	cout << endl;

}

int main()
{
	//test0();
	test1();
	return 0;
}