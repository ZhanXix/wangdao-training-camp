//通过设置线程锁属性，用mutex实现两个进程各加2千万，最终实现4千万
#include <func.h>
typedef struct AddData{
    int val;
    pthread_mutex_t mutex;

}AddData_t,*pAddData_t;
#define N 20000000
int main(int argc,char *argv[])
{
    //设置共享内存中的线程锁
    int shmid=shmget(1000,1<<20,IPC_CREAT|0600);
    ERROR_CHECK(shmid,-1,"shmget");
    pAddData_t pData;
    pData=(pAddData_t)shmat(shmid,NULL,0);
    ERROR_CHECK(pData,(pAddData_t)-1,"shmat");
    pthread_mutexattr_t mutexattr;
    pthread_mutexattr_init(&mutexattr);
    pthread_mutexattr_setpshared(&mutexattr,PTHREAD_PROCESS_SHARED);
    pthread_mutex_init(&pData->mutex,&mutexattr);
    pData->val=0;
    //设置共享内存完毕，开始用两个进程各加N
    struct timeval begin,end;
    gettimeofday(&begin,NULL);
    if(!fork())//子进程
    {
        for(int i=0;i<N;i++)
        {
            pthread_mutex_lock(&pData->mutex);
            ++(pData->val);
            pthread_mutex_unlock(&pData->mutex);

        }
    }else{//父进程
        for(int i=0;i<N;i++)
        {
            pthread_mutex_lock(&pData->mutex);
            ++(pData->val);
            pthread_mutex_unlock(&pData->mutex);

        }
        wait(NULL);
        gettimeofday(&end,NULL);
        printf("最终数值%d,用时%ldus\n",pData->val,1000000*(end.tv_sec-begin.tv_sec)+end.tv_usec-begin.tv_usec);
    }
    return 0;
}

