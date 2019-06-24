#include <func.h>

int main(int argc,char *argv[])
{
    printf("当前进程pid为%d，父进程pid为%d，真实用户ID为%d，真实组ID为%d，有效用户ID为%d，有效组ID为%d\n",getpid(),getppid(),getuid(),getgid(),geteuid(),getegid());    
    return 0;
}

