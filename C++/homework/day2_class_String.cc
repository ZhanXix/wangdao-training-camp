#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
    String()//构造
    : _pstr(NULL)
    {
        cout << "String()//构造" << endl;
    }

    String(const char *pstr)//构造
    : _pstr( new char[strlen(pstr)+1]() )
    {
        strcpy(_pstr,pstr);
        cout << "String(const char *pstr)//构造" << endl;
    }

    String(const String & rhs)//复制
    : _pstr( new char[strlen(rhs._pstr)+1]() )
    {
        strcpy(_pstr,rhs._pstr);
        cout << "String(const String & rhs)//复制" << endl;
    }

    String & operator=(const String & rhs)//赋值
    {
        if( this != &rhs )
        {
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        cout << "String & operator=(const String & rhs)//赋值" << endl;
        return *this;
    }

    ~String()//析构
    {
        if(_pstr)
            delete [] _pstr;
        cout << "~String()//析构" << endl;
    }

    void print()
    {
        if(_pstr)
            cout << _pstr << endl;
        else
            cout << "<NULL>" << endl;
    }

private:
    char *_pstr;
};

int main()
{
    String str1;
    
    cout << "str1 = ";
    str1.print();

    String str2 = "Hello,world";
    String str3("wangdao");

    cout << "str2 = ";
    str2.print();
    cout << "str3 = ";
    str3.print();

    String str4 = str3;
    cout << "str4 = ";
    str4.print();

    str4 = str2;
    cout << "str4 = ";
    str4.print();

    return 0;
}

