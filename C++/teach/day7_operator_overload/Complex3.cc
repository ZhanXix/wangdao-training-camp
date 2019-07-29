#include <iostream>
using std::cout;
using std::endl;

class Complex
{
public:
    Complex(double dreal=0, double dimag=0)
        : _dreal(dreal)
          , _dimag(dimag)
    {
        cout << "Complex(double, double)" << endl;
    }

    void display() const
    {
        cout << _dreal << " + " << _dimag << "i" << endl;
    }

    //get函数
    double getReal () const { return _dreal; }
    double getImag () const { return _dimag; }

    //set函数
    void setReal(double real) { _dreal = real; }
    void setImag(double imag) { _dimag = imag; }

    //运算符重载之成员函数
    //(不推荐使用)
    Complex operator+(const Complex &rhs)
    {
        return Complex(_dreal + rhs._dreal,
                       _dimag + rhs._dimag);
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
    Complex c1(1,2);
    cout << "c1 = ";
    c1.display();
    Complex c2 = c1 + 5;//隐式转换
        //c1.operator+(5)
    cout << "c2 = ";
    c2.display();
    //c2 = 5 + c1;
        //5.operator+(c1) //error
    //cout << "c2 = ";
    //c2.display();
}


int main()
{
    test1();
    return 0;
}

