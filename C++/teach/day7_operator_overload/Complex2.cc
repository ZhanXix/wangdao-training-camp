#include <iostream>
using std::cout;
using std::endl;

class Complex
{
public:
    Complex(double dreal, double dimag)
    : _dreal(dreal)
    , _dimag(dimag)
    {
        cout << "Complex(double, double)" << endl;
    }

    void display() const
    {
        cout << _dreal << " + " << _dimag << "i" << endl;
    }

    friend Complex operator+(const Complex &lhs, const Complex &rhs);
    friend  bool operator==(const Complex &lhs, const Complex &rhs);

    //前置形式
    Complex & operator++()
    {
        ++_dreal;
        ++_dimag;
        return *this;
    }

    //后置形式
    Complex operator++(int) //后置形式在其参数中多加一个int，该int不是要传递参数
                            //只是为了与前置形式进行区分
    {
        Complex tmp(*this);
        ++_dreal;
        ++_dimag;
        return tmp;
    }

    //表达式执行结束之后，对象本身发生变化
    //
    //复合赋值运算符都推荐使用成员函数形式进行重载
    Complex &operator+=(const Complex &rhs)
    {
        _dreal += rhs._dreal;
        _dimag += rhs._dimag;
        return (*this);
    }

private:
    double _dreal;
    double _dimag;
};

//不能对内置类型进行重载运算符
//int operator+(int a,int b)
//{
//    return a-b;
//}

//运算符重载之友元函数
Complex operator+(const Complex &lhs, const Complex &rhs)
{
    return Complex(lhs._dreal + rhs._dreal,
                   lhs._dimag + rhs._dimag);
}

bool operator==(const Complex &lhs, const Complex &rhs)
{
    return (lhs._dreal == rhs._dreal) && (lhs._dimag == rhs._dimag);
}

bool operator!=(const Complex &lhs, const Complex &rhs)
{
    return !(lhs == rhs);
}

int test0()
{
    Complex c1(1,2), c2(3,4);
    Complex c3 = c1 + c2;
    cout << "c3 = ";
    c3.display();

    return 0;
}

void test1()
{
    int a=1;
    cout << "(++a) = " << (++a) << endl; //前置++
    cout << a << endl;

    cout << "(a++) = " << (a++) << endl;//后置++
    cout << a << endl;

    Complex c1(1,2), c2(3,4);
    cout << "c1 = ";
    c1.display();

    cout << "(++c1) = ";
    (++c1).display();
    c1.display();

    cout << "(c1++) = ";
    (c1++).display();
    c1.display();
}

int test2()
{
    Complex c1(1,2), c2(3,4);

    c1+=c2;
    cout << "执行c1+=c2后" << endl;
    cout << "c1 = ";
    c1.display();

    return 0;
}
int main()
{
    //test1();
    test2();
    return 0;
}
