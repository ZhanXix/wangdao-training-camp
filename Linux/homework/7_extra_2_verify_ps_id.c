#include <func.h>

int main(int argc,char *argv[])
{
    printf("当前真实用户ID为%d，有效用户ID为%d\n",getuid(),geteuid());
    while(1);
    return 0;
}

