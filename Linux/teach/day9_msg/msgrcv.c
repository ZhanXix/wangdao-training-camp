#include <func.h>
typedef struct msgbuf{
    long mtype;
    char mtext[64];
}MSG_T;
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msgInfo;
    bzero(&msgInfo,sizeof(msgInfo));
    int ret=msgrcv(msgid,&msgInfo,sizeof(msgInfo.mtext),atoi(argv[1]),0);
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("mtype=%ld,mtext=%s\n",msgInfo.mtype,msgInfo.mtext);
    return 0;
}

