#include <iostream>
using std::cout;
using std::endl;

class String
{
public:
    String()
    : _pstr(nullptr)
    {
        cout << "String()" << endl;
    }

    void print()
    {
        printf("_pstr = %p\n",_pstr);
        cout << _pstr << endl;//cout输出char* 的空指针，会导致程序直接崩溃
    }

private:
    char *_pstr;
};

int main()
{
    String s;
    s.print();

    cout << "---" << endl;

    return 0;
}

