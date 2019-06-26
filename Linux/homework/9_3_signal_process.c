//signal设置信号处理行为，演示不同信号到来时，后来的信号会打断原有信号的信号处理函数效果
#include <func.h>

void signal_handler(int signal_num)
{
    printf("捕捉信号：%d\n",signal_num);
    sleep(4);
    printf("信号%d处理完毕！\n",signal_num);
}
int main(int argc,char *argv[])
{
    signal(SIGINT,signal_handler);
    signal(SIGQUIT,signal_handler);
    while(1);
    return 0;
}

