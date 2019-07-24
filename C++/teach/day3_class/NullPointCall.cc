#include <iostream>
using std::cout;
using std::endl;

class NullPointCall
{
public:
    void test1()
    {
        cout << "test1()" << endl;
    }
    void test2(int data)
    {
        cout << "test2() data =" << data << endl;
    }
    static void test3()
    {
        cout << "test3() _data2 = " << _data2 << endl;
    }
    void test4()
    {
        cout << "test4() _data = " << _data << endl;
    }
private:
    int _data;
    static int _data2;
};

int NullPointCall::_data2 = 0;

int main()
{
    NullPointCall *p = nullptr;//空指针
    p->test1();
    p->test2(10);
    p->test3();
    //p->test4();//error：段错误 (核心已转储)
    return 0;
}

