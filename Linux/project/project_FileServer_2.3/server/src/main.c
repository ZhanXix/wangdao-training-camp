#include "../include/file_server.h"

int fds_exit[2];
void SigFunc_Exit(int sigNum)
{
    write(fds_exit[1],"1",1);
    printf("已捕捉到退出信号%d\n",sigNum);
}

int main()
{
    while(1)//防止进程意外退出
    {
        if(fork())
        {
            int status;
            wait(&status);
            if(WIFEXITED(status))
            {
                printf("-----服务器进程正常退出-----\n");
                exit(0);
            }
        }else{//主程序
            int ret,i,j;
            //从配置文件读取信息
            char ip[15]={0},port[5]={0};
            int threadNum=0;
            ret=Read_Config(ip,port,&threadNum);
            ERROR_RETURN(ret);
        #ifdef DEBUG
            printf("server config: ip=%s,port=%s,threadNum=%d\n",ip,port,threadNum);
        #endif // DEBUG
            //创建线程
            Thread_Pool_Info_t threadPool;
            bzero(&threadPool,sizeof(Thread_Pool_Info_t));
            ThreadPool_Init(&threadPool,threadNum);
            ThreadPool_Start(&threadPool);
            //printf("-----线程创建完毕-----\n");
            //初始化服务器socketFd
            int socketFd;
            ret=Tcp_Init(&socketFd,ip,port);
            ERROR_RETURN(ret);
            //退出机制
            pipe(fds_exit);
            signal(SIGUSR1,SigFunc_Exit);//发送10号信号即退出
            //改变当前文件夹
            ret=chdir("../files");
            ERROR_CHECK(ret,-1,"chdir");
            //创建/打开日志文件,写入服务器启动信息
            time_t nowtime=time(NULL);
            char logBuf[128]={0};
            strcpy(logBuf,ctime(&nowtime));
            logBuf[strlen(logBuf)-1]=0;
            strcat(logBuf,"  **********服务器启动**********\n");
            int logFd=open("../conf/log.txt",O_RDWR|O_APPEND|O_CREAT,0666);
            ret=write(logFd,logBuf,strlen(logBuf));
            close(logFd);
            //epoll监听
            int epFd=epoll_create(1);
            ERROR_CHECK(epFd,-1,"epoll_create");
            Epoll_Add(epFd,socketFd);//将socketFd加入监听
            Epoll_Add(epFd,fds_exit[0]);//将fds_exit[0]加入监听
            struct epoll_event *pEvents;
            pEvents=(struct epoll_event*)calloc(2,sizeof(struct epoll_event));
            int readyFdCount=0;
            char exitFlag;
            int newFd;
            printf("-----服务器初始化完毕-----\n");
            while(1)
            {
                readyFdCount=epoll_wait(epFd,pEvents,2,-1);
                for(i=0;i<readyFdCount;i++)
                {
                    if(pEvents[i].data.fd==socketFd)
                    {
                        newFd=accept(socketFd,NULL,NULL);
                        ERROR_CHECK(newFd,-1,"accept");
                        printf("收到客户端的连接请求，newFd=%d\n",newFd);
                        //写日志
                        nowtime=time(NULL);
                        strcpy(logBuf,ctime(&nowtime));
                        logBuf[strlen(logBuf)-1]=0;
                        sprintf(logBuf,"%s 收到连接请求 newFd=%d\n",logBuf,newFd);
                        pthread_mutex_lock(&threadPool.log_mutex);//加锁
                        logFd=open("../conf/log.txt",O_RDWR|O_APPEND);
                        ret=write(logFd,logBuf,strlen(logBuf));
                        close(logFd);
                        pthread_mutex_unlock(&threadPool.log_mutex);//解锁
                        //加入工作队列
                        ret=WorkQueue_Add(newFd,threadPool.pWorkQueue);
                        if(-1==ret)
                        {
                            close(newFd);
                            continue;
                        }
                        pthread_cond_signal(&threadPool.cond);
                    }
                    if(pEvents[i].data.fd==fds_exit[0])//收到退出信号
                    {
                        ret=read(fds_exit[0],&exitFlag,1);
                        ERROR_CHECK(ret,-1,"read");
                        for(j=0;j<threadNum;j++)
                        {
                            ret=pthread_cancel(threadPool.pthId[j]);
                            THREAD_ERROR_CHECK(ret,"pthread_cancel");
                            printf("已向线程%ld发送结束信息\n",threadPool.pthId[j]);
                        }
                        for(j=0;j<threadNum;j++)
                        {
                            ret=pthread_join(threadPool.pthId[j],NULL);
                            THREAD_ERROR_CHECK(ret,"pthread_join");
                        }
                        //写日志
                        nowtime=time(NULL);
                        strcpy(logBuf,ctime(&nowtime));
                        logBuf[strlen(logBuf)-1]=0;
                        strcat(logBuf,"**********服务器结束运行**********\n\n");
                        pthread_mutex_lock(&threadPool.log_mutex);//加锁
                        logFd=open("../conf/log.txt",O_RDWR|O_APPEND);
                        ret=write(logFd,logBuf,strlen(logBuf));
                        close(logFd);
                        pthread_mutex_unlock(&threadPool.log_mutex);//解锁
                        printf("退出处理完毕\n");
                        exit(0);
                    }
                }
            }
        }
    }
}