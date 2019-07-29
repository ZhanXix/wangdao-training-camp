#include <iostream>
#include <limits>
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

    //输出流运算符的要求是：左操作数为流对象，右操作数为输出内容
    //
    //因此输出流运算符不能作为成员函数存在
    //std::ostream & operator<<(std::ostream &os)
    //{}
    //
    friend std::ostream & operator<<(std::ostream &os, const Complex &rhs);
    friend std::istream & operator>>(std::istream &is, Complex &rhs);

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

std::ostream & operator<<(std::ostream &os, const Complex &rhs)
{
    //os << rhs._dreal << " + " << rhs._dimag << "i";
    if(rhs._dimag == 0){
        os << rhs._dreal;
    } else {
        if(rhs._dreal == 0){
            if( rhs._dimag == 1 )
            {
                os << "i";
            } else if( rhs._dimag == -1 ){
                os << "-i";
            } else {
                os << rhs._dimag << "i";
            } 
        } else {
            os << rhs._dreal;
            if( rhs._dimag == 1 ){
                os << " + i";
            } else if( rhs._dimag == -1  ){
                os << " - i";
            } else if(rhs._dimag > 0){
                os << " + " << rhs._dimag << "i";
            } else {
                os << " - " << rhs._dimag * (-1) << "i";
            }
        }
    }

    return os;
}

void readDoubleValue(std::istream &is, double & numble)
{
    cout << "please input a valid double value:" << endl;
    while(is >> numble, !is.eof()){
        if(is.bad()){
            cout << "istream has corrupted" << endl;
            return;
        } else if(is.fail()){
            is.clear();
            is.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            cout << "please input a valid double value:" << endl;
            continue;
        }
        break;
    }
}

//强调：对于输入流要考虑特殊情况
std::istream & operator>>(std::istream &is, Complex &rhs)
{
    //is >> rhs._dreal;
    //is >> rhs._dimag;
    readDoubleValue(is, rhs._dreal);
    readDoubleValue(is, rhs._dimag);

    return is;
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

int test3()
{
    Complex c1(1,2), c2(3,4);

    c1+=c2;
    cout << "执行c1+=c2后" << endl;
    cout << "c1 = " << c1 << endl;
    //输出流运算符的要求是：左操作数为流对象，右操作数为输出内容
    //operator<<( operator<<(cout,"c1 = "), c1);

    Complex c3(0,-1);//  -i
    Complex c4(0,0);//   0
    Complex c5(-1,-2);// -1 - 2i
    Complex c6(-2,0);//  -2
    Complex c7(3,0);//   3
    Complex c8(0,-2);//  -2i

    cout << "c3 = " << c3 << endl;
    cout << "c4 = " << c4 << endl;
    cout << "c5 = " << c5 << endl;
    cout << "c6 = " << c6 << endl;
    cout << "c7 = " << c7 << endl;
    cout << "c8 = " << c8 << endl;

    return 0;
}

void test4()
{
    Complex c1(0,0);
    std::cin >> c1;
    cout << c1 << endl;
}

int main()
{
    //test1();
    //test2();
    //test3();
    test4();
    return 0;
}
