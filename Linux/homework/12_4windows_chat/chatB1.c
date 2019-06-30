#include "func.h"
struct msgbuf{
    long mtype;
    char mtext[255];
};
int main()
{
    system("clear");
    //消息队列B-B
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msgInfo;
    while(1)
    {
        bzero(&msgInfo,sizeof(msgInfo));
        int ret=msgrcv(msgid,&msgInfo,sizeof(msgInfo.mtext),0,0);
        ERROR_CHECK(ret,-1,"msgrcv");
        if(1==msgInfo.mtype)
        {
            printf("%77s",msgInfo.mtext);
        }else if(2==msgInfo.mtype){
            printf("%s",msgInfo.mtext);
        }else if(3==msgInfo.mtype){
            printf("---------------对话主动中止---------------\n");
            break;
        }else if(4==msgInfo.mtype){
            printf("----------------对话已中止----------------\n");
            break;
        }else{
            printf("消息队列读取错误!\n");
            break;
        }
    }
    return 0;
}