/*
 * 4-4 *
 统计一篇英文(The_Holy_Bible.txt)文章中出现的单词和词频，
   输入：某篇文章的绝对路径
   输出：词典（词典中的内容为每一行都是一个“单词 词频”）

   词典的存储格式如下
 -----------------
|   a 66          |
|   abandon 77    |
|   public 88     |
|    ......	      |
|_________________|

* 12-1 *
 词频统计的作业再用map/unordered_map容器去实现一次，
 体验一下使用vector/map/unordered_map时程序执行的速度

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

int Method0_vector()//这是上一次写这题时用的代码
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

	//得到文件路径
	string path;
	cout << "输入某篇文章的绝对路径：" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//开始计时
	clock_t start, end;
	start = clock();

	//读文件
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "打开文件出错！请确认文件路径是否正确" << endl;
		return -1;
	}

	vector<WordCount> Wordv;

	string word;
	bool flag = 0;
	while (ifs >> word)
	{
		if (word.at(0) >= '0' && word.at(0) <= '9')//判断这个单词是不是数字
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
		cout << "创建文件dictionary.txt出错!" << endl;
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

	//程序结束计时
	end = clock();
	cout << "总用时：" << (double)(end - start)/1000000 << "s" << endl;

	return 0;
}

int Method1_map()
{

	//得到文件路径
	string path;
	cout << "输入某篇文章的绝对路径：" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//开始计时
	clock_t start, end;
	start = clock();

	//读文件
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "打开文件出错！请确认文件路径是否正确" << endl;
		return -1;
	}

	map<string, int> dictionary;
	string word;
	while (ifs >> word) {
		if (word[0] >= '0' && word[0] <= '9')//如果这个字符串是数字
		{
			continue;
		}
		dictionary[word]++;
	}

	ofstream ofs("dictionary.txt");
	if (!ofs)
	{
		cout << "创建文件dictionary.txt出错!" << endl;
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

	//程序结束计时
	end = clock();
	cout << "总用时：" << (double)(end - start)/1000000 << "s" << endl;

	return 0;
}

int Method2_unordered_map()
{

	//得到文件路径
	string path;
	cout << "输入某篇文章的绝对路径：" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

	//开始计时
	clock_t start, end;
	start = clock();

	//读文件
	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "打开文件出错！请确认文件路径是否正确" << endl;
		return -1;
	}

	unordered_map<string, int> dictionary;
	string word;
	while (ifs >> word) {
		if (word[0] >= '0' && word[0] <= '9')//如果这个字符串是数字
		{
			continue;
		}
		dictionary[word]++;
	}

	ofstream ofs("dictionary.txt");
	if (!ofs)
	{
		cout << "创建文件dictionary.txt出错!" << endl;
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

	//程序结束计时
	end = clock();
	cout << "总用时：" << (double)(end - start)/1000000 << "s" << endl;

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
