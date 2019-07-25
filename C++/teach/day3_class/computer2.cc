#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    Computer(const char * brand,double price)
    : _brand(new char[strlen(brand)+1]())
    , _price(price)
    {
        strcpy(_brand,brand);
        _totalPrice += _price;
        cout << "Computer(const char*, float)" << endl;
    }

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

    Computer &operator=(const Computer &rhs)
    {
        if(this != &rhs)//考虑自复制的情况
        {
            delete [] _brand;//回收左操作数申请的空间
            _brand = new char[strlen(rhs._brand)+1]();
            strcpy(_brand,rhs._brand);

            _price=rhs._price;

            cout << "Computer &operator=(const Computer &rhs)" << endl;
        }
        return *this;
    }

#if 0
    void print(/* Computer * const this */)
    {
        cout << "void print()" << endl;
        cout << "brand: " << _brand << endl
            << "price: " << _price << endl;
    }
#endif

    //const成员函数是不能修改数据成员的
    //this指针两边都要const关键字进行保护
    //
    //const成员函数只能调用const成员函数进行保护，
    //不能调用非const成员函数
    void print(/* Computer const * const this */) const
    {
        cout << "void print() const" << endl;
        //this->_price = 10000;//error
        //setPrice(10000);//error
        cout << "brand: " << _brand << endl
            << "price: " << _price << endl;
    }

    void setPrice(double price)
    {
        _price = price;
    }

    //静态成员函数，没有隐含的this指针
    //
    //不能直接访问非静态的数据成员和成员函数
    //只能访问静态数据成员和静态成员函数
    static void printTotalPrice()
    {
        //cout << "brand: " << _brand << endl;//error
        //this->print();//error
        cout << "totalPrice: " << _totalPrice << endl;
    }

private:
    char *_brand;
    double _price;
    static double _totalPrice;//位于全局静态区
    //被类的所有成员共享
};

//静态数据成员的初始化必须要放在类之外进行
double Computer::_totalPrice = 0.0;

void func(const Computer &pc)
{
    pc.print();
}

int test0()
{
    cout << "sizeof(Computer) = " << sizeof(Computer) << endl;
    Computer pc1("ThinkPad",8888);
    cout << "pc1 = ";
    pc1.print();
    //pc1.printTotalPrice();//静态成员函数可以直接用类名调用
    Computer::printTotalPrice();
    cout << endl;

    Computer pc2("Xiaomi",7500);
    cout << "pc2 = ";
    pc2.print();//非const对象可以调用const成员函数
    //pc2.printTotalPrice();
    Computer::printTotalPrice();

    //const对象只能使用const成员函数
    const Computer pc3("Acer",6666);
    pc3.print();

    return 0;
}

int main()
{
    test0();
    return 0;
}

