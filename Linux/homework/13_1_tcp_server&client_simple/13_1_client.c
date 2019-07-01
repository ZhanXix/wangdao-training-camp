#include "func.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    int client_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(client_fd,-1,"socket");
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    client_addr.sin_family=AF_INET;
    client_addr.sin_addr.s_addr=inet_addr("192.168.5.192");
    client_addr.sin_port=atoi(argv[1]);
    ret=connect(client_fd,(struct sockaddr*)&client_addr,sizeof(client_addr));
    ERROR_CHECK(ret,-1,"connect");
    char buf[128]={0};
    ret=recv(client_fd,buf,sizeof(buf),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("客户端从服务器收到数据：%s\n",buf);
    ret=send(client_fd,"hi!I am client",14,0);
    close(client_fd);
    return 0;
}