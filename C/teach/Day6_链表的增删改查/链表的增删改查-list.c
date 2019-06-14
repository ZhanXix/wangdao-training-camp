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
		printf("%3d %5.2f\n", pHead->num, pHead->score);
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

//�����ɾ��
void listDelete(pStudent_t* ppHead, Student_t** ppTail, int deleteNum)
{
	pStudent_t pCur = *ppHead;
	pStudent_t pPre = pCur;
	if (NULL == pCur)
	{
		printf("List is empty.\n");
	}
	else if (deleteNum == pCur->num)//ɾ������ͷ��
	{
		*ppHead = pCur->pNext;
		if (NULL == *ppHead)
		{
			*ppTail = NULL;
		}
	}
	else
	{
		while (pCur)	//ɾ�������м��β��
		{
			if (deleteNum == pCur->num)
			{
				pPre->pNext = pCur->pNext;
				break;
			}
			pPre = pCur;
			pCur = pCur->pNext;
		}
		if (NULL == pCur)	//û�ҵ���Ӧ�ڵ�
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

//������޸�
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