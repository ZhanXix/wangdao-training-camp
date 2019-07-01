#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int socketFd=socket(AF_INET,SOCK_STREAM,0);//生成一个套接口描述符
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv[2]));//port编号
    serAddr.sin_addr.s_addr=inet_addr(argv[1]);//IP地址；inet_addr用于将点分十进制数的IP地址转换为网络字节序的32位二进制数值
    int ret;
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));//绑定一个端口号和IP地址，使套接口与指定的端口号和IP地址相关联
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//10是缓冲区大小；listen使服务器的这个端口和IP处于监听状态
    struct sockaddr_in client;
    bzero(&client,sizeof(client));
    socklen_t clientLen=sizeof(client);
    int newFd=accept(socketFd,(struct sockaddr*)&client,&clientLen);//接受远程计算机的连接请求，建立起与客户机之间的通信连接
    printf("client ip=%s,client port=%d\n",inet_ntoa(client.sin_addr),ntohs(client.sin_port));
    char buf[1024]={0};
    recv(newFd,buf,sizeof(buf),0);//用新的套接字来接收远端主机传来的数据
    printf("server gets %s\n",buf);
    send(newFd,"hello world",11,0);//用新的套接字发送数据给指定的远端主机
    //while(1);
    close(socketFd);
    close(newFd);
    return 0;
}

