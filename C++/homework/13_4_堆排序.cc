/*
**4. 实现一个堆排序算法**
可选择使用模板或非模板的实现：

使用模板的框架如下：
	template <typename T, typename Compare = std::less<T> >
	class HeapSort
	{
	public:
		void heapAdjust();
		void sort();
	private:
		//...
	};
*/

#include <iostream>
using std::cout;
using std::endl;

template <typename T>
class HeapSort
{
public:
	HeapSort(T *a,int amount)
		: _a(a)
		, _amount(amount)
	{}

	void sort() 
	{
		int i;
		for (i = _amount / 2 - 1; i >= 0; --i)
		{
			heapAdjust(i, _amount);
		}//把整个数组调整为一个大根堆
		T temp = *_a;
		*_a = *(_a + _amount - 1);
		*(_a + _amount - 1) = temp;
		for (i = _amount - 1; i > 1; --i)
		{
			heapAdjust(0, i);
			temp = *_a;
			*_a = *(_a + i - 1);
			*(_a + i - 1) = temp;
		}
	}

private:
	void heapAdjust(int adjustNode, int arrLen)
	{
		int father = adjustNode;
		int son = father * 2 + 1;
		while (son < arrLen) {
			if (son + 1 < arrLen) {
				if (*(_a + son) < *(_a + son + 1)) {
					++son;
				}
			}
			if (*(_a + father) < *(_a + son)) {
				T temp = *(_a + son);
				*(_a + son) = *(_a + father);
				*(_a + father) = temp;
				father = son;
				son = father * 2 + 1;
			}
			else {
				break;
			}
		}
	}

private:
	T* _a;
	int _amount;
};

//只写了一个简单的int数组测试
//其他的类型需要重载更多的东西
int test_int()
{
	int arr[10] = { 3,7,5,4,9,2,6,9,1,8 };
	HeapSort<int> hs(arr, 10);
	hs.sort();
	for (auto& elem : arr) {
		cout << elem << " ";
	}
	cout << endl;

	return 0;
}

int main() {
	test_int();	
	return 0;
}