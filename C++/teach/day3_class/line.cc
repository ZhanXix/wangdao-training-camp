#include <iostream>
using std::cout;
using std::endl;

//对于拷贝构造函数、赋值运算符函数、析构函数，
//这三者之中只要有一个要显式提供
//其他两个也必须要提供

class Point
{
public:
    //explicit //必须要显式调用构造函数，禁止隐式转换
    Point(int ix=0, int iy=0)
    : _ix(ix)   
    , _iy(iy)
    {
        cout << "Point(int ix, int iy)" << endl;
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
    int _ix;
    int _iy;
};

class Line
{
public:
    //类的对象成员也必须要放在初始化表达式中进行初始化
    Line(int x1,int x2,int y1,int y2)
    : _pt1(x1,y1)
    , _pt2(x2,y2)
    {
        cout << "Line(int x1,int x2,int y1,int y2)" << endl;
    }
    void printLine()
    {
        _pt1.print();
        cout << " ---> " << endl;
        _pt2.print();
    }
private:
    Point _pt1;
    Point _pt2;
};


int main()
{
    Point pt0;

    Point pt();//声明了一个函数
    //pt.print();//error
    
    Point();//构造了一个临时对象，只存在于这一行中
    Point().print();
    Point(1,2).print();

    Line l1(1,2,3,4);
    l1.printLine();

    return 0;
}

