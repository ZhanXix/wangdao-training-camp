#include <iostream>
#include <set>
using std::cout;
using std::endl;
using std::set;

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
	set<int> numbers;
	cout << "numbers' size = " << numbers.size() << endl;

	numbers.insert(1);
	numbers.insert(2);
	numbers.insert(3);
	display(numbers);
}

void test1()
{
	int arr[10] = { 3,6,1,2,6,5,7,9,8,3 };

	//set默认情况下是按照升序方式进行排列
	//set中不能存放关键字相同的元素
	//
	//底层实现：采用红黑树(rb-tree) ==> 近似平衡二叉树(AVL)
	//			==> 查找一个元素的时间复杂度为O(logN) ==> 二分查找
	//
	//红黑树特点：
	//	1.节点不是红色就是黑色
	//	2.根节点是黑色的
	//	3.叶子结点都是黑色的（空结点）
	//	4.不能有连续的两个结点是红色的
	//	5.从根节点到任意一个结点，路径上的黑色节点数目相同
	set<int> numbers(arr, arr + 10);
	display(numbers);

	//set不支持下标访问运算符
	//numbers[0];//error

	set<int>::iterator it = numbers.begin();
	//*it = 10;//error: 放入set中的元素无法进行修改，都是只读的
	numbers.erase(it);//可以删除
	display(numbers);
}

int main()
{
	//test0();
	test1();
	return 0;
}