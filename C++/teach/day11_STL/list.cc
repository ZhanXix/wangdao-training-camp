//list���еķ���
#include <iostream>
#include <list>
using std::cout;
using std::endl;
using std::list;

template <class Container>
void display(const Container& c)
{
	typename Container::const_iterator cit = c.begin();
	for (; cit != c.end(); ++cit) {
		cout << *cit << " ";
	}
	cout << endl;
}

struct Greater
{
	bool operator()(const int& lhs, const int& rhs) {
		return lhs > rhs;
	}
};

void test0()	//sort/merge/reverse
{
	list<int> numbers1{ 5,1,10,3,2,8 };
	//numbers1.sort();//Ĭ������°�����������
	display(numbers1);

	//Greater gt0;
	//cout << gt0(1, 2) << endl;
	//cout << gt0(2, 1) << endl;
	//numbers1.sort(gt0);

	std::greater<int> gt;//����
	numbers1.sort(gt);
	display(numbers1);

	list<int> numbers2{ 19,15,13 };

	numbers1.merge(numbers2, gt);
	display(numbers1);
	display(numbers2);
	numbers1.reverse();
	display(numbers1);
}

void test1()	//splice
{
	list<int> numbers1{ 5,1,10,3,2,8 };
	list<int> numbers2{ 19,15,13 };

	//ʱ�临�Ӷ�ΪO(1)
	//numbers1.splice(numbers1.begin(), numbers2);
	display(numbers1);
	display(numbers2);

	auto it = numbers1.begin();
	++it; ++it;

	auto it2 = numbers2.begin();
	++it2; 
	numbers1.splice(it, numbers2, it2);
	display(numbers1);
	display(numbers2);

	it = numbers1.begin();
	it2 = numbers1.end();
	--it2;
	//�ѵ�ǰlist�����һ��λ�õ�Ԫ���Ƶ���ʼλ��
	numbers1.splice(it, numbers1, it2);
	display(numbers1);
}

int main()
{
	//test0();
	test1();
	return 0;
}