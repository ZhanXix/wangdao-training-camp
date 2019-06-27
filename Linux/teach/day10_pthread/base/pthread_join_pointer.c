#include <func.h>

void *threadFunc(void *p)
{
    p=malloc(20);
    strcpy((char*)p,"hello world");
    printf("I am child thread,%s\n",(char*)p);
    pthread_exit(p);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    char *pRet;
    ret=pthread_join(pthid,(void**)&pRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("I am main thread,%s\n",pRet);
    return 0;
}

