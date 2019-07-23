#include "computer.h"
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

//在类之外实现成员函数(如果不加inline关键字就不是inline函数了)
void Computer::setBrand(const char * brand)
{
    strcpy( _brand, brand );
}

void Computer::setPrice(float price)
{
    _price = price;
}

void Computer::print()
{
    cout << "brand: " << _brand << endl
        << "price: " << _price << endl;
}

int main()
{
    int number=0;
    cout << "number = " << number << endl;

    //自定义类类型
    Computer pc;//创建类对象的过程称为类的实例化
    //pc._price = 10000;//error
    pc.setBrand("ThinkPad");
    pc.setPrice(8888);
    pc.print();

    Computer pc2;
    pc2.setBrand("ACER");
    pc2.setPrice(6666);
    pc2.print();

    return 0;
}

