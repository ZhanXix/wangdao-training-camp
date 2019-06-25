#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    key_t key;
    key=ftok(argv[1],1);
    printf("key=%d\n",key);
    return 0;
}

