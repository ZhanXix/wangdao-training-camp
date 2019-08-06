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
int test0()	//���Ը÷����Ƿ����
{
	string path;
	cout << "�����ļ�����" << endl;
	cin >> path;

	ifstream ifs;
	ifs.open(path);
	if (!ifs) {
		cout << "���ļ�" << path << "ʧ��!" << endl;
		return 0;
	}

	unordered_map<int, string> lines;	//�洢ԭʼ��
	map<string, set<int>> word2Line;	//��¼ÿ���������ڵ�������
	map<string, int> dict;	//��¼���ʳ��ֵĴ���

	
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

		//ȥ�����еĵķ��������֣������µ���
		//���ҰѴ�д��ĸ��Ϊ��Сд��ĸ
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

//��װ����ӿ�
class TextQuery
{
public:
	void readFile(const string filename);
	void query(const string& word);

private:
	unordered_map<int, string> _lines;//�洢ԭʼ��
	map<string, set<int>> _word2Line;//��¼ÿ���������ڵ�������
	map<string, int> _dict;//��¼���ʳ��ֵĴ���
};

void TextQuery::readFile(const string filename) {
	ifstream ifs;
	ifs.open(filename);
	if (!ifs) {
		cout << "���ļ�" << filename << "ʧ��!" << endl;
		return;
	}

	string line;
	stringstream ss;
	string word;
	int row = 0;

	//���ļ�
	while (std::getline(ifs, line)) {
		++row;
		_lines.insert(std::make_pair(row, line));

		if (!line.size()) {
			continue;
		}

		//ȥ�����еĵķ��������֣������µ���
		//���ҰѴ�д��ĸ��Ϊ��Сд��ĸ
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
		while (ss >> word, !ss.eof()) {	//����stringstream�ִ�
			_word2Line[word].insert(row);
			_dict[word]++;
		}
		ss.clear();
	}

	cout << ">>>���ļ��ɹ�" << endl;
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
	cout << "�����ļ�����" << endl;
	cin >> filename;

	tq.readFile(filename);

	string queryWord;
	cout << "����Ҫ��ѯ�ĵ��ʣ�" << endl;
	cin >> queryWord;
	tq.query(queryWord);

	return 0;
}