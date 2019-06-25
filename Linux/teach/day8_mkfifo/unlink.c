#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    ret=unlink(argv[1]);
    ERROR_CHECK(ret,-1,"unlink");
    return 0;
}

