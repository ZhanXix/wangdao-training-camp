#include <iostream>
using std::cout;
using std::endl;

class Example
{
public:
    Example(int data)
        //数据成员初始化的顺序只与其声明时的顺序有关，
        //而与其在初始化表达式中的顺序无关
    : _iy(data)
    , _ix(_iy) //有问题，_ix会初始化为不确定值
    {
        cout << "Example(int)" << endl;
    }
    void print()
    {
        cout << _ix << "," << _iy << endl;
    }

private:
    int _ix;
    int _iy;
};

int main()
{
    Example ex(10);
    ex.print();
    return 0;
}

