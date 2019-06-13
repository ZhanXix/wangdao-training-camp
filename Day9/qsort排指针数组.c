#include <stdio.h>
#include <stdlib.h>

typedef struct student
{
	int num;
	struct student* pNext;
}Student_t, * pStudent_t;

int comparePoint(const void* pleft, const void* pright)
{
	pStudent_t* p1 = (pStudent_t*)pleft;
	pStudent_t* p2 = (pStudent_t*)pright;
	return (*p1)->num - (*p2)->num;
}

int main()
{
	int i, listLen = 0;
	pStudent_t* pArr;	//指针数组
	pStudent_t phead, ptail, pNew, pCur;
	phead = ptail = NULL;
	while (scanf("%d", &i) != EOF)
	{
		pNew = (pStudent_t)calloc(1, sizeof(Student_t));
		pNew->num = i;
		if (NULL == phead)
		{
			phead = pNew;
			ptail = pNew;
		}
		else
		{
			pNew->pNext = phead;
			phead = pNew;
		}
		listLen++;
	}
	pArr = (pStudent_t*)malloc(listLen * sizeof(pStudent_t));//存储listLen个指针
	pCur = phead;
	for (i = 0; i < listLen; i++)
	{
		pArr[i] = pCur;
		pCur = pCur->pNext;
	}
	qsort(pArr, listLen, sizeof(pStudent_t), comparePoint);
	for (i = 0; i < listLen; i++)
	{
		printf("%3d", pArr[i]->num);
	}
	putchar('\n');
	while (phead)//链表的销毁
	{
		pCur = phead;
		phead = phead->pNext;
		free(pCur);
		pCur = NULL;
	}
	ptail = NULL;
	system("pause");
}