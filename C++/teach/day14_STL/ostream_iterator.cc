#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::ostream_iterator;


int main()
{
	vector<int> numbers{ 1,2,3,4,5 };

	for (auto& elem : numbers) {
		cout << elem << " ";
	}
	cout << endl;

	//适配器设计模式
	//ostream_iterator是来模拟迭代器
	ostream_iterator<int> osi(cout, " ");
	copy(numbers.begin(), numbers.end(), osi);
	cout << endl;

	return 0;
}