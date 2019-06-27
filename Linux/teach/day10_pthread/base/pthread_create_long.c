#include <func.h>

void *threadFunc(void *p)//线程函数
{
    printf("I am child thread %ld\n",(long)p);//指针在64位下占8字节，刚好与long对应
}
int main(int argc,char *argv[])
{
    pthread_t pthid,pthid1;
    int ret;
    long val=1;
    ret=pthread_create(&pthid,NULL,threadFunc,(void*)val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    val=2;
    ret=pthread_create(&pthid1,NULL,threadFunc,(void*)val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_join(pthid,NULL);//等待子线程
    pthread_join(pthid1,NULL);//等待子线程
    printf("I am main thread\n");
    return 0;
}

