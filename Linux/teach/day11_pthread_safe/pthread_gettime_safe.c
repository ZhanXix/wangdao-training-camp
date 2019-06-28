#include <func.h>

void *threadFunc(void *p)
{
    time_t now;
    time(&now);
    char buf[1000]={0};
    char *pnow=ctime_r(&now,buf);
    printf("I am child thread p=%s\n",pnow);
    sleep(3);
    printf("I am child thread p=%s\n",pnow);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,NULL);
    sleep(1);
    time_t now;
    time(&now);
    char buf[1000]={0};
    char *pnow=ctime_r(&now,buf);
    printf("I am main thread p=%s\n",pnow);
    pthread_join(pthid,NULL);
    return 0;
}

