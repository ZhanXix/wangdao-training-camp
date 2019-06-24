#include <func.h>

int main(int argc,char *argv[])
{
    int i;
    for(i=0;i<argc;i++)
    {
        puts(argv[i]);
    }
    printf("I am print process\n");    
    while(1);
    return 0;
}

