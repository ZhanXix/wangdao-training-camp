#include "�������ɾ�Ĳ�-list.h"

//����ͷ�巨
void listHeadInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));//1������ռ������
	//calloc���԰ѿռ�������������Ϊ0
	pNew->num = val;
	if (NULL == *ppHead)//�ж������Ƿ�Ϊ��
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

//�����ӡ
void listPrint(pStudent_t pHead)
{
	while (pHead != NULL)
	{
		printf("%3d", pHead->num);
		pHead = pHead->pNext;
	}
	putchar('\n');
}

//����β�巨
void listTailInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));
	pNew->num = val;
	if (NULL == *ppTail)//�ж������Ƿ�Ϊ��
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

//�����������
void listSortInsert(pStudent_t* ppHead, Student_t** ppTail, int val)
{
	pStudent_t pNew = (pStudent_t)calloc(1, sizeof(Student_t));
	pStudent_t pCur = *ppHead, pPre;
	pNew->num = val;
	if (NULL == *ppHead)//�ж������Ƿ�Ϊ��
	{
		*ppHead = pNew;
		*ppTail = pNew;
	}
	else if (val < pCur->num)//ͷ�巨
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
		if (NULL == pCur)//β�巨
		{
			pPre->pNext = pNew;
			*ppTail = pNew;
		}
	}
}