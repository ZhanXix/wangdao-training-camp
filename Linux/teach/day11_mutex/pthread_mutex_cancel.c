#include <func.h>
typedef struct
{
    pthread_mutex_t mutex;
}Data_t;
void cleanup(void *p)
{
    pthread_mutex_t *pmutex=(pthread_mutex_t *)p;
    pthread_mutex_unlock(pmutex);
    printf("unlock sucess\n");
}
void* threadFunc(void *p)
{
    Data_t *pArg=(Data_t*)p;
    pthread_mutex_lock(&pArg->mutex);//不是cancel点
    pthread_cleanup_push(cleanup,&pArg->mutex);
    printf("child lock success\n");//cancel点
    sleep(2);//cancel点
    pthread_cleanup_pop(1);
    printf("you can not see me\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    Data_t threadInfo;
    pthread_t pthid,pthid1;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    pthread_create(&pthid1,NULL,threadFunc,&threadInfo);
    int ret;
    sleep(1);
    ret=pthread_cancel(pthid);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_cancel(pthid1);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    long threadRet;
    ret=pthread_join(pthid,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("pthid ret=%ld\n",threadRet);
    ret=pthread_join(pthid1,(void**)&threadRet);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("pthid1 ret=%ld\n",threadRet); 
    return 0;
}

