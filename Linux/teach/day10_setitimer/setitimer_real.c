#include <func.h>
long times=0;
void sigFunc(int signum)
{
    time_t now;
    time(&now);//获取当前距离1970年1月1日的秒数
    printf("%s %ld\n",ctime(&now),times);
    times=0;
}
int main(int argc,char *argv[])
{
    signal(SIGALRM,sigFunc);
    struct itimerval t;
    bzero(&t,sizeof(t));
    t.it_value.tv_sec=1;
    t.it_interval.tv_sec=1;
    sigFunc(0);
    int ret;
    ret =setitimer(ITIMER_REAL,&t,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    //char buf[128]={0};
    //read(STDIN_FILENO,buf,sizeof(buf));
    //printf("buf=%s\n",buf);
    double d,f;
    while(1)
    {
        f=1234568.26;
        d=892.126*f;
        times++;
    }
    return 0;
}

