//这一题day10的时候就写了，但是当时没有看清楚题目要求，全部用的是管道。所以今天重写了。

//注：开启顺序必须是先开chatA再开chatA1、先开chatB再开chatB1，否则会出现由于未初始化而产生的读取错误。
//关闭则是任意在chatA或者chatB窗口使用ctrl+C，则会实现四个进程全部关闭且清理全部管道文件、信号量、共享内存、消息队列

#include "func.h" 
struct msgbuf{
    char type;
    char mtext[255];
}Msgbuf_t;
void sigFunc(int signum)
{
    unlink("chatAB.pipe");
    unlink("chatBA.pipe");
    int shmAA=shmget(1000,sizeof(Msgbuf_t),IPC_CREAT|0666);
    struct msgbuf *pAA=(struct msgbuf*)shmat(shmAA,NULL,0);;
    int semAA=semget(1000,2,IPC_CREAT|0600);
    if(2==signum)
    {
        struct sembuf sopp,sopv;
        sopp.sem_num=0;
        sopp.sem_op=-1;
        sopp.sem_flg=SEM_UNDO;
        sopv.sem_num=1;
        sopv.sem_op=1;
        sopv.sem_flg=SEM_UNDO;
        semop(semAA,&sopp,1);
        pAA->type='E';//exitA
        semop(semAA,&sopv,1);
    }
    shmctl(shmAA,IPC_RMID,NULL);
    semctl(semAA,0,IPC_RMID);
    exit(0);
}
int main()
{
    system("clear");
    int ret;
    signal(SIGINT,sigFunc);
    //管道 A-B B-A
    mkfifo("chatAB.pipe",0666);
    mkfifo("chatBA.pipe",0666); 
    int fdwAB=open("chatAB.pipe",O_WRONLY);
    int fdrBA=open("chatBA.pipe",O_RDONLY);
    //共享内存 A-A1
    int shmAA=shmget(1000,sizeof(Msgbuf_t),IPC_CREAT|0666);
    struct msgbuf *pAA=(struct msgbuf *)shmat(shmAA,NULL,0);
    pAA->type='0';
    bzero(pAA->mtext,255);
    //信号量
    int semAA=semget(1000,2,IPC_CREAT|0600);
    ERROR_CHECK(semAA,-1,"semget");
    unsigned short arr[2]={1,0};//0号信号量的值代表还能存放的消息数，1号信号量的值代表当前消息数
    semctl(semAA,0,SETALL,arr);
    struct sembuf sopp,sopv;
    sopp.sem_num=0;
    sopp.sem_op=-1;
    sopp.sem_flg=SEM_UNDO;
    sopv.sem_num=1;
    sopv.sem_op=1;
    sopv.sem_flg=SEM_UNDO;
    //输入输出
    int fdMax=fdwAB>fdrBA?fdwAB+1:fdrBA+1;
    fd_set wrset,rdset;
    char buf[254]={0};
    while(1)
    {
        FD_ZERO(&wrset);
        FD_SET(fdwAB,&wrset);
        FD_ZERO(&rdset);
        FD_SET(fdrBA,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        ret=select(fdMax,&rdset,&wrset,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdwAB,&wrset)&&FD_ISSET(STDIN_FILENO,&rdset))
        {
            system("clear");
            bzero(&buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            if(ret)
            {
                semop(semAA,&sopp,1);
                bzero(pAA->mtext,255);
                strcpy(pAA->mtext,buf);
                pAA->type='A';
                semop(semAA,&sopv,1);
                write(fdwAB,buf,strlen(buf));
            }else{
                break;
            }
        }
        if(FD_ISSET(fdrBA,&rdset))
        {
            bzero(&buf,sizeof(buf));
            ret=read(fdrBA,buf,sizeof(buf));
            if(ret)
            {
                semop(semAA,&sopp,1);
                bzero(pAA->mtext,255);
                strcpy(pAA->mtext,buf);
                pAA->type='B';
                semop(semAA,&sopv,1);
            }else{
                semop(semAA,&sopp,1);
                pAA->type='F';//exitB
                semop(semAA,&sopv,1);
                sigFunc(0);
                break;
            }
        }
    }
    return 0;
}
