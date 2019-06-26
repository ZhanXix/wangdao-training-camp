//接收消息
#include <func.h>

struct message{
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct message msg_buf;
    memset(&msg_buf,0,sizeof(msg_buf));
    int ret=msgrcv(msgid,&msg_buf,sizeof(msg_buf.mtext),atoi(argv[1]),IPC_NOWAIT);
    ERROR_CHECK(ret,-1,"msgrcv");
    printf("成功接收消息！类型%ld,内容%s\n",msg_buf.mtype,msg_buf.mtext);
    return 0;
}

