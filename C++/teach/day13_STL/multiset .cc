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
	numbers.erase(it);//可以删除
	display(numbers);

	//添加元素:
	//multiset能添加相同元素，不会添加失败
	auto ret = numbers.insert(2);
	cout << "添加元素成功！" << endl;
	cout << *ret << endl;

	//查找元素：
	if (numbers.count(1) > 0) {
		cout << "查找元素成功" << endl;
	}
	else {
		cout << "multiset中没有该元素" << endl;
	}

	auto it2 = numbers.find(3);
	if (it2 == numbers.end()) {
		cout << "multiset中没有该元素" << endl;
	}
	else {
		cout << "查找元素成功" << endl;
		cout << "*it2 = " << *it2 << endl;
	}

	//范围查找：
	//lowerbound 下边界 [ 
	//upperbound 上边界 )
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