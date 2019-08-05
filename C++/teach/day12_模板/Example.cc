#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::vector;

class Example
{
public:
	Example(int size)
		: _size(size)
		, _cnt(0)
		, _data(new int[_size]())
	{}

	//成员函数模板
	//
	//迭代器 当成一个指针来使用
	//
	template <class Iterator>
	void setData(Iterator beg, Iterator end)
	{
		while (beg != end && _cnt < _size) {
			_data[_cnt] = *beg;
			++beg;
			++_cnt;
		}
	}

	void display() const
	{
		for (int idx = 0; idx != _cnt; ++idx) {
			cout << _data[idx] << " ";
		}
		cout << endl;
	}

private:
	int _size;
	int _cnt;
	int* _data;
};

int main()
{
	vector<int> numbers(10, 1);

	Example e(10);
	e.setData(numbers.begin(), numbers.end());
	e.display();

	int arr[10] = { 1,2,3,4,5,6,7,8,9,10 };
	Example e2(10);
	e2.setData(arr, arr + 10);
	e2.display();

	return 0;
}