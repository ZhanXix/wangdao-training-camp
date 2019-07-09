#include "func.h"

int main(int argc,char** argv)
{
	args_check(argc,3);
	int sfd;
	//初始化socket,UDP
	sfd=socket(AF_INET,SOCK_DGRAM,0);
	check_error(-1,sfd,"socket");
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));//端口号转换为网络字节序
	ser.sin_addr.s_addr=inet_addr(argv[1]);//点分10进制的IP地址转为网络字节序
	int ret;
	char buf[128]={0};
	int epfd=epoll_create(1);
	struct epoll_event event,evs[2];
	event.events=EPOLLIN;//是否可读
	event.data.fd=STDIN_FILENO;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,STDIN_FILENO,&event);
	check_error(-1,ret,"epoll_ctl");
	event.data.fd=sfd;
	ret=epoll_ctl(epfd,EPOLL_CTL_ADD,sfd,&event);
	check_error(-1,ret,"epoll_ctl1");
	int i;
	int ret_num;
	while(1)
	{
		ret=epoll_wait(epfd,evs,2,-1);
		for(i=0;i<ret;i++)
		{
			if(evs[i].data.fd==sfd)
			{
				bzero(buf,sizeof(buf));
				ret_num=recvfrom(sfd,buf,sizeof(buf),0,NULL,NULL);
				check_error(-1,ret_num,"recvfrom");
				printf("%s\n",buf);
			}
			if(evs[i].data.fd==STDIN_FILENO)
			{
				bzero(buf,sizeof(buf));
				read(0,buf,sizeof(buf));
				ret_num=sendto(sfd,buf,strlen(buf)-1,0,(struct sockaddr*)&ser,sizeof(ser));
				check_error(-1,ret_num,"sendto");
			}
		}
	}
	close(sfd);
}
