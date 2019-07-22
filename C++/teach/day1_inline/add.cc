#include "add.h"

inline
int add(int x,int y)
{
    return x+y;
}

//不可以这样写，inline函数必须在头文件里面实现，否则会报错:
//inline function 'int add(int, int)' used but never defined
