#include <func.h>

int main(int argc,char *argv[])
{
    pthread_mutex_t mutex;
    pthread_mutexattr_t mattr;
    int ret;
    ret=pthread_mutexattr_init(&mattr);
    THREAD_ERROR_CHECK(ret,"pthread_mutexattr_init");
    pthread_mutexattr_settype(&mattr,PTHREAD_MUTEX_ERRORCHECK);//允许同一个线程对同一把锁加锁多次
    pthread_mutex_init(&mutex,&mattr);
    pthread_mutex_lock(&mutex);
    ret=pthread_mutex_lock(&mutex);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_lock");
    printf("you can see me\n");
    return 0;
}

