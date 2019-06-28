#include <func.h>
#define N 20000000
typedef struct{
    int val;
    pthread_mutex_t mutex;
}Data_t;
void *threadFunc(void *p)//线程函数
{
    int i;
    Data_t *pVal=(Data_t*)p;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&pVal->mutex);
        pVal->val+=1;
        pthread_mutex_unlock(&pVal->mutex);
    }
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    Data_t threadInfo;
    threadInfo.val=0;
    ret=pthread_mutex_init(&threadInfo.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval start,end;
    gettimeofday(&start,NULL);
    ret=pthread_create(&pthid,NULL,threadFunc,&threadInfo);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    int i;
    for(i=0;i<N;i++)
    {
        pthread_mutex_lock(&threadInfo.mutex);
        threadInfo.val+=1;
        pthread_mutex_unlock(&threadInfo.mutex);
    }
    pthread_join(pthid,NULL);//等待子线程
    gettimeofday(&end,NULL);
    printf("I am main thread,val=%d,use time=%ld\n",threadInfo.val,(end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec);
    return 0;
}

