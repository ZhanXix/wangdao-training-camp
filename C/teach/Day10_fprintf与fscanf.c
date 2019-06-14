#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct 
{
	int num;
	float score;
	char name[20];
}Student_t;

int main(int argc,char *argv[])
{
	Student_t s = { 1001,98.5,"lele" };
	FILE* fp;
	if (argc != 2)
	{
		printf("error args\n");
		goto error;
	}
	fprintf(fp,"%d %5.2f %s\n", s.num, s.score, s.name);
	//fprintf(stdout, "%d %5.2f %s\n", s.num, s.score, s.name);  标准输出，和printf一样会打印到屏幕上
error:
	system("pause");
}