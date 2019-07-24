#include <iostream>
using std::cout;
using std::endl;

//对于拷贝构造函数、赋值运算符函数、析构函数，
//这三者之中只要有一个要显式提供
//其他两个也必须要提供

class Point
{
public:
    //explicit //必须要显示调用构造函数，禁止隐式转换
    Point(int ix = 0, int iy = 0)
    : _ix(ix)   //对于const数据成员，只能放在初始化表达式中进行初始化
    , _iy(iy)
    {
        cout << "Point(int ix, int iy)" << endl;
        //_ix = ix;
        //_iy = iy;
    }

    ~Point()
    {
        cout << "~Point()" << endl;
    }

    void print()
    {
        cout << "(" << _ix
             << "," << _iy
             << ")" << endl;
    }


private:
    const int _ix;
    const int _iy;

};

int main()
{
    Point pt1(3,4);
    //pt1._ix=10; //error:'_ix' is protected within this context

    pt1.~Point(); //析构函数可以显式调用，但一般不这样做，因为函数退出时还是会自动调用析构函数

    Point pt2 = 10;//存在隐式转换，通过构造函数进行（需要构造函数存在默认值，且没有explicit关键字）
    cout << "pt2 = ";
    pt2.print();

    return 0;
}

