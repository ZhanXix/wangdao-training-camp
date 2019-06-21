#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdw=open(argv[1],O_WRONLY);
    printf("I am writer fdw=%d\n",fdw);
    int count=0,ret;
    while(1)//写管道有上限
    {
        ret=write(fdw,"helloworld",10);
        count+=ret;
        printf("count=%d\n",count);
        usleep(100000);
    }
    return 0;
}

