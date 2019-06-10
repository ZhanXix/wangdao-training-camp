/*
有一个学生结构体，其数据成员有：学号，姓名，3门课程。
从键盘上输入5个学生的信息。
要求输出：
(1) 按照学号递增输出全部学生信息，每个学生的信息一行。(格式： 学号 姓名 分数 1 分数 2 分数 3 总分)
(2) 输出每门课程最高分的学生的信息
(3) 输出每门课程的平均分
(4) 按照总分输出学生排名
*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct student
{
	int id;
	char* name[20];
	float score[3];
	float total;
}Student_t, * pStudent_t;

int cmp1(const void* a, const void* b)
{
	return(*(pStudent_t)a).id > (*(pStudent_t)b).id ? 1 : -1;
}
int cmp2(const void* a, const void* b)
{
	return(*(pStudent_t)a).total > (*(pStudent_t)b).total? -1 : 1;
}
int main()
{
	Student_t s[5];
	pStudent_t p[5];
	int i, j;
	do
	{
		printf("输入5个学生的信息:\n");
		for (i = 0; i < 5; ++i)
		{
			scanf("%d%s%f%f%f", &s[i].id, s[i].name, &s[i].score[0], &s[i].score[1], &s[i].score[2]);
			s[i].total = s[i].score[0] + s[i].score[1] + s[i].score[2];
			p[i] = &s[i];
		}
		printf("--------------------------------------\n");
		printf("按学号递增输出：\n");
		qsort(*p, 5, sizeof(Student_t), cmp1);
		for (i = 0; i < 5; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", p[i]->id, p[i]->name, p[i]->score[0], p[i]->score[1], p[i]->score[2], p[i]->total);
		}
		printf("--------------------------------------\n");
		pStudent_t maxScore[3] = { &s[0],&s[0], &s[0] };
		for (i = 1; i < 5; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				if (s[i].score[j] > maxScore[j]->score[j])
				{
					maxScore[j] = &s[i];
				}
			}
		}
		printf("单科分数最高的三位学生分别为：\n");
		for (int i = 0; i < 3; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", maxScore[i]->id, maxScore[i]->name, maxScore[i]->score[0], maxScore[i]->score[1], maxScore[i]->score[2], maxScore[i]->total);
		}
		printf("--------------------------------------\n");
		float ave[3] = { 0 };
		for (i = 0; i < 5; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				ave[j] += s[i].score[j];
			}
		}
		printf("每门课程的平均分分别为：%5.2f %5.2f %5.2f\n", ave[0] / 5, ave[1] / 5, ave[2] / 5);
		printf("--------------------------------------\n");
		printf("按照总分输出学生排名：\n");
		qsort(*p, 5, sizeof(Student_t), cmp2);
		for (i = 0; i < 5; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", p[i]->id, p[i]->name, p[i]->score[0], p[i]->score[1], p[i]->score[2], p[i]->total);
		}
		rewind(stdin);
		printf("\n要继续，请输入y...");
	} while (getchar() == 'y');
	system("pause");
}