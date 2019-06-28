//子线程，主线程，同时对一个全局变量加2千万，通过加锁，实现最终效果是4千万
#include <func.h>
typedef struct AddData{
    int val;
    pthread_mutex_t mutex;
}AddData_t,*pAddData_t;
#define N 20000000
void *threadFunc(void *p1)
{
    pAddData_t p=(pAddData_t)p1;
    for(int i=0;i<N;i++)
    {
        pthread_mutex_lock(&p->mutex);
        ++(p->val);
        pthread_mutex_unlock(&p->mutex);
    }
    pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t pth;
    AddData_t data;
    int ret;
    ret=pthread_create(&pth,NULL,threadFunc,&data);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    data.val=0;
    ret=pthread_mutex_init(&data.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    struct timeval begin,end;
    gettimeofday(&begin,NULL);
    for(int i=0;i<N;i++)
    {
        pthread_mutex_lock(&data.mutex);
        ++(data.val);
        pthread_mutex_unlock(&data.mutex);
    }
    ret=pthread_join(pth,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    gettimeofday(&end,NULL);
    printf("最终数值%d,用时%ldus\n",data.val,1000000*(end.tv_sec-begin.tv_sec)+end.tv_usec-begin.tv_usec);
    return 0;
}

