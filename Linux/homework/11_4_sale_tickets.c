//编写火车站买票，两个子线程卖票，一个子线程放票
#include <func.h>
#define N 15
typedef struct tickets{
    int num;
    pthread_mutex_t mutex;
    pthread_cond_t cond;
}Tickets_t,*pTickets_t;
void* sale1_func(void *p1)
{
    pTickets_t p=(pTickets_t)p1;
    int sale=0;
    while(1)
    {
        usleep(500);
        pthread_mutex_lock(&p->mutex);
        if(p->num)
        {
            --(p->num);
            ++sale;
            printf("售票窗口1卖出一张票，余票%d\n",p->num);
            if(0==p->num)
            {
                pthread_cond_signal(&p->cond);
            }
            pthread_mutex_unlock(&p->mutex);
        }else{
            pthread_mutex_unlock(&p->mutex);
            printf("售票窗口1共卖出%d张票\n",sale);
            pthread_exit(NULL);
        }
    }
}
void* sale2_func(void *p1)
{
    pTickets_t p=(pTickets_t)p1;
    int sale=0;
    while(1)
    {
        usleep(500);
        pthread_mutex_lock(&p->mutex);
        if(p->num)
        {
            --(p->num);
            ++sale;
            printf("售票窗口2卖出一张票，余票%d\n",p->num);
            if(0==p->num)
            {
                pthread_cond_signal(&p->cond);
            }
            pthread_mutex_unlock(&p->mutex);
        }else{
            pthread_mutex_unlock(&p->mutex);
            printf("售票窗口2共卖出%d张票\n",sale);
            pthread_exit(NULL);
        }
    }
}
void* add_func(void *p1)
{
    pTickets_t p=(pTickets_t)p1;
    //如果要实现无限补票，这里要写成循环
    pthread_mutex_lock(&p->mutex);
    if(p->num>0)
    {
        pthread_cond_wait(&p->cond,&p->mutex);
    }
    p->num+=N;
    printf("补票完毕！\n");
    pthread_mutex_unlock(&p->mutex);
}
int main(int argc,char *argv[])
{
    int ret;
    Tickets_t tic;
    tic.num=N;
    ret=pthread_mutex_init(&tic.mutex,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_mutex_init");
    ret=pthread_cond_init(&tic.cond,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_cond_init");
    pthread_t sale1,sale2,add;//两个子线程卖票，一个子线程放票
    ret=pthread_create(&sale1,NULL,sale1_func,&tic);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&sale2,NULL,sale2_func,&tic);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_create(&add,NULL,add_func,&tic);
    THREAD_ERROR_CHECK(ret,"pthread_create");
    ret=pthread_join(sale1,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(sale2,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    ret=pthread_join(add,NULL);
    THREAD_ERROR_CHECK(ret,"pthread_join");
    return 0;
}

