#include <iostream>
#include <vector>
#include <iterator>
#include <algorithm>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::copy;
using std::ostream_iterator;
using std::istream_iterator;


int main()
{
	vector<int> numbers;
	//cout << "111" << endl;//利用打印方式找到段错误出现位置

	istream_iterator<int> isi(cin);
	//cout << "222" << endl;

	//int number;
	//cin >> number;
	//numbers.push_back(number);

	//begin、end是用来遍历元素的
	//copy(isi, istream_iterator<int>(), numbers.begin());
	//这里需要使用插入迭代器
	copy(isi, istream_iterator<int>(), std::back_inserter(numbers));
	//cout << "333" << endl;

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	//cout << "444" << endl;
	cout << endl;


	return 0;
}