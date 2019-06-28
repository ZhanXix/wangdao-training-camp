#include <func.h>
typedef struct
{
    pthread_mutex_t mutex;
}Data_t;
void* threadFunc(void *p)
{
    Data_t *pArg=(Data_t*)p;
    int ret=pthread_mutex_unlock(&pArg->mutex);
    pthread_mutex_lock(&pArg->mutex);
    printf("child lock success\n");
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    Data_t threadInfo;
    pthread_t pthid;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    pthread_mutex_lock(&threadInfo.mutex);
    printf("man thread lock success\n");
    int ret=pthread_join(pthid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}

