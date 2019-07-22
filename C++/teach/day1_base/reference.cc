#include <iostream>
using std::cout;
using std::endl;

void test0()
{
    int number = 10;
    int &ref = number; //引用的定义
    //引用是一个变量的别名，可以看作一个受限制的指针
    //引用一经初始化，不会再改变指向

    //int &ref2;//error:引用必须要初始化
                //引用不能单独存在
    int *p; //指针可以单独存在
    
    cout << "&number = " << &number << endl;
    cout << "&ref = " << &ref << endl;
    cout << "number = " << number << endl;
    cout << "ref = " << ref << endl;

    ref = 20;

    cout << "number = " << number << endl;
    cout << "ref = " << ref << endl;

}

//值传递 ==> 复制(副本)
#if 0
void swap(int x,int y)
{
    int temp = x;
    x = y;
    y = temp;
}
#endif

#if 0
//地址传递 ==> 值传递
void swap(int *px,int *py)
{
    int temp = *px;
    *px = *py;
    *py = temp;
}
#endif

//1.引用作为函数形参，传递实参

//引用传递 ==> 直接操作实参，减少复制的开销
//能够提高程序的效率
//
//使用起来比指针更直观、更自然
//
void swap(int &x,int &y)
{
    int temp = x;
    x = y;
    y = temp;
}


int test1()
{
    //test0();
    int a=3,b=4;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    swap(a,b);
    //swap(&a,&b);
    cout << "执行交换之后：" << endl;
    cout << "a = " << a << endl;
    cout << "b = " << b << endl;
    return 0;
}

//2.引用作为函数的返回值
//要求：返回的变量其生命周期一定要大于函数的

int arr[5]={1,2,3,4,5};

int getNumber(int idx)
{
    return arr[idx];//如果返回值是int型，return时会进行复制
}

int & getNumber2(int idx)
{
    return arr[idx];//如果返回值是int型，return时不会进行复制
}

//不能返回一个局部变量的引用
int & getNumber3()
{
    int number=10;//局部变量
    return number;
}

//不要轻易返回堆空间变量的引用
//除非已经有了内存回收的策略
int & getNumber4()
{
    int *pint = new int(1); 
    cout << "pint = " << pint << endl;
    return *pint;
}

int test3()
{
    int x = getNumber(1);
    cout << "x = " << x << endl;

    //&getNumber(1); //error:getNumber返回的是一个临时变量，临时变量不能取地址
    //getNumber(1) = 11;
    
    getNumber2(1)=11;
    cout << "arr[1] = " << arr[1] << endl;

    //cout << "getNumber3() = " << getNumber3() << endl;//段错误

    int &y = getNumber4();
    cout << "y = " << y << endl;
    cout << "&y = " << &y << endl;
    delete &y;

    int a=1, b=2, c=3;
    //在表达式中调用一次getNumber4,就会产生一次内存泄漏
    cout << "c=" << a + b + getNumber4() + c << endl;

    return 0;
}

int main()
{
    test3();
    return 0;
}
