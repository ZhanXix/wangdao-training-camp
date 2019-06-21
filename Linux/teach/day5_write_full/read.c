#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int fdr=open(argv[1],O_RDONLY);
    printf("I am reader fdr=%d\n",fdr);
    char buf[128]={0};
    while(1);
    return 0;
}

