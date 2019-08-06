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

	//setĬ��������ǰ�������ʽ��������
	//set�в��ܴ�Źؼ�����ͬ��Ԫ��
	//
	//�ײ�ʵ�֣����ú����(rb-tree) ==> ����ƽ�������(AVL)
	//			==> ����һ��Ԫ�ص�ʱ�临�Ӷ�ΪO(logN) ==> ���ֲ���
	//
	//������ص㣺
	//	1.�ڵ㲻�Ǻ�ɫ���Ǻ�ɫ
	//	2.���ڵ��Ǻ�ɫ��
	//	3.Ҷ�ӽ�㶼�Ǻ�ɫ�ģ��ս�㣩
	//	4.��������������������Ǻ�ɫ��
	//	5.�Ӹ��ڵ㵽����һ����㣬·���ϵĺ�ɫ�ڵ���Ŀ��ͬ
	set<int> numbers(arr, arr + 10);
	display(numbers);

	//set��֧���±���������
	//numbers[0];//error

	set<int>::iterator it = numbers.begin();
	//*it = 10;//error: ����set�е�Ԫ���޷������޸ģ�����ֻ����
	numbers.erase(it);//����ɾ��
	display(numbers);
}

int main()
{
	//test0();
	test1();
	return 0;
}