//7、创建一个子线程，子线程申请内存，通过清理函数进行free，子线程停留在read标准输入，主线程cancel子线程，子线程能够通过清理函数free对应的malloc的内存
#include <func.h>
void clean(void *p)
{
    free(p);
    printf("已清理空间\n");
}
void *pthread_func(void *p)
{
    p=malloc(20);
    pthread_cleanup_push(clean,p);
    sleep(1);
    pthread_cleanup_pop(1);
    read(STDIN_FILENO,p,20);
    pthread_exit((void*)2);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret=pthread_create(&pthid,NULL,pthread_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long getPthReturn;
    ret=pthread_join(pthid,(void**)&getPthReturn);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("主线程已获取子线程退出值：%ld\n",getPthReturn);
    return 0;
}

