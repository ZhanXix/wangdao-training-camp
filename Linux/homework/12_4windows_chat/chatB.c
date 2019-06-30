#include "func.h"
struct msgbuf{
    long mtype;
    char mtext[255];
};
void sigFunc(int signum)
{
    int msgid=msgget(1000,IPC_CREAT|0666);
    struct msgbuf msgInfo;
    if(2==signum)
    {
        msgInfo.mtype=3;
        msgsnd(msgid,&msgInfo,strlen(msgInfo.mtext),0);
    }
    msgctl(msgid,IPC_RMID,NULL);
    exit(0);
}
int main()
{
    system("clear");
    int ret;
    signal(SIGINT,sigFunc);
    //管道 A-B B-A
    int fdrAB=open("chatAB.pipe",O_RDONLY);
    int fdwBA=open("chatBA.pipe",O_WRONLY);
    //消息队列B-B
    int msgid=msgget(1000,IPC_CREAT|0600);
    struct msgbuf msgInfo;
    //输入输出
    int fdMax=fdwBA>fdrAB?fdwBA+1:fdrAB+1;
    fd_set wrset,rdset;
    char buf[254]={0};
    while(1)
    {
        FD_ZERO(&wrset);
        FD_SET(fdwBA,&wrset);
        FD_ZERO(&rdset);
        FD_SET(fdrAB,&rdset);
        FD_SET(STDIN_FILENO,&rdset);
        ret=select(fdMax,&rdset,&wrset,NULL,NULL);
        ERROR_CHECK(ret,-1,"select");
        if(FD_ISSET(fdwBA,&wrset)&&FD_ISSET(STDIN_FILENO,&rdset))
        {
            system("clear");
            bzero(&buf,sizeof(buf));
            ret=read(STDIN_FILENO,buf,sizeof(buf));
            bzero(&msgInfo,sizeof(msgInfo));
            if(ret)
            {
                msgInfo.mtype=1;
                strcpy(msgInfo.mtext,buf);
                ret=msgsnd(msgid,&msgInfo,strlen(msgInfo.mtext),0);
                ERROR_CHECK(ret,-1,"msgsnd");
                write(fdwBA,buf,strlen(buf));
            }else{
                break;
            }
        }
        if(FD_ISSET(fdrAB,&rdset))
        {
            bzero(&buf,sizeof(buf));
            ret=read(fdrAB,buf,sizeof(buf));
            bzero(&msgInfo,sizeof(msgInfo));
            if(ret)
            {
                msgInfo.mtype=2;
                strcpy(msgInfo.mtext,buf);
                ret=msgsnd(msgid,&msgInfo,strlen(msgInfo.mtext),0);
                ERROR_CHECK(ret,-1,"msgsnd");
            }else{
                bzero(&msgInfo,sizeof(msgInfo));
                msgInfo.mtype=4;
                msgsnd(msgid,&msgInfo,strlen(msgInfo.mtext),0);
                sigFunc(0);
                break;
            }
        }
    }
    return 0;
}