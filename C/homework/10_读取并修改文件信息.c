/*
 * 有一个记录学生信息的文件，每一行记录一名学生的信息，格式如下：
 * 学号\t 姓名\t 性别\t 分数1\t 分数2\t 分数3\n.
 * 要求：（1）读取文件的内容，串成一个链表。
 * （2）按照总分递减排序将结果保存到原文件。
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct student_information_node
{
	unsigned id;
	char name[24];
	char sex;
	float score[3];
	struct student_information_node* pNext;
}Information_t, * pInformation_t;

int cmp(const void* a, const void* b)
{
	pInformation_t* pa = (pInformation_t*)a;
	pInformation_t* pb = (pInformation_t*)b;
	if ((*pb)->score[0] + (*pb)->score[1] + (*pb)->score[2] - (*pa)->score[0] - (*pa)->score[1] - (*pa)->score[2] > 0)
	{
		return 1;
	}
	else
	{
		return -1;
	}
}
void Create_New_student_information_node(pInformation_t* ppHead, pInformation_t* ppTail, pInformation_t s)
{
	int i;
	pInformation_t pNew = (pInformation_t)malloc(sizeof(Information_t));
	pNew->id = s->id;
	strcpy(pNew->name, s->name);
	pNew->sex = s->sex;
	pNew->pNext = NULL;
	for (i = 0; i < 3; ++i)
	{
		pNew->score[i] = s->score[i];
	}
	if (NULL == *ppHead)
	{
		*ppHead = pNew;
		*ppTail = pNew;
	}
	else
	{
		(*ppTail)->pNext = pNew;
		*ppTail = pNew;
	}
}
int main(int argc, char* argv[])
{
	pInformation_t pHead = NULL, pTail = NULL, pCur;
	FILE* fp;
	pInformation_t s;
	pInformation_t* pArr;
	int num = 0, i = 0;
	s = (pInformation_t)malloc(sizeof(Information_t));
	if (argc != 2)
	{
		printf("error args\n");
		goto error;
	}
	fp = fopen(argv[1], "r");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	while (memset(s, 0, sizeof(Information_t)), fscanf(fp, "%d\t%s\t%c\t%f\t%f\t%f", &s->id, s->name, &s->sex, &s->score[0], &s->score[1], &s->score[2]) != EOF)
	{
		Create_New_student_information_node(&pHead, &pTail, s);
		++num;
	}
	fclose(fp);
	free(s);
	s = NULL;
	pCur = pHead;
	pArr = (pInformation_t*)malloc(num * sizeof(pInformation_t));
	while (pCur)
	{
		pArr[i] = pCur;
		pCur = pCur->pNext;
		i++;
	}
	qsort(pArr, num, sizeof(pInformation_t), cmp);
	fp = fopen(argv[1], "w");
	for (i = 0; i < num; ++i)
	{
		printf("%d\t%s\t%c\t%5.2f\t%5.2f\t%5.2f\t%5.2f\n", pArr[i]->id, pArr[i]->name, pArr[i]->sex, pArr[i]->score[0], pArr[i]->score[1], pArr[i]->score[2], pArr[i]->score[0] + pArr[i]->score[1] + pArr[i]->score[2]);
		fprintf(fp, "%d\t%s\t%c\t%5.2f\t%5.2f\t%5.2f\n", pArr[i]->id, pArr[i]->name, pArr[i]->sex, pArr[i]->score[0], pArr[i]->score[1], pArr[i]->score[2]);
	}
	fclose(fp);
error:
	system("pause");
}