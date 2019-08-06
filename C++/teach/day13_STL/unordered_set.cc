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
	//unordered_set元素是无序的
	//内部不能存放关键字相同的元素
	int array[10] = { 8,7,1,2,5,9,0,8,7,3 };
	unordered_set<int> numbers(array, array + 10);
	display(numbers);

	auto it = numbers.begin();
	cout << *it << endl;
	++it;//前向访问迭代器。只能向前遍历(++)，不能向后(--)
	cout << *it << endl;
	//--it;//error  （实验证明，在windows下面是可以--的，linux里会报错）
	//cout << *it << endl;

	auto it2 = numbers.find(9);
	if (it2 != numbers.end()) {
		cout << *it2 << endl;
	}
	else {
		cout << "查找元素失败" << endl;
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