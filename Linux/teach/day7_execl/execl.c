#include <func.h>

int main(int argc,char *argv[])
{
    sleep(10);
    execl("./print","niuniu","123","456",NULL);
    printf("you can't see me\n");
    return 0;
}

