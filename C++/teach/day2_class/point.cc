#include <iostream>
using std::cout;
using std::endl;

class Point
{
public:
    //构造函数的作用：创建对象，初始化数据成员
    //
    //当没有定义任何构造函数时，系统会自动提供一个默认构造函数；
    //一旦显示提供了一个构造函数时，默认构造函数就不会再自动提供
    //

    //Point() = default;//简单写法，形成一个默认构造函数（需要先直接在定义里赋值，如：private:int _ix=0;）

    //构造函数可以进行重载
    //
    Point()
    : _ix(0)
    , _iy(0)    //初始化表达式（初始化列表），一般一行写一个，便于添加、删除、检查
    {
        //_ix=0;//赋值语句，并非真正的初始化
        //_iy=0;
        cout << "point()" << endl;
    }
    Point(int ix,int iy)
    : _ix(ix)
    , _iy(iy)
    {
        //_ix = ix;
        //_iy = iy;
        cout << "Point(int,int)" << endl;
    }

    void print()
    {
        cout << "(" << _ix
             << "," << _iy
             << ")" << endl;
    }

    //析构函数
    //
    //默认情况下，系统也会自动提供一个析构函数
#if 1
    ~Point()//不能传参，所以析构函数只有一个
    {
        cout << "~Point()" << endl;
    }
#endif

private:
    int _ix;
    int _iy;
};


int main()
{
    int number=10;

    Point pt0;//调用默认构造函数；如果已经显式提供了一个有参构造函数，就必须再显式提供一个无参构造函数
    cout << "pt0=";
    pt0.print();

    Point pt(1,2);//有参构造函数
    cout << "pt=";
    pt.print();

    Point * p1 = new Point(3,4);
    p1->print();
    delete p1;
    
    return 0;
}

