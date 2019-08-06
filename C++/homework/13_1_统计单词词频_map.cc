/*
 * 4-4 *
 ͳ��һƪӢ��(The_Holy_Bible.txt)�����г��ֵĵ��ʺʹ�Ƶ��
   ���룺ĳƪ���µľ���·��
   ������ʵ䣨�ʵ��е�����Ϊÿһ�ж���һ�������� ��Ƶ����

   �ʵ�Ĵ洢��ʽ����
 -----------------
|   a 66          |
|   abandon 77    |
|   public 88     |
|    ......	      |
|_________________|

* 12-1 *
 ��Ƶͳ�Ƶ���ҵ����map/unordered_map����ȥʵ��һ�Σ�
 ����һ��ʹ��vector/map/unordered_mapʱ����ִ�е��ٶ�

*/

#include <iostream>
#include <fstream>
#include <map>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::map;
using std::string;

int main()
{
	//�õ��ļ�·��
	string path;
	cout << "����ĳƪ���µľ���·����" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//���ļ�
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "���ļ�������ȷ���ļ�·���Ƿ���ȷ" << endl;
		return -1;
	}


	map<string, int> dictionary;
	string word;
	while (ifs >> word) {
		if (word[0] >= '0' && word[0] <= '9')//�������ַ���������
		{
			continue;
		}
		dictionary[word]++;
	}

	ofstream ofs("dictionary.txt");
	if (!ofs)
	{
		cout << "�����ļ�dictionary.txt����!" << endl;
		return -1;
	}

	int i;
	ofs << "------------------" << endl;
	for (auto& elem : dictionary) {
		ofs << "|   " << elem.first
			<< " " << elem.second << endl;
	}
	ofs << "------------------" << endl;

	ifs.close();
	ofs.close();
	return 0;
}