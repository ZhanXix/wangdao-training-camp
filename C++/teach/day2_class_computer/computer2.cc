#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class Computer
{
public:
    //防止public区域的称为类对外的接口、功能、服务
    void setBrand(const char * brand);
    void setPrice(float price);
    void print();

private://封装的效果
    //私有的成员不能在类之外直接访问
    char _brand[20];//数据成员名字前要加下划线（约定俗成），有时候别人会写 brand_ 或 m_brand
    float _price;
};

//在类之外实现成员函数(如果不加inline关键字就不是inline函数了)
inline void Computer::setBrand(const char * brand)
{
    strcpy( _brand, brand );
}

inline void Computer::setPrice(float price)
{
    _price = price;
}

inline void Computer::print()
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

