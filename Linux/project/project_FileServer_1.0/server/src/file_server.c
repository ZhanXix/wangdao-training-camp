#include "file_server.h"

int Read_Config(char *ip,char *port,int *threadNum)//读取配置文件中的信息
{
    int i,j;
    FILE *fp=fopen("../conf/server.conf","r");
    ERROR_CHECK(fp,(FILE*)-1,"fopen");
    char buf[256]={0},name[40]={0},thNum[8]={0};
    while(fgets(buf,sizeof(buf),fp)!=NULL)
    {
        for(i=0;i<sizeof(buf)&&buf[i]!=0;++i)
        {
            if('='==buf[i])
            {
                break;
            }
            name[i]=buf[i];
        }
        if(strcmp(name,"ip")==0)//读入ip
        {
            for(j=0,i+=1;i<sizeof(buf)&&buf[i]!='\n'&&buf[i]!=0;++i,++j)
            {
                ip[j]=buf[i];
            }
        }else if(strcmp(name,"port")==0){//读入端口号
            for(j=0,i+=1;i<sizeof(buf)&&buf[i]!='\n'&&buf[i]!=0;++i,++j)
            {
                port[j]=buf[i];
            }
        }else if(strcmp(name,"threadNum")==0){//读入线程数
            for(j=0,i+=1;i<sizeof(buf)&&buf[i]!='\n'&&buf[i]!=0;++i,++j)
            {
                thNum[j]=buf[i];
            }
            *threadNum=atoi(thNum);
        }
        bzero(buf,sizeof(buf));
        bzero(name,sizeof(name));
    }
    return 0;
}

int Tcp_Init(int *pSocketFd,char *ip,char *port)//初始化服务器端口监听
{
    int ret;
    int socketFd;
    socketFd=socket(AF_INET,SOCK_STREAM,0);
    ERROR_CHECK(socketFd,-1,"socket");
    struct sockaddr_in socketAddr;
    bzero(&socketAddr,sizeof(socketAddr));
    socketAddr.sin_family=AF_INET;
    socketAddr.sin_addr.s_addr=inet_addr(ip);
    socketAddr.sin_port=htons(atoi(port));
    int reuse=1;
    ret=setsockopt(socketFd,SOL_SOCKET,SO_REUSEADDR,&reuse,sizeof(int));
    ERROR_CHECK(ret,-1,"setsockopt");
    ret=bind(socketFd,(struct sockaddr*)&socketAddr,sizeof(socketAddr));
    ERROR_CHECK(ret,-1,"bind");
    ret=listen(socketFd,10);
    ERROR_CHECK(ret,-1,"listen");
    *pSocketFd=socketFd;
    return 0;
}

int Epoll_Add(int epFd,int socketFd)//添加epoll监视
{
    int ret;
    struct epoll_event event;
    event.events=EPOLLIN;
    event.data.fd=socketFd;
    ret=epoll_ctl(epFd,EPOLL_CTL_ADD,socketFd,&event);
#ifdef DEBUG
    printf("epoll已添加监视%d\n",socketFd);
#endif // DEBUG
    ERROR_CHECK(ret,-1,"epoll_ctl");
    return 0;
}