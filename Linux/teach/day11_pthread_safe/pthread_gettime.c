#include <func.h>

void *threadFunc(void *p)
{
    time_t now;
    time(&now);
    //不安全！！！
    char *pnow=ctime(&now);//ctime里用的是静态局部变量，不是线程安全函数
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
    char *pnow=ctime(&now);
    printf("I am main thread p=%s\n",pnow);
    pthread_join(pthid,NULL);
    return 0;
}

