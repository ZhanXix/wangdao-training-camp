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

    //系统提供的拷贝函数不再满足需求
    //Computer(const Computer &rhs)
    //: _brand(rhs._brand)//浅拷贝
    //, _price(rhs._price)
    //{
    //    cout << "Computer(const Computer &rhs)" << endl;
    //}
    
    //1.拷贝构造函数的引用符号不可以删除，
    //  如果删除，会导致拷贝函数的无穷递归调用，直到栈溢出
    //  （用形参，就又会触发拷贝函数，疯狂自己调用自己，直至栈满程序崩溃)
    //2.拷贝构造函数的const关键字不可以删除，
    //  如果删除，当传递过来的是一个右值时，就无法编译通过

    Computer(const Computer &rhs)
    : _brand(new char[strlen(rhs._brand+1)]()) //深拷贝
    , _price(rhs._price)
    {
        cout << "Computer(const Computer &)" << endl;
        strcpy(_brand,rhs._brand);
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

int main()
{
    //test1();
    test2();
    return 0;
}

