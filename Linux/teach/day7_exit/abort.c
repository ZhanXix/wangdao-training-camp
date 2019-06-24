#include <func.h>
void print()
{
    printf("I am print");
    abort();

}
int main(int argc,char* argv[])
{
    print();
    printf("after print\n");
    return 0;
}

