#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using std::cout;
using std::endl;
using std::vector;
using std::string;
using std::ifstream;
using std::ofstream;
using std::fstream;

//所有的流对象都是不能进行复制的

void printStreamStatus(ifstream & ifs)
{
    cout << "ifs's badbit = " << ifs.bad() << endl;
    cout << "ifs's failbit = " << ifs.fail() << endl;
    cout << "ifs's eofbit = " << ifs.eof() << endl;
    cout << "ifs's goodbit = " << ifs.good() << endl;
}

void printStreamStatus(fstream & fs)
{
    cout << "fs's badbit = " << fs.bad() << endl;
    cout << "fs's failbit = " << fs.fail() << endl;
    cout << "fs's eofbit = " << fs.eof() << endl;
    cout << "fs's goodbit = " << fs.good() << endl;
}

vector<string> file;

void test0()
{
    ifstream ifs;
    //文件输入流要求文件必须存在
    ifs.open("config");
    printStreamStatus(ifs);
    //if(!ifs.good()){
    if(!ifs)
    {
        cout << "ifstream open file error!" << endl;
        return;
    }

    string line;
    //while(ifs >> word){ //输入流运算符默认情况下是以空格作为分隔符的
    //
    //C风格得到一行的写法：
    //char buff[1000] = {0};
    //ifs.getline(buff,1000);
    //
    while(std::getline(ifs,line))
    {
        file.push_back(line);
        //cout << line << endl;
    }

    for(auto &line : file)
    {
        cout << line << endl;
    }

    ifs.close();
}

void test1()
{
    //ofstream并不要求文件存在，当文件不存在时，直接创建新文件
    //当文件存在时，会直接清空文件的内容
    ofstream ofs("config");
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return;
    }

    for(auto &line : file)
    {
        ofs << line << "\n";
    }

    cout << "test1() end" << endl;

    ofs.close();
}

void test2()
{
    ofstream ofs("config", std::ios::app);
    if(!ofs)
    {
        cout << "ofstream open file error!" << endl;
        return;
    }
    cout << "ofs.tellp() = " << ofs.tellp() << endl;

    ofs << "this is a new line\n";

    ofs.close();
}

void test3()
{
    string filename("file.txt");
    fstream fs(filename);
    if(!fs)
    {
        cout << "fstream open file " << filename << " error" << endl;
        return;
    }

    int number = -1;
    for(size_t idx = 0; idx != 10; ++idx)
    {
        std::cin >> number;
        fs << number << " ";
    }
    cout << "number = " << number << endl;

    printStreamStatus(fs);
    cout << "fs.tellg() = " << fs.tellg() << endl;

    //fs.seekg(0);
    fs.seekg(std::ios::beg);

    for(size_t idx = 0; idx != 10; ++idx)
    {
        fs >> number;
        cout << number << " ";
    }
    cout << endl;

    fs.close();
}

void test4()
{
    //把某文件中的内容一次性读完
    string filename = "config";
    ifstream ifs(filename, std::ios::ate);
    if(!ifs)
    {
        cout << "fstream open file " << filename << " error" << endl;
        return;
    }

    int length = ifs.tellg();
    cout << "ifs.tellg() = " << ifs.tellg() << endl;

    ifs.seekg(0);
    char buff[length + 1] = {0};
    ifs.read(buff, length);

    printf("buff = %s\n",buff);

    ifs.close();
}

int main()
{
    //test0();
    //test1();
    
    //test2();
    
    //test3();
    
    test4();

    return 0;
}

