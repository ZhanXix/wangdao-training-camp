#include <func.h>
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;
void *threadFunc(void *p)
{
    pData_t pArg=(pData_t)p;
    struct timespec t;
    t.tv_sec=time(NULL)+3;
    t.tv_nsec=0;
    int ret;
    pthread_mutex_lock(&pArg->mutex);
    ret=pthread_cond_timedwait(&pArg->cond,&pArg->mutex,&t);
    pthread_mutex_unlock(&pArg->mutex);
    printf("I am child thread wake up,ret=%d\n",ret);
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    Data_t threadInfo;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    sleep(1);
    pthread_cond_signal(&threadInfo.cond);//让条件变量成立：一瞬间成立
    pthread_join(pthid,NULL);
    printf("I am man thread\n");
    return 0;
}

