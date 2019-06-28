//编写代码，通过ctime感受线程安全
#include <func.h>
void *pth_func(void *p)
{
    time_t now;
    time(&now);
    char safeTime_buf[512]={0};
    char *safeTime=ctime_r(&now,safeTime_buf);
    char *unsafeTime=ctime(&now);
    printf("子线程安全时间%s不安全时间%s\n",safeTime,unsafeTime);
    sleep(3);
    printf("子线程安全时间%s不安全时间%s\n",safeTime,unsafeTime);
}
int main(int argc,char *argv[])
{
    pthread_t pth;
    int ret=pthread_create(&pth,NULL,pth_func,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    time_t now;
    sleep(2);
    time(&now);
    char safeTime_buf[512]={0};
    char *safeTime=ctime_r(&now,safeTime_buf);
    char *unsafeTime=ctime(&now);
    printf("主线程安全时间%s不安全时间%s\n",safeTime,unsafeTime);
    ret=pthread_join(pth,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}

