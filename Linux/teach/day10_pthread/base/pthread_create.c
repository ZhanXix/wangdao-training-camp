#include <func.h>

void *threadFunc(void *p)
{
    printf("I am child thread\n");
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    usleep(1);
    printf("I am main thread\n");
    return 0;
}

