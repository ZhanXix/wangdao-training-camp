#include <iostream>

int add(int x=0,int y=0)  //设置默认值
{
    return x+y;
}
//一旦将某一个参数设置默认值之后，其后的所有参数都需要设置默认值
//
//默认值的设置是按照从右到左的顺序进行


int main()
{
    int a=3, b=4;
    std::cout << add(a) << std::endl
              << add() << std::endl
              << add(a,4) << std::endl;
    return 0;
}

