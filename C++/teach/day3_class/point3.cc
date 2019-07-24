#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
    //对于引用数据成员，只能放在初始化表达式中进行初始化
    explicit
    Point(int ix = 0, int iy = 0)
    : _ix(ix)
    , _iy(iy)
    , _ref(ix)
    {
        cout << "Point(int ix, int iy)" << endl;
        //_ix = ix;//error
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
             << "," << _ref
             << ")" << endl;
    }


private:
    int _ix;
    int _iy;
    int &_ref;
};

int main()
{
    Point pt(3,4);
    //pt._ix=10; //error:'_ix' is protected within this context

    pt.~Point(); //析构函数可以显式调用，但一般不这样做，因为函数退出时还是会自动调用析构函数

    //Point pt2 = 10;//存在隐式转换，通过构造函数进行（需要构造函数存在默认值，且没有explicit关键字）
    cout << "pt = ";
    pt.print();

    return 0;
}

