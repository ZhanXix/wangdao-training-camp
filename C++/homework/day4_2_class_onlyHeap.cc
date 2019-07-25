/*实现只能生成堆对象的代码 */
#include <string.h>
#include <stdlib.h>
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

    void destroy()
    {
        cout << "void destroy()" << endl;
        if(this)
        {
            delete this;
        }
    }

    void print()
    {
        cout << _name << ": $" << _price << endl;
    }

    void *operator new(size_t size)
    {
        cout << "void *operator new(size_t size)" << endl;
        void *p = malloc(size);
        return p;
    }

    void operator delete(void *p)
    {
        cout << "void operator delete(void *p)" << endl;
        free(p);
    }

private:
    ~MyClass()
    {
        cout << " ~MyClass()" << endl;
        if(_name)
        {
            delete [] _name;
            _name = nullptr;
        }
    }

    //data
    int _price;
    char *_name;
};

int main()
{
    MyClass *pApple = new MyClass(10,"apple");
    pApple->print();
    pApple->destroy();

    return 0;
}
