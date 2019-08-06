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
#include <vector>
#include <map>
#include <unordered_map>
#include <string>
#include <ctime>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using std::vector;
using std::map;
using std::unordered_map;
using std::string;

int Method0_vector()//������һ��д����ʱ�õĴ���
{
	class WordCount
	{
	public:
		WordCount(string word)
			: _count(1)
			, _word(word)
		{}

		bool is_same(string word) const
		{
			if (_word == word)
			{
				return true;
			}
			else {
				return false;
			}
		}

		void add_count()
		{
			++_count;
		}

		void print() const
		{
			cout << "|   " << _word << " " << _count << endl;
		}

		void print(ofstream& ofs) const
		{
			ofs << "|   " << _word << " " << _count << endl;
		}

	private:
		int _count;
		string _word;
	};

	//�õ��ļ�·��
	string path;
	cout << "����ĳƪ���µľ���·����" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//��ʼ��ʱ
	clock_t start, end;
	start = clock();

	//���ļ�
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "���ļ�������ȷ���ļ�·���Ƿ���ȷ" << endl;
		return -1;
	}

	vector<WordCount> Wordv;

	string word;
	bool flag = 0;
	while (ifs >> word)
	{
		if (word.at(0) >= '0' && word.at(0) <= '9')//�ж���������ǲ�������
		{
			continue;
		}
		for (auto& w : Wordv)
		{
			if (w.is_same(word))
			{
				w.add_count();
				flag = 1;
				break;
			}
		}
		if (0 == flag)
		{
			WordCount newWord(word);
			Wordv.push_back(newWord);
		}
		flag = 0;
	}

	ofstream ofs("dictionary.txt");
	if (!ofs)
	{
		cout << "�����ļ�dictionary.txt����!" << endl;
		return -1;
	}

	ofs << "------------------" << endl;
	for (auto& w : Wordv)
	{
		w.print(ofs);
	}
	ofs << "------------------" << endl;

	ifs.close();
	ofs.close();

	//���������ʱ
	end = clock();
	cout << "����ʱ��" << (double)(end - start)/1000000 << "s" << endl;

	return 0;
}

int Method1_map()
{

	//�õ��ļ�·��
	string path;
	cout << "����ĳƪ���µľ���·����" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//��ʼ��ʱ
	clock_t start, end;
	start = clock();

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

	//���������ʱ
	end = clock();
	cout << "����ʱ��" << (double)(end - start)/1000000 << "s" << endl;

	return 0;
}

int Method2_unordered_map()
{

	//�õ��ļ�·��
	string path;
	cout << "����ĳƪ���µľ���·����" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//��ʼ��ʱ
	clock_t start, end;
	start = clock();

	//���ļ�
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "���ļ�������ȷ���ļ�·���Ƿ���ȷ" << endl;
		return -1;
	}

	unordered_map<string, int> dictionary;
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

	//���������ʱ
	end = clock();
	cout << "����ʱ��" << (double)(end - start)/1000000 << "s" << endl;

	return 0;
}

int main()
{
	cout << "Method0_vector()" << endl;
	Method0_vector();
	cout << "Method1_map()" << endl;
	Method1_map();
	cout << "Method2_unordered_map()" << endl;
	Method2_unordered_map();

	return 0;
}
