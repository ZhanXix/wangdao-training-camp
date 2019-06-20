#include <func.h>

int main(int argc,char *argv[])
{
    ARGS_CHECK(argc,2);
    int ret;
    ret=mkdir(argv[1],0777);
    ERROR_CHECK(ret,-1,"mkdir");
    return 0;
}
