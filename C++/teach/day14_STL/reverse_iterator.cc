#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;


int main()
{
	vector<int> numbers{ 1,2,3,4,5 };
	
	//µü´úÆ÷ÊÊÅäÆ÷
	vector<int>::reverse_iterator rit = numbers.rbegin();
	for (; rit != numbers.rend(); ++rit) {
		cout << *rit << " ";
	}
	cout << endl;

	return 0;
}