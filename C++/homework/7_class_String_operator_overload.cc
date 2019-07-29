/*实现String类的其它运算符的重载*/
//在day2作业的基础上进行修改
#include <string.h>
#include <iostream>
#include <limits>
using std::cout;
using std::endl;
using std::size_t;

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
        cout << "String(const char *)//构造" << endl;
        strcpy(_pstr,pstr);
    }

    String(const String & rhs)//复制
    : _pstr( new char[strlen(rhs._pstr)+1]() )
    {
        strcpy(_pstr,rhs._pstr);
    }

    ~String()//析构
    {
        cout << "~String()//析构" << endl;
        if(_pstr){
            delete [] _pstr;
        }
    }

    String & operator=(const String & rhs)//赋值
    {
        if( this != &rhs ){
            delete [] _pstr;
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }

    String &operator=(const char * pstr)//赋值
    {
        if(_pstr){
            delete [] _pstr;
        }
        _pstr = new char[strlen(pstr)+1]();
        strcpy(_pstr,pstr);
        return *this;
    }

    String &operator+=(const String &rhs)//+=
    {
        if(_pstr){
            String temp = *this;
            delete [] _pstr;
            _pstr = new char[strlen(temp._pstr)+strlen(rhs._pstr)+1]();
            strcpy(_pstr,temp._pstr);
            strcat(_pstr,rhs._pstr);
        } else {
            _pstr = new char[strlen(rhs._pstr)+1]();
            strcpy(_pstr,rhs._pstr);
        }
        return *this;
    }

    String &operator+=(const char * pstr)//+=
    {
        if(_pstr){
            String temp = *this;
            delete [] _pstr;
            _pstr = new char[strlen(temp._pstr)+strlen(pstr)+1]();
            strcpy(_pstr,temp._pstr);
            strcat(_pstr,pstr);
        } else {
            _pstr = new char[strlen(pstr)+1]();
            strcpy(_pstr,pstr);
        }
        return *this;
    }

    char &operator[](size_t index)//[]
    {
        if( _pstr && index<strlen(_pstr) ){
            return _pstr[index];
        } else {
            static char nullchar = 0;
            return nullchar;
        }
    }

    const char &operator[](size_t index) const//[]
    {
        return _pstr[index];
    }

    size_t size() const//长度
    {
        if(_pstr){
            return strlen(_pstr);
        } else {
            return 0;
        }
    }

    const char* c_str() const
    {
        return _pstr;
    }

    void print() const//打印
    {
        if(_pstr){
            cout << _pstr << endl;
        } else {
            cout << "<NULL>" << endl;
        }
    }

    /*友元函数*/
    friend bool operator==(const String & lhs, const String & rhs);
    friend bool operator!=(const String &, const String &);

    friend bool operator<(const String &, const String &);
    friend bool operator>(const String &, const String &);
    friend bool operator<=(const String &, const String &);
    friend bool operator>=(const String &, const String &);
    
    friend std::ostream &operator<<(std::ostream &os, const String &s);
    friend std::istream &operator>>(std::istream &is, String &s);

private:
    char *_pstr;
};


bool operator==(const String & lhs, const String & rhs)
{
    if(strcmp(lhs._pstr,rhs._pstr)){
        return false;
    } else {
        return true;
    }
}

bool operator!=(const String & lhs, const String & rhs)
{
    return !(lhs==rhs);
}

bool operator<(const String & lhs, const String & rhs)
{
    if( strcmp(lhs._pstr,rhs._pstr) < 0){
        return true;
    } else {
        return false;
    }
}

bool operator>(const String & lhs, const String & rhs)
{
    if( strcmp(lhs._pstr,rhs._pstr) > 0){
        return true;
    } else {
        return false;
    }
}
    
bool operator<=(const String & lhs, const String & rhs)
{
    return ( lhs<rhs || lhs==rhs );
}

bool operator>=(const String & lhs, const String & rhs)
{
    return ( lhs>rhs || lhs==rhs );
}
    
