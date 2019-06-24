#include <func.h>
void print()
{
    printf("I am print");//由于_exit不刷新输出缓冲区，此句不会被打印出来
    _exit(5);

}
int main(int argc,char* argv[])
{
    print();
    printf("after print\n");
    return 0;

}


