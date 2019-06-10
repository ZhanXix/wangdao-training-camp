#include <stdio.h> 
#include <stdlib.h> 

int k = 0;//全局变量
void print()
{
	k++;
	printf("I am print k = %d\n", k);
}
//全局变量阅读难度提升
int main()
{
	int i = 5;//就近原则
	printf("I am main i = %d\n", i);
	print();
	print();
	system("pause");
}