std::ostream &operator<<(std::ostream &os, const String &s)
{
    os << s._pstr;
    return os;
}

void readString(std::istream &is, char * str)
{
    cout << "请输入字符串：" << endl;
    while( is>>str, !is.eof() ){
        if( is.bad() ){
            cout << "istream has corrupted" << endl;
            return;
        } else if( is.fail() ){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            cout << "请输入字符串：" << endl;
            continue;
        }
        break;
    }
}

std::istream &operator>>(std::istream &is, String &s)
{
    char str[1000];
    readString(is, str);
    s = str;
    return is;
}

String operator+(const String &lhs, const String &rhs)
{
    char * pstr = new char[ lhs.size() + rhs.size() + 1 ]();
    strcpy(pstr,lhs.c_str());
    strcat(pstr,rhs.c_str());
    String str(pstr);
    return str;
}

String operator+(const String & lhs, const char * cstr)
{
    char * pstr = new char[ lhs.size() + strlen(cstr) + 1 ]();
    strcpy(pstr,lhs.c_str());
    strcat(pstr,cstr);
    String str(pstr);
    return str;
}

String operator+(const char * cstr, const String & rhs)
{
    char * pstr = new char[ rhs.size() + strlen(cstr) + 1  ]();
    strcpy(pstr,cstr);
    strcat(pstr,rhs.c_str());
    String str(pstr);
    return str;
}


/*以下为测试用代码*/
int test0()
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

void test1()
{
    String str1;
    str1 = "Hello, wangdao! ";
    cout << "str1 = " << str1 << endl;

    String str2;
    str2 += "GoodBye!";
    cout << "str2 = " << str2 << endl;
    str1 += "Nice to meet you! ";
    cout << "str1 = " << str1 << endl;
    str1 += str2;
    cout << "str1 = " << str1 << endl;

    str2[0] = 'g';
    str2[str2.size()] = '~';
    str2[str2.size()-1] = '~';
    cout << "str2 = " << str2 << endl;
    
    cout << "str2 = ";
    for( size_t idx=0; idx<str2.size(); ++idx )
    {
        cout << str2[idx];
    }
    cout << endl;

    String str3 = str2.c_str();
    cout << "str3 = " << str3 << endl;
    cout << "str3==str2? " << (str3==str2) << endl;
    cout << "str3!=str2? " << (str3!=str2) << endl;
    cout << "str3>str2? " << (str3>str2) << endl;
    cout << "str3<str2? " << (str3<str2) << endl;
    cout << "str3>=str2? " << (str3>=str2) << endl;
    cout << "str3<=str2? " << (str3<=str2) << endl;

    str3 = "Nice to meet you!";
    cout << "str3 = " << str3 << endl;
    cout << "str3==str2? " << (str3==str2) << endl;
    cout << "str3!=str2? " << (str3!=str2) << endl;
    cout << "str3>str2? " << (str3>str2) << endl;
    cout << "str3<str2? " << (str3<str2) << endl;
    cout << "str3>=str2? " << (str3>=str2) << endl;
    cout << "str3<=str2? " << (str3<=str2) << endl;

    std::cin >> str3;
    cout << "str3 = " << str3 << endl;
    cout << "str3==str2? " << (str3==str2) << endl;
    cout << "str3!=str2? " << (str3!=str2) << endl;
    cout << "str3>str2? " << (str3>str2) << endl;
    cout << "str3<str2? " << (str3<str2) << endl;
    cout << "str3>=str2? " << (str3>=str2) << endl;
    cout << "str3<=str2? " << (str3<=str2) << endl;

    str3 = str1 + str2;
    cout << "str3 = " << str3 << endl;
    str3 = str1 + "HA!";
    cout << "str3 = " << str3 << endl;
    str3 = "HA?" + str2;
    cout << "str3 = " << str3 << endl;
}


int main()
{
    //test0();
    test1();
    return 0;
}
