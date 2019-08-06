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
	//得到文件路径
	string path;
	cout << "输入某篇文章的绝对路径：" << endl;
	cin >> path;
	//D:\Documents\Code\Cpp\CPP\The_Holy_Bible.txt

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
	return 0;
}