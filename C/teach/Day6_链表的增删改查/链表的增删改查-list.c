#include "链表的增删改查-list.h"

//链表头插法
void listHeadInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));//1是申请空间的数量
	//calloc可以把空间内所有数据置为0
	pNew->num = val;
	if (NULL == *ppHead)//判断链表是否为空
	{
		*ppHead = pNew;
		*ppTail = pNew;
	}
	else
	{
		pNew->pNext = *ppHead;
		*ppHead = pNew;
	}
}

//链表打印
void listPrint(pStudent_t pHead)
{
	while (pHead != NULL)
	{
		printf("%3d %5.2f\n", pHead->num, pHead->score);
		pHead = pHead->pNext;
	}
	putchar('\n');
}

//链表尾插法
void listTailInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));
	pNew->num = val;
	if (NULL == *ppTail)//判断链表是否为空
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

//链表有序插入
void listSortInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));
	pStudent_t pCur = *ppHead, pPre;
	pNew->num = val;
	if (NULL == *ppHead)//判断链表是否为空
	{
		*ppHead = pNew;
		*ppTail = pNew;
	}
	else if (val < pCur->num)//头插法
	{
		pNew->pNext = *ppHead;
		*ppHead = pNew;
	}
	else
	{
		while (pCur)
		{
			if (pCur->num > val)
			{
				pPre->pNext = pNew;
				pNew->pNext = pCur;
				break;
			}
			pPre = pCur;
			pCur = pCur->pNext;
		}
		if (NULL == pCur)//尾插法
		{
			pPre->pNext = pNew;
			*ppTail = pNew;
		}
	}
}

//链表的删除
void listDelete(pStudent_t* ppHead, Student_t** ppTail, int deleteNum)
{
	pStudent_t pCur = *ppHead;
	pStudent_t pPre = pCur;
	if (NULL == pCur)
	{
		printf("List is empty.\n");
	}
	else if (deleteNum == pCur->num)//删除的是头部
	{
		*ppHead = pCur->pNext;
		if (NULL == *ppHead)
		{
			*ppTail = NULL;
		}
	}
	else
	{
		while (pCur)	//删除的是中间或尾部
		{
			if (deleteNum == pCur->num)
			{
				pPre->pNext = pCur->pNext;
				break;
			}
			pPre = pCur;
			pCur = pCur->pNext;
		}
		if (NULL == pCur)	//没找到对应节点
		{
			printf("Don't find deleteNum.\n");
			return;
		}
		if (pCur == *ppTail)
		{
			*ppTail = pPre;
		}
	}
	free(pCur);
	pCur = NULL;
}

//链表的修改
void listModify(pStudent_t pHead, int num, float score)
{
	while (pHead)
	{
		if (pHead->num == num)
		{
			pHead->score = score;
			break;
		}
		pHead = pHead->pNext;
	}
	if (NULL == pHead)
	{
		printf("Don't find modify num.\n");
	}
}