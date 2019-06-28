//启动两个线程，处于wait状态，主线程cancel子线程，确保子线程正常被cancel，主线程回收子线程
#include <func.h>
typedef struct lock{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Lock_t,*pLock_t;
void cleanup(void *p)
{
    pthread_mutex_unlock(&((pLock_t)p)->mutex);
    printf("清理成功\n");
}
void* pth_func1(void *p)
{
    pLock_t pMylock=(pLock_t)p;
    pthread_mutex_lock(&pMylock->mutex);
    pthread_cleanup_push(cleanup,p);
    printf("子线程1等待中\n");
    pthread_cond_wait(&pMylock->cond,&pMylock->mutex);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}
void* pth_func2(void *p)
{
    pLock_t pMylock=(pLock_t)p;
    pthread_mutex_lock(&pMylock->mutex); 
    pthread_cleanup_push(cleanup,p);
    printf("子线程2等待中\n");
    pthread_cond_wait(&pMylock->cond,&pMylock->mutex);
    pthread_cleanup_pop(1);
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    int ret;
    Lock_t mylock;
    ret=pthread_mutex_init(&mylock.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_cond_init(&mylock.cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    pthread_t pth1,pth2;
    ret=pthread_create(&pth1,NULL,pth_func1,&mylock);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&pth2,NULL,pth_func2,&mylock);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_cancel(pth1);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_cancel(pth2);
    THREAD_ERROR_CHECK(ret,"pthread_cancel");
    ret=pthread_join(pth1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(pth2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}

