#include <stdio.h>
#include <iostream>
using std::cout;
using std::endl;

int main()
{
    int a=1;
    printf("sizeof(a) = %ld\n",sizeof a);
    printf("sizeof(a) = %ld\n",sizeof(a));
    return 0;
}

