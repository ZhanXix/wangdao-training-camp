#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork())
    {
        printf("I am child,pid=%d\n",getpid());
        while(1);
    }else{
        return 0;
    }
}

