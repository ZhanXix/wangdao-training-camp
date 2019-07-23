#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

struct Computer
{
    //struct的默认访问权限是public，class的默认访问权限是private
public:
    void setBrand(const char * brand)
    {
        strcpy( _brand, brand );
    }
    
    void setPrice(float price)
    {
        _price = price;
    }

    void print()
    {
        cout << "brand: " << _brand << endl
             << "price: " << _price << endl;
    }

private:
    char _brand[20];//数据成员名字前要加下划线（约定俗成），有时候别人会写 brand_ 或 m_brand
    float _price;
};

int main()
{
    int number=0;
    cout << "number = " << number << endl;

    Computer pc;
    //pc._price = 10000;//error
    pc.setBrand("ThinkPad");
    pc.setPrice(8888);
    pc.print();
    
    return 0;
}

