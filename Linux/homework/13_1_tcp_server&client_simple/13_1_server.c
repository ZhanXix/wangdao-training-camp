//一个客户端，一个服务器端，客户端向服务器发送一句话，服务器向客户端发送一句话
#include "func.h"

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    int socket_fd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socket_fd,-1,"socket");
    struct sockaddr_in socket_addr;
    bzero(&socket_addr,sizeof(socket_addr));
    socket_addr.sin_family=AF_INET;
    socket_addr.sin_addr.s_addr=inet_addr("192.168.5.192");
    socket_addr.sin_port=atoi(argv[1]);
    ret=bind(socket_fd,(struct sockaddr*)&socket_addr,sizeof(socket_addr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(socket_fd,1);
    ERROR_CHECK(ret,-1,"listen");
    struct sockaddr_in client_addr;
    bzero(&client_addr,sizeof(client_addr));
    int client_addr_len=sizeof(client_addr);
    int new_fd=accept(socket_fd,(struct sockaddr*)&client_addr,&client_addr_len);
    ERROR_CHECK(new_fd,-1,"accept");
    char buf[128]={0};
    ret=send(new_fd,"hello!I am server",17,0);
    ERROR_CHECK(ret,-1,"send");
    ret=recv(new_fd,buf,sizeof(buf),0);
    ERROR_CHECK(ret,-1,"recv");
    printf("服务器从客户端收到数据：%s\n",buf);
    close(socket_fd);
    close(new_fd);
    return 0;
}