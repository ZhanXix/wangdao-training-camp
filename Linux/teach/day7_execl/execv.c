#include <func.h>

int main(int argc,char *argv[])
{
    sleep(10);
    char *const args[]={"niuniu","123","456",NULL};
    execv("./print",args);
    printf("you can't see me\n");
    return 0;
}

