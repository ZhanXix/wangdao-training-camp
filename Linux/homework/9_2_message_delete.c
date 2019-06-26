//删除消息队列
#include <func.h>

struct message{
    long mtype;
    char mtext[128];
};
int main(int argc,char *argv[])
{
    int msgid=msgget(1000,IPC_CREAT|0600);
    ERROR_CHECK(msgid,-1,"msgget");
    int ret=msgctl(msgid,IPC_RMID,NULL);
    ERROR_CHECK(ret,-1,"msgctl");
    printf("成功删除消息队列！\n");
    return 0;
}

