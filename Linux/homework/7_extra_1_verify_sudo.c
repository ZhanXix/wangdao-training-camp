//验证sudo里边是使用了setuid，还是seteuid
#include <func.h>

int main(int argc,char *argv[])
{
    printf("当前真实用户ID为%d，有效用户ID为%d\n",getuid(),geteuid());
    return 0;
}

