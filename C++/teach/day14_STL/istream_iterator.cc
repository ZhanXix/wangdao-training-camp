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
	//cout << "111" << endl;//���ô�ӡ��ʽ�ҵ��δ������λ��

	istream_iterator<int> isi(cin);
	//cout << "222" << endl;

	//int number;
	//cin >> number;
	//numbers.push_back(number);

	//begin��end����������Ԫ�ص�
	//copy(isi, istream_iterator<int>(), numbers.begin());
	//������Ҫʹ�ò��������
	copy(isi, istream_iterator<int>(), std::back_inserter(numbers));
	//cout << "333" << endl;

	copy(numbers.begin(), numbers.end(), ostream_iterator<int>(cout, " "));
	//cout << "444" << endl;
	cout << endl;


	return 0;
}