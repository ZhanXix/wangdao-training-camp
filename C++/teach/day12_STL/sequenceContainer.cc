//��������

#include <iostream>
#include <vector>
#include <deque>
#include <list>
using std::cout;
using std::endl;
using std::vector;
using std::deque;
using std::list;

template <class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	for (; cit != c.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
}

int array[5] = { 1,2,3,4,5 };

void test0()
{
	cout << "\n>>> test vector:" << endl;
	cout << sizeof(vector<int>) << endl;
	//vector<int> numbers(10, 1);
	//vector<int> numbers(array, array + 5);//��������Χ��һ������ҿ�������[beg, end)
	vector<int> numbers{ 1,2,3,4,5 };
	display(numbers);

	numbers.push_back(6);//O(1)
	display(numbers);
	//vectorû����ͷ����Ӻ�ɾ��Ԫ�صĲ���
	//���vector�ṩpush_front/pop_front
	//���ᵼ������Ԫ���ƶ�һ�Σ���ʱ�临�Ӷ�ΪO(n)

	cout << "numbers[2] = " << numbers[2] << endl;

	//���Ԫ��
	//
	//ǿ��������vector��˵��ִ��д����֮��
	//����Ҫ���¸��µ�������λ�ã��п��ܵ���������bug
	vector<int>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	auto it2 = numbers.insert(it, 11);//O(n)
	cout << "*it = " << *it << endl;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	it2 = numbers.insert(++it, 3, 10);
	cout << "*it2 = " << *it2 << endl;
	++it2;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	//ɾ��Ԫ��
	numbers.erase(it2, it2 + 3);
	display(numbers);

	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;
	//���Ԫ��
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;
	numbers.shrink_to_fit();//�ͷŶ���ռ�
	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;
	display(numbers);
}

void test1()
{
	cout << "\n>>> test deque:" << endl;
	//deque<int> numbers(10, 1);
	//deque<int> numbers(array, array + 5);
	deque<int> numbers{ 1,2,3,4,5 };
	display(numbers);

	numbers.push_back(6);//O(1)
	display(numbers);
	numbers.push_front(0);//O(1)
	display(numbers);

	//deque֧���±�����������֧��������ʣ�
	cout << "numbers[2] = " << numbers[2] << endl;

	//���Ԫ��
	deque<int>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	auto it2 = numbers.insert(it, 11);//O(n)
	cout << "*it = " << *it << endl;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	it2 = numbers.insert(++it, 3, 10);
	cout << "*it2 = " << *it2 << endl;
	++it2;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	//ɾ��Ԫ��
	numbers.erase(it2, it2 + 3);
	display(numbers);

	//���Ԫ��
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	//dequeû��capacity����
	numbers.shrink_to_fit();
	cout << "numbers.size() = " << numbers.size() << endl;
	display(numbers);
}

void test2()
{
	cout << "\n>>> test list:" << endl;
	//list<int> numbers(10, 1);
	//list<int> numbers(array, array + 5);
	list<int> numbers{ 1,2,3,4,5 };
	display(numbers);

	numbers.push_back(6);//O(1)
	display(numbers);
	numbers.push_front(0);//O(1)
	display(numbers);

	//list��֧���±�������������֧��������ʣ�

	//���Ԫ��
	list<int>::iterator it = numbers.begin();
	cout << "*it = " << *it << endl;
	auto it2 = numbers.insert(it, 11);//O(n)
	cout << "*it = " << *it << endl;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	it2 = numbers.insert(++it, 3, 10);
	cout << "*it2 = " << *it2 << endl;
	++it2;
	cout << "*it2 = " << *it2 << endl;
	display(numbers);

	//ɾ��Ԫ��
	//list�ĵ�������֧��+��-�����
	//listֻ֧��˫����ʵ����� ++��--
	auto it3 = it2;
	++it3; ++it3; ++it3;
	numbers.erase(it2, it3);
	display(numbers);

	//���Ԫ��
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	//listû��capacity����
	//listû��shrink_to_fit����
	display(numbers);
}



int main()
{
	test0();
	test1();
	test2();
	return 0;
}