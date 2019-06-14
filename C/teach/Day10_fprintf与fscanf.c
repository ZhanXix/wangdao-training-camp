#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct
{
	int num;
	float score;
	char name[20];
}Student_t;

int main(int argc, char* argv[])
{
	Student_t s = { 1001,98.5,"lele" };
	FILE* fp;
	int ret;
	if (argc != 2)
	{
		printf("error args\n");
		goto error;
	}
	fp = fopen(argv[1], "r+");
	//fprintf(fp,"%d %5.2f %s\n", s.num, s.score, s.name);
	//fprintf(stdout, "%d %5.2f %s\n", s.num, s.score, s.name);  ��׼�������printfһ�����ӡ����Ļ��
	while (memset(&s, 0, sizeof(Student_t)), fscanf(fp, "%d%f%s", &s.num, &s.score, s.name) != EOF)
	{
		printf("%d %5.2f %s\n", s.num, s.score, s.name);
	}
	fclose(fp);
error:
	system("pause");
}