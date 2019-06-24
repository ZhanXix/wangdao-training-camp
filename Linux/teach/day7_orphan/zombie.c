#include <func.h>

int main(int argc,char *argv[])
{
    if(!fork())
    {
        printf("I am child,pid=%d\n",getpid());
    }else{
        while(1);
        return 0;
    }
}

