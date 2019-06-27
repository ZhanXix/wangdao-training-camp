#include <func.h>

void *threadFunc(void *p)
{
    printf("I am child thread\n");
    pthread_exit((void*)10);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    long threadRet;//不能够用int，要用long，否则访问越界
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,%ld\n",threadRet);
    return 0;
}

