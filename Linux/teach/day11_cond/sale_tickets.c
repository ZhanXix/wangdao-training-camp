#include <func.h>
typedef struct
{
    int tickets;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Data_t,*pData_t;
void cleanup(void *p)
{
    pthread_mutex_t *pmutex=(pthread_mutex_t *)p;
    pthread_mutex_unlock(pmutex);
    printf("unlock sucess\n");
}
void* saleWindows1(void *p)
{
    Data_t *pArg=(Data_t*)p;
    int i=0;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
            printf("I am saleWindows1,start sale,%d\n",pArg->tickets);
            pArg->tickets--;
            i++;
            if(!pArg->tickets)
            {
                pthread_cond_signal(&pArg->cond);
            }
            printf("I am saleWindows1,sale finish,%d\n",pArg->tickets);
            pthread_mutex_unlock(&pArg->mutex);
            sleep(1);
        }else{
            pthread_mutex_unlock(&pArg->mutex);
            printf("I am saleWindows1,%d\n",i);
            break;
        }
    }
    return NULL;
}
void* saleWindows2(void *p)
{
    Data_t *pArg=(Data_t*)p;
    int i=0;
    while(1)
    {
        pthread_mutex_lock(&pArg->mutex);
        if(pArg->tickets>0)
        {
            printf("I am saleWindows2,start sale,%d\n",pArg->tickets);
            pArg->tickets--;
            i++;
            if(!pArg->tickets)
            {
                pthread_cond_signal(&pArg->cond);
            }
            printf("I am saleWindows2,sale finish,%d\n",pArg->tickets);
            pthread_mutex_unlock(&pArg->mutex);
            sleep(1);
        }else{
            pthread_mutex_unlock(&pArg->mutex);
            printf("I am saleWindows2,%d\n",i);
            break;
        }
    }
    return NULL;
}
void* setTickets(void* p)
{
    Data_t* pArg=(pData_t)p;
    pthread_mutex_lock(&pArg->mutex);
    if(pArg->tickets>0)
    {
        pthread_cond_wait(&pArg->cond,&pArg->mutex);
    }
    pArg->tickets=20;
    pthread_mutex_unlock(&pArg->mutex);
}
int main(int argc,char *argv[])
{
    Data_t threadInfo;
    threadInfo.tickets=20;
    pthread_t pthid,pthid1,pthid2;
    pthread_mutex_init(&threadInfo.mutex,NULL);
    pthread_cond_init(&threadInfo.cond,NULL);
    pthread_create(&pthid,NULL,saleWindows1,&threadInfo);
    pthread_create(&pthid1,NULL,saleWindows2,&threadInfo);
    pthread_create(&pthid2,NULL,setTickets,&threadInfo);
    int ret;
    ret=pthread_join(pthid,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(pthid1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    printf("sale over\n");
    return 0;
}

