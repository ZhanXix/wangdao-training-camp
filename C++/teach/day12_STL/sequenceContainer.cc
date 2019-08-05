//线性容器

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
	//vector<int> numbers(array, array + 5);//迭代器范围是一个左闭右开的区间[beg, end)
	vector<int> numbers{ 1,2,3,4,5 };
	display(numbers);

	numbers.push_back(6);//O(1)
	display(numbers);
	//vector没有在头部添加和删除元素的操作
	//如果vector提供push_front/pop_front
	//都会导致所有元素移动一次，其时间复杂度为O(n)

	cout << "numbers[2] = " << numbers[2] << endl;

	//添加元素
	//
	//强调：对于vector来说，执行写操作之后，
	//都需要重新更新迭代器的位置，有可能迭代器出现bug
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

	//删除元素
	numbers.erase(it2, it2 + 3);
	display(numbers);

	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;
	//清空元素
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;
	numbers.shrink_to_fit();//释放多余空间
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

	//deque支持下标访问运算符（支持随机访问）
	cout << "numbers[2] = " << numbers[2] << endl;

	//添加元素
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

	//删除元素
	numbers.erase(it2, it2 + 3);
	display(numbers);

	//清空元素
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	//deque没有capacity方法
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

	//list不支持下标访问运算符（不支持随机访问）

	//添加元素
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

	//删除元素
	//list的迭代器不支持+、-运算符
	//list只支持双向访问迭代器 ++、--
	auto it3 = it2;
	++it3; ++it3; ++it3;
	numbers.erase(it2, it3);
	display(numbers);

	//清空元素
	numbers.clear();
	cout << "numbers.size() = " << numbers.size() << endl;
	//list没有capacity方法
	//list没有shrink_to_fit方法
	display(numbers);
}



int main()
{
	test0();
	test1();
	test2();
	return 0;
}