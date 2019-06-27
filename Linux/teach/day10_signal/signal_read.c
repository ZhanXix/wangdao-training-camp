#include <func.h>
void sigFunc(int signum)
{
    printf("%d is coming\n",signum);
}
int main(int argc,char *argv[])
{
    signal(SIGINT,sigFunc);
    char buf[128]={0};
    int ret=read(STDIN_FILENO,buf,sizeof(buf));
    printf("ret=%d,buf=%s\n",ret,buf);
    return 0;
}

