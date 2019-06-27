#include <func.h>

void *threadFunc(void *p)//线程函数
{
    printf("I am child thread %s\n",(char*)p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    char *pArg=(char*)malloc(20);
    strcpy(pArg,"hello");
    ret=pthread_create(&pthid,NULL,threadFunc,pArg);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_join(pthid,NULL);//等待子线程
    printf("I am main thread\n");
    return 0;
}

