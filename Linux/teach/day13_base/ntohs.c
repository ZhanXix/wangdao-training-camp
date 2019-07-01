#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    short port=atoi(argv[1]);
    short nport=htons(port);
    printf("%x\n",nport);
    port=0;
    port=ntohs(nport);
    printf("%x\n",port);
    return 0;
}

