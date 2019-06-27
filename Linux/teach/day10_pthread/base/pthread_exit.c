#include <func.h>
void print()
{
    printf("I am print\n");
    pthread_exit(NULL);
}
void *threadFunc(void *p)
{
    printf("I am child thread\n");
    print();
    printf("I am child,after print\n");
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    int ret;
    ret=pthread_create(&pthid,NULL,threadFunc,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    pthread_join(pthid,NULL);
    printf("I am main thread\n");
    return 0;
}

