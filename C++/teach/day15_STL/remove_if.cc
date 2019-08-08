#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
using std::cout;
using std::endl;
using std::vector;
using std::remove;
using std::ostream_iterator;

int test0()
{
	vector<int> numbers{ 5,3,1,2,66,7,1,66,8,9,66 };
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	//执行remove的过程中，没有直接删除元素，而是将后面元素往前移
	//
	//remove的实现不是针对某一种容器，直接删除元素有可能会导致迭代器范围出现问题
	//
	remove(numbers.begin(), numbers.end(), 66);
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	return 0;
}

void test1()
{
	vector<int> numbers;
	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;

	numbers.push_back(1);
	cout << "numbers.size() = " << numbers.size() << endl;
	cout << "numbers.capacity() = " << numbers.capacity() << endl;

	bool flag = true;


	//在遍历元素的过程中，做了添加元素的操作，
	//该操作导致底层元素存放的位置发生了变化，
	//从而导致迭代器失效的问题
	//
	//注意：一般情况下，在遍历容器元素的过程中，
	//不要轻易做添加或者删除的操作，
	//除非很确定不会造成迭代器失效的问题
	auto it = numbers.begin();
	for (; it != numbers.end(); ++it) {
		cout << *it << " ";
		if (flag) {
			numbers.push_back(2);
			flag = false;
		}
	}
}

int main()
{
	//test0();
	test1();

	return 0;
}


#if 0
void display(int &number)
{
	++number;
	cout << number << " ";
}

void test0()
{
	vector<int> numbers{ 1,2,3,4,5 };

	//std::for_each(numbers.begin(), numbers.end(), display);

	//lambda表达式 ==> 匿名函数
	std::for_each(numbers.begin(), numbers.end(), [](int number){
		//cout << numbers.size() << endl;
		cout << number << " ";
		});
	cout << endl;

	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}

void test1()
{
	vector<int> numbers{ 7,1,2,6,8,9,3,4,5 };
	//对线性容器进行查找时，要采用的是std::find/std::count
	//其时间复杂度为O(N)
	auto it = std::find(numbers.begin(), numbers.end(), 3);
	cout << "*it = " << *it << endl;

	//为了提高查找速度，可以先排序，再进行查找
	//
	//sort默认情况下按照升序排序
	std::greater<int> gt;
	std::sort(numbers.begin(), numbers.end(), gt);
	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;

	//此时使用lower_bound，时间复杂度O(logN)
	auto it2 = std::lower_bound(numbers.begin(), numbers.end(), 3, gt);
	cout << "*it2 = " << *it2 << endl;
}

int main()
{
	//test0();
	test1();
	return 0;
}
#endif