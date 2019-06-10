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
		printf("%3d", pHead->num);
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