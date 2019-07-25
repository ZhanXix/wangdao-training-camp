#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>
using std::cout;
using std::endl;
using std::string;
using std::istringstream;
using std::ostringstream;
using std::stringstream;
using std::ifstream;
using std::vector;

void printStreamStatus(stringstream & ss)
{
    cout << "ss's badbit = " << ss.bad() << endl;
    cout << "ss's failbit = " << ss.fail() << endl;
    cout << "ss's eofbit = " << ss.eof() << endl;
    cout << "ss's goodbit = " << ss.good() << endl;
}

//做格式转换
//  把其他类型的数据转换成字符串
//  把字符串转换成其他类型数据
void test0()
{
    stringstream ss;
    int number1 = 100;
    int number2 = 101;

    //当成字符串输出流使用
    ss << "number1= " << number1
        << " number2= " << number2;

    string line = ss.str();
    cout << line;

    string key;
    int value;

    while(!ss.eof())
    {
        //当成字符串输入流使用
        ss >> key >> value;
        printStreamStatus(ss);
        cout << key << "--->" << value << endl;
    }
}

string int2str(int number)
{
    ostringstream oss;
    oss << number;
    return oss.str();
}

void readConfid(const string &filename)
{
    ifstream ifs(filename);
    if(!ifs)
    {
        cout << "ifstream open file " << filename << " error" << endl;
        return;
    }

    string line;
    struct Info
    {
        Info(const string &k, const string &v)
        : key(k)
        , value(v)
        {}

        string key;
        string value;
    };

    vector<Info> config;
    while(getline(ifs, line))
    {
        istringstream iss(line);
        string key, value;
        while(!iss.eof())
        {
            iss >> key >> value;
            config.push_back(Info(key,value));
        }
    }

    for(auto & info : config)
    {
        cout << info.key << "--->" << info.value << endl;
    }
}

int main()
{
    //test0();
    string filename="config";
    readConfid(filename);
    return 0;
}

