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

    ~Computer()
    {
        if(_brand)
            delete [] _brand;

        cout << "~Computer()" << endl;
    }

    Computer(const Computer &rhs)
        : _brand(new char[strlen(rhs._brand+1)]()) //深拷贝
        , _price(rhs._price)
    {
        cout << "Computer(const Computer &)" << endl;
        strcpy(_brand,rhs._brand);
    }

    //系统提供的赋值函数不再满足需求
    //Computer &operator=(const Computer &rhs)
    //{
    //    _brand=rhs._brand;
    //    _price=rhs._price;
    //
    //    cout << "Computer &operator=(const Computer &rhs)" << endl;
    //    return *this;
    //}
    //需要显式提供赋值运算符函数
    //最容易出错
    Computer &operator=(const Computer &rhs)
    {
        if(this != &rhs)//考虑自复制的情况
        {
            delete [] _brand;//回收左操作数申请的空间
            //再进行深拷贝
            _brand = new char[strlen(rhs._brand)+1]();
            strcpy(_brand,rhs._brand);

            _price=rhs._price;

            cout << "Computer &operator=(const Computer &rhs)" << endl;
        }
        return *this;
    }

private:
    char *_brand;
    float _price;
};


inline void Computer::print()
{
    printf("brand = %p\n",_brand);
    cout << "brand: " << _brand << endl
        << "price: " << _price << endl;
}

void test1()
{
    Computer pc("Thinkpad",8888);
    cout << "pc = ";
    pc.print();

    Computer pc2 = pc; //调用复制（拷贝）构造函数
    //等价于Computer pc2(pc);
    cout << "pc2 = ";
    pc2.print();
}

Computer getComputer()
{
    Computer pc3("Xiaomi",7500);
    cout << "pc3 = ";
    pc3.print();
    return pc3;
}

void test2()
{
    getComputer();//临时对象，非持久化对象 (没有写回到内存)
    //右值：无法取地址

    //int & ref = 1; // 1 字面值，右值，无法绑定
    //只有const引用能绑定到右值
    const int & ref = 1;
    cout << "ref = " << ref << endl;

    Computer pc4 = getComputer();
    cout << "pc4 = ";
    pc4.print();
}

void test3()
{
    Computer pc1("Thinkpad",8888);
    Computer pc2("Xiaomi",8888);

    pc2 = pc1;
    //pc2.operator()=pc1;
    cout << "执行赋值语句之后：" << endl;
    cout << "pc1 = ";
    pc1.print();
    cout << "pc2 = ";
    pc2.print();

    int a = 3, b = 4;
    a = (a = b); //自复制情况，需要考虑
}

int main()
{
    test3();
    return 0;
}

