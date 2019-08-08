#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <functional>
using std::cout;
using std::endl;
using std::vector;
using std::replace_if;
using std::ostream_iterator;

bool compare(int number)
{
	return number > 3;
}

void test0()
{
	vector<int> numbers{ 1,2,3,4,5,6 };
	
	std::less<int> lt;//需要传递2个参数才能完成调用
	cout << lt(3, 4) << endl;
	cout << lt(5, 4) << endl;
	std::greater<int> gt;
	//replace_if(numbers.begin(), numbers.end(), compare, 7);
	
	//std::bind1st  std::bind2nd  都是用来提前给函数绑定参数的
	replace_if(numbers.begin(), numbers.end(), std::bind1st(lt, 3), 7);
	//replace_if(numbers.begin(), numbers.end(), std::bind2nd(lt, 3), 7);

	std::copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	cout << endl;
}


int main()
{
	test0();
	//test1();

	return 0;
}