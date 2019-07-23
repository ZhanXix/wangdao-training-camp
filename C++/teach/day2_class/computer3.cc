#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char * brand,float price)
    : _brand(new char[strlen(brand)+1]())
    , _price(price)
    {
        strcpy(_brand,brand);
        cout << "Computer(const char*, float)" << endl;
    }
    
    void print();

    //系统提供的析构函数什么都没有，不满足需求
    //我们需要delete在堆空间开辟的区域，否则会出现内存泄漏
    //
    ~Computer()
    {//析构函数的作用是用来清理对象开辟出来的资源
        if(_brand)
            delete [] _brand;

        cout << "~Computer()" << endl;
    }

private:
    char *_brand;
    float _price;
};


inline void Computer::print()
{
    cout << "brand: " << _brand << endl
        << "price: " << _price << endl;
}

Computer gPc("Xiaomi",7500);


int test0()
{

    cout <<  "sizeof(Computer) = " << sizeof(Computer) << endl;
    Computer pc("ThinkPad",8888);
    cout << "pc = ";
    pc.print();

    Computer pc2("ACER",6666);
    cout << "pc2 = ";
    pc2.print();

    gPc.print();

    static Computer pc3("Lenovo",5555);
    pc3.print();

    Computer * pc4 = new Computer("MateBook",7500);
    pc4->print();

    delete pc4;

    return 0;
}

int main()
{
    test0();
    return 0;
}

