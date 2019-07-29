#include <math.h>
#include <iostream>
using std::cout;
using std::endl;

class Point;//类的前向声明 ===> 不知道类的成员有哪些，无法确定类的大小

class Line
{
public:
    float distance(const Point &lhs, const Point &rhs);
    void setPoint(Point &pt, int ix, int iy);

private:
    int _data;
};

class Point
{
public:
    Point(int ix=0, int iy=0)
    : _ix(ix)
    , _iy(iy)
    {
        cout << "Point(int,int)" << endl;
    }

    void print() const
    {
        cout << "(" << _ix
             << "," << _iy
             << ")";
    }

    //友元关系是单向的
    //不具备传递性，不能继承
    //void setLine(Line &line, int data)
    //{
    //    line._data = data;
    //}

    //友元类
    friend Line;

private:
    int _ix;
    int _iy;
};


float Line::distance(const Point &lhs, const Point &rhs)
{
    return sqrt((lhs._ix - rhs._ix) * (lhs._ix - rhs._ix) +
                 (lhs._iy - rhs._iy) * (lhs._iy - rhs._iy));
}

void Line::setPoint(Point &pt, int ix, int iy)
{
    pt._ix = ix;
    pt._iy = iy;
}

int main()
{
    Point pt1(10,11);
    Point pt2(21,22);
    Line().setPoint(pt2,31,32);
    pt1.print();
    cout << " ---> ";
    pt2.print();
    cout << "的距离" << Line().distance(pt1,pt2) << endl;
    return 0;
}

