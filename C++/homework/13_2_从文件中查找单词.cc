#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <unordered_map>
#include <set>
using std::cin;
using std::cout;
using std::endl;
using std::ifstream;
using std::stringstream;
using std::string;
using std::map;
using std::unordered_map;
using std::set;

#if 0
int test0()	//测试该方法是否可用
{
	string path;
	cout << "输入文件名：" << endl;
	cin >> path;

	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "打开文件" << path << "失败!" << endl;
		return 0;
	}

	unordered_map<int, string> lines;	//存储原始行
	map<string, set<int>> word2Line;	//记录每个单词所在的所有行
	map<string, int> dict;	//记录单词出现的次数

	
	string line;
	stringstream ss;
	string word;
	int row = 0;
	while (std::getline(ifs, line)) {
		++row;

		lines.insert(std::make_pair(row, line));
		
		if (!line.size()) {
			continue;
		}

		//去除这行的的符号与数字，仅留下单词
		//并且把大写字母改为了小写字母
		for (char& c : line) {
			if (c >= 'a' && c <= 'z') {
				continue;
			}
			else if (c >= 'A' && c <= 'Z') {
				c += 32;
			}
			else {
				c = ' ';
			}
		}

		//cout << line << endl;
		ss << line << endl;	
		while (ss >> word, !ss.eof()) {
			//cout << word << endl;
			word2Line[word].insert(row);
			dict[word]++;
		}
		ss.clear();

	}

	for (auto& elem : lines) {
		cout << "(line " << elem.first << ") " << elem.second << endl;
	}
	cout << endl;
	for (auto& elem : word2Line) {
		cout << elem.first << " ";
		for (auto& elem2 : elem.second) {
			cout << elem2 << " ";
		}
		cout << endl;
	}
	cout << endl;
	for (auto& elem : dict) {
		cout << elem.first << " " << elem.second << endl;
	}

	return 0;
}
#endif

//封装程序接口
class TextQuery
{
public:
	void readFile(const string filename);
	void query(const string& word);

private:
	unordered_map<int, string> _lines;//存储原始行
	map<string, set<int>> _word2Line;//记录每个单词所在的所有行
	map<string, int> _dict;//记录单词出现的次数
};

void TextQuery::readFile(const string filename) {
	ifstream ifs;
	ifs.open(filename);
	if (!ifs) {
		cout << "打开文件" << filename << "失败!" << endl;
		return;
	}

	string line;
	stringstream ss;
	string word;
	int row = 0;

	//读文件
	while (std::getline(ifs, line)) {
		++row;
		_lines.insert(std::make_pair(row, line));

		if (!line.size()) {
			continue;
		}

		//去除这行的的符号与数字，仅留下单词
		//并且把大写字母改为了小写字母
		for (char& c : line) {
			if (c >= 'a' && c <= 'z') {
				continue;
			}
			else if (c >= 'A' && c <= 'Z') {
				c += 32;
			}
			else {
				c = ' ';
			}
		}

		ss << line << endl;
		while (ss >> word, !ss.eof()) {	//利用stringstream分词
			_word2Line[word].insert(row);
			_dict[word]++;
		}
		ss.clear();
	}

	cout << ">>>读文件成功" << endl;
}

void TextQuery::query(const string& word)
{
	cout << word << " occurs " << _dict[word] 
		<< " times." << endl;

	for (auto& row : _word2Line[word]) {
		cout << "    (line " << row << ") " 
			<< _lines[row] << endl;
	}
}

int main()
{
	TextQuery tq;

	string filename;
	cout << "输入文件名：" << endl;
	cin >> filename;

	tq.readFile(filename);

	string queryWord;
	cout << "输入要查询的单词：" << endl;
	cin >> queryWord;
	tq.query(queryWord);

	return 0;
}