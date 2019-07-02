#include <func.h>

int tcpInit(int *sfd,char *argv1,char *argv2)
{
    int socketFd=socket(AF_INET,SOCK_STREAM,0);//生成一个套接口描述符
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in serAddr;
    bzero(&serAddr,sizeof(serAddr));
    serAddr.sin_family=AF_INET;
    serAddr.sin_port=htons(atoi(argv2));//port编号
    serAddr.sin_addr.s_addr=inet_addr(argv1);//IP地址；inet_addr用于将点分十进制数的IP地址转换为网络字节序的32位二进制数值
    int ret;
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&serAddr,sizeof(serAddr));//绑定一个端口号和IP地址，使套接口与指定的端口号和IP地址相关联
    ERROR_CHECK(ret,-1,"bind");
    listen(socketFd,10);//10是缓冲区大小；listen使服务器的这个端口和IP处于监听状态
    *sfd=socketFd;
    return 0; 
}

