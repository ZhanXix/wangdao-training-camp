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

    //get函数
    double getReal () const { return _dreal; }
    double getImag () const { return _dimag; }

    //set函数
    void setReal(double real) { _dreal = real; }
    void setImag(double imag) { _dimag = imag; }

    friend Complex operator+(const Complex &lhs, const Complex &rhs);

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

int main()
{
    Complex c1(1,2), c2(3,4);
    Complex c3 = c1 + c2;
    cout << "c3 = ";
    c3.display();

    return 0;
}

