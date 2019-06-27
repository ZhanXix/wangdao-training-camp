//创建一个子线程，传入数值1，在子线程中能够获取并打印，子线程退出，返回数值2，主线程通过pthread_join获取等待子线程结束并获取子线程的退出值并打印
#include <func.h>

void *pthread_func(void *p)
{
    printf("子线程已获取传入数值：%d\n",*(int*)p);
    pthread_exit((void*)2);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int val=1;
    int ret=pthread_create(&pthid,NULL,pthread_func,&val);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    long getPthReturn;
    ret=pthread_join(pthid,(void**)&getPthReturn);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("主线程已获取子线程退出值：%ld\n",getPthReturn);
    return 0;
}

