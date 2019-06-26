#include <func.h>
struct msgbuf{
    long mtype;
    char mtext[64];
};
int main(int argc,char *argv[])
{
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct msgbuf msgInfo;
    msgInfo.mtype=1;
    strcpy(msgInfo.mtext,"hello");
    int ret=msgsnd(msgid,&msgInfo,strlen(msgInfo.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    return 0;
}

