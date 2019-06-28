#include <func.h>
typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;
void *threadFunc(void *p)
{
    pData_t pArg=(pData_t)p;
    pthread_mutex_lock(&pArg->mutex);
    pthread_cond_wait(&pArg->cond,&pArg->mutex);
    pthread_mutex_unlock(&pArg->mutex);
    printf("I am child thread wake up\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    Data_t threadInfo;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    pthread_t pthid;
    pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    usleep(5000);
    pthread_cond_signal(&threadInfo.cond);//让条件变量成立：一瞬间成立
    pthread_join(pthid,NULL);
    printf("I am man thread\n");
    return 0;
}

