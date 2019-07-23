#include <iostream>
using std::cout;
using std::endl;

struct X
{
    //X(short & data)
    //: _data(data)
    //{}

    short & _data;
};


int main()
{
    char ch = 'h';
    char & ref = ch;

    short x = 10;
    short & ref1 = x;
    &ref1;

    cout << "sizeof(short &) = " << sizeof(short &) << endl;
    cout << "sizeof(ref) = " << sizeof(ref) << endl;
    cout << "sizeof(ref1) = " << sizeof(ref1) << endl;

    cout << "sizeof(X) = " << sizeof(X) << endl;

    return 0;
}

