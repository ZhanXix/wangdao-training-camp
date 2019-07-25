/*实现只能生成栈对象的代码 */
#include <string.h>
#include <iostream>
using std::cout;
using std::endl;

class MyClass
{
public:
    MyClass()
    : _price(0)
    , _name(nullptr){}

    MyClass(int price, const char *name)
    : _price(price)
    , _name(new char[strlen(name)+1]())
    {
        cout << "MyClass(int price, const char *name)" << endl;
        strcpy(_name,name);
    }

    ~MyClass()
    {
        cout << " ~MyClass()" << endl;
        if(_name)
        {
            delete [] _name;
            _name = nullptr;
        }
    }

    void print()
    {
        cout << _name << ": $" << _price << endl;
    }

private:
    void *operator new(size_t size) {}
    void operator delete(void *p){}

    //data
    int _price;
    char *_name;
};

int main()
{
    MyClass apple(10,"apple");
    apple.print();

    return 0;
}
