#include <func.h>
//查看清理函数的执行顺序
void cleanup(void *p)
{
    free(p);//在清理函数中，就不会在正常的执行流程中
    printf("I am cleanup\n");
}
void* threadFunc(void *p)
{
    p=malloc(20);
    pthread_cleanup_push(cleanup,p);
    sleep(3);//代码执行
    pthread_cleanup_pop(1);//你要提前free的时候用的是pop
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,NULL);
    long threadRet;
    int ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("threadRet=%ld\n",threadRet);
    return 0;
}

