#include <func.h>
//查看清理函数的执行顺序
void cleanup1(void *p)
{
    printf("I am cleanup%ld\n",(long)p);
}
void* threadFunc(void *p)
{
    pthread_cleanup_push(cleanup1,(void*)1);
    pthread_cleanup_push(cleanup1,(void*)2);
    pthread_cleanup_pop(1);//pop弹出一个清理函数，1执行，0不执行
    pthread_cleanup_pop(1);
    return NULL;//return情况下不会执行清理函数
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

