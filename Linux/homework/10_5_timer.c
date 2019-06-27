//使用真实计时器，实用计时器，虚拟计时器，统计程序执行时间，在实用计时器及虚拟计时器设定计时后，先睡眠，再让程序处于while（1）
#include <func.h>
int time_real=0,time_virtual=0,time_prof=0;
void sigFunc(int signum)
{
    if(SIGALRM==signum)
    {
        time_real++;
    }else if(SIGVTALRM==signum){
        time_virtual++;
    }else{
        time_prof++;
    }
    printf("当前程序运行时间：真实计时器%ds，虚拟计时器%ds，实用计时器%ds\n",time_real,time_virtual,time_prof);
}
int main(int argc,char *argv[])
{
    signal(SIGALRM,sigFunc);
    signal(SIGVTALRM,sigFunc);
    signal(SIGPROF,sigFunc);
    struct itimerval timer_real,timer_virtual,timer_prof;
    bzero(&timer_real,sizeof(timer_real));
    timer_real.it_interval.tv_sec=1;
    timer_real.it_value.tv_sec=1;
    bzero(&timer_virtual,sizeof(timer_virtual));
    timer_virtual.it_interval.tv_sec=1;
    timer_virtual.it_value.tv_sec=1;
    bzero(&timer_prof,sizeof(timer_prof));
    timer_prof.it_interval.tv_sec=1;
    timer_prof.it_value.tv_sec=1;
    int ret;
    ret=setitimer(ITIMER_REAL,&timer_real,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    ret=setitimer(ITIMER_VIRTUAL,&timer_virtual,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    ret=setitimer(ITIMER_PROF,&timer_prof,NULL);
    ERROR_CHECK(ret,-1,"setitimer");
    sleep(5);
    while(1);
    return 0;
}

