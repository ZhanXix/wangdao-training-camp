#include "func.h"
#define SERVER_STRING "Server: jdbhttpd/0.1.0\r\n"
void headers(int);
void cat(int,FILE*);
int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("error args\n");
		return -1;
	}
	int sfd;
	sfd=socket(AF_INET,SOCK_STREAM,0);
	if(-1==sfd)
	{
		perror("socket");
		return -1;
	}
	printf("sfd=%d\n",sfd);
	struct sockaddr_in ser;
	bzero(&ser,sizeof(ser));
	ser.sin_family=AF_INET;
	ser.sin_port=htons(atoi(argv[2]));//一定要用htons
	ser.sin_addr.s_addr=inet_addr(argv[1]);
	int ret=bind(sfd,(struct sockaddr*)&ser,sizeof(struct sockaddr));
	if(-1==ret)
	{
		perror("bind");
		return -1;
	}
	listen(sfd,10);
	int new_fd;
	struct sockaddr_in client;
	bzero(&client,sizeof(client));
	int len=sizeof(client);
	new_fd=accept(sfd,(struct sockaddr *)&client,&len);
	printf("new_fd=%d,ip=%s,port=%d\n",new_fd,inet_ntoa(client.sin_addr),ntohs(client.sin_port));
	char buf[4096]={0};
	ret=recv(new_fd,buf,sizeof(buf),0);
	if(-1==ret)
	{
		perror("recv");
		return -1;
	}
	printf("%s\n",buf);
    bzero(buf,sizeof(buf));
	headers(new_fd);
	return 0;
}
void headers(int client)
{
    char buf[1024];

    strcpy(buf, "HTTP/1.0 500 ERROR NOT KNOWN\r\n");
    send(client, buf, strlen(buf), 0);
//    strcpy(buf, SERVER_STRING);
//    send(client, buf, strlen(buf), 0);
//    sprintf(buf, "Content-Type: text/html\r\n");
//    send(client, buf, strlen(buf), 0);
    strcpy(buf, "\r\n");
    send(client, buf, strlen(buf), 0);
}
void cat(int client, FILE *resource)
{
    char buf[1024];

    fgets(buf, sizeof(buf), resource);
    while (!feof(resource))
    {
        send(client, buf, strlen(buf), 0);
        fgets(buf, sizeof(buf), resource);
    }
}
