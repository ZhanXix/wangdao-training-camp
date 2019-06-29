#include <func.h>
void* threadFunc(void *p)
{
   printf("I am child thread\n");
   pthread_exit(NULL);
}
int main(int argc,char *argv[])
{
    pthread_t pthid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr,PTHREAD_CREATE_DETACHED);
    pthread_create(&pthid,&attr,threadFunc,NULL);
    int ret=pthread_join(pthid,NULL);
    printf("I am main thread ret=%d\n",ret);
    return 0;
}

