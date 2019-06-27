#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,3);
    int ret;
    ret=kill(atoi(argv[2]),atoi(argv[1]));   
    ERROR_CHECK(ret,-1,"kill");
    return 0;
}

