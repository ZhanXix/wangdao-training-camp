/*
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
*/

#include <string.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
using std::cin;
using std::cout;
using std::endl;
using std::vector;
using std::ifstream;
using std::ofstream;
using std::fstream;
using std::string;

class WordCount
{
public:
    WordCount(string word)
    : _count(1)
    , _word(word)
    {
        //cout << "add new word: " << word << endl;
    }
    
    bool is_same(string word) const
    {
        if(_word==word)
        {
            return true;
        }else{
            return false;
        }
    }

    void add_count()
    {
        ++_count;
    }

    void print() const
    {
        cout << "|    " << _word << " " << _count << "    |" << endl;
    }
    
    void print(ofstream &ofs) const
    {
        ofs << "|    " << _word << " " << _count << "    |" << endl;
    }

private:
    int _count;
    string _word;
};

int main()
{
    ifstream ifs;
    ifs.open("/home/xz/cpp/homework/The_Holy_Bible.txt");
    if(!ifs)
    {
        cout << "ifstream open file error!" << endl;
        return -1;
    }

    vector<WordCount> Wordv;

    string word;
    bool flag = 0;
    while(ifs >> word/*, !cin.eof()*/)
    {
        if(word.at(0)>='0'&&word.at(0)<='9')//判断这个单词是不是数字
        {
            continue;
        }
        //cout << word << " ";
        for(auto &w : Wordv)
        {
            if(w.is_same(word))
            {
                w.add_count();
                flag = 1;
                break;
            }
        }
        if(0==flag)
        {
            WordCount newWord(word);
            Wordv.push_back(newWord);
        }
        flag = 0;
    }
    //cout << endl;

    ofstream ofs("dictionary.txt");
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return -1;
    }

    ofs << "-----------------" << endl;
    for(auto &w : Wordv)
    {
        w.print(ofs);
    }
    ofs << "-----------------" << endl;

    ifs.close();
    ofs.close();
    return 0;
}

