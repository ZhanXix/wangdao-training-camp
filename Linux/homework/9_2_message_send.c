//创建消息队列，发送消息
#include <func.h>

struct message{
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    struct message msg_buf;
    msg_buf.mtype=atoi(argv[1]);
    strcpy(msg_buf.mtext,argv[2]);
    int ret=msgsnd(msgid,&msg_buf,strlen(msg_buf.mtext),0);
    ERROR_CHECK(ret,-1,"msgsnd");
    printf("成功发送消息！类型%ld,内容%s\n",msg_buf.mtype,msg_buf.mtext);
    return 0;
}

