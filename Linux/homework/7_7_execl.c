//通过execl拉起来一个add进程，并给其传参3和4，让其求和最终得到7
#include <func.h>

int main(int argc,char *argv[])
{
    execl("add","execl_add","3","4",NULL);    
    return 0;
}

