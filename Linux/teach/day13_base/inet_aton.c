#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    struct in_addr netIp;
    int ret;
    ret=inet_aton(argv[1],&netIp);
    if(0==ret)
    {
        fprintf(stderr,"Invalid address\n");
        return -1;
    }
    printf("%x\n",netIp.s_addr);
    printf("ip=%s\n",inet_ntoa(netIp));
    printf("%x\n",inet_addr(argv[1]));
    return 0;
}

