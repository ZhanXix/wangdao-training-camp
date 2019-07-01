#include <func.h>
//名字地址转化
int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct hostent *p;
    p=gethostbyname(argv[1]);
    if(NULL==p)
    {
        printf("gethostbyname fail\n");
        return -1;
    }
    printf("%s\n",p->h_name);//正式主机名
    int i;
    for(i=0;p->h_aliases[i]!=NULL;i++)
    {
        puts(p->h_aliases[i]);//主机别名
    }
    printf("%d\n",p->h_addrtype);//主机IP地址类型，IPv4为AF_INET
    printf("%d\n",p->h_length);//主机IP地址字节长度
    char ip[16]={0};
    for(i=0;p->h_addr_list[i]!=NULL;i++)//主机的IP地址列表
    {
        bzero(ip,sizeof(ip));
        inet_ntop(p->h_addrtype,p->h_addr_list[i],ip,sizeof(ip));//将网络字节序的32位二进制数值转换为点分十进制的IP地址
        puts(ip);
    }
    return 0;
}

