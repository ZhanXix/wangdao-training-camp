//创建一个子线程，cancel子线程，在子线程中push两个清理函数，感受清理函数的执行顺序
#include <func.h>
void cleanup1(void *p)
{
    printf("清理函数1已执行\n");
}
void cleanup2(void *p)
{
    printf("清理函数2已执行\n");
}
void *pthFunc(void *p)
{
    pthread_cleanup_push(cleanup1,NULL);
    pthread_cleanup_push(cleanup2,NULL);
    printf("子进程执行中...\n");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(1);
}
int main(int argc,char *argv[])
{
    pthread_t pth;
    int ret;
    ret=pthread_create(&pth,NULL,pthFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pth);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pth,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}

