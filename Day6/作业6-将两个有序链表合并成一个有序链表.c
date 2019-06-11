/*
��������������ϲ���һ����������
*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertOrder(pLNode_t* toHead, pLNode_t* toTail, int newData)//�������
{
	pLNode_t pNew;
	pNew = (pLNode_t)calloc(1, sizeof(LNode_t));
	pNew->data = newData;
	if (*toHead == NULL)
	{
		*toHead = pNew;
		*toTail = pNew;
	}
	else if ((*toHead)->data > newData)
	{
		pNew->next = *toHead;
		*toHead = pNew;
	}
	else if ((*toTail)->data <= newData)
	{
		(*toTail)->next = pNew;
		*toTail = pNew;
	}
	else
	{
		pLNode_t pCur = *toHead;
		pLNode_t pPer;
		while (pCur)
		{
			if (pCur->data > newData)
			{
				pPer->next = pNew;
				pNew->next = pCur;
				break;
			}
			pPer = pCur;
			pCur = pCur->next;
		}
	}
}

void print(pLNode_t pHead)//�����������
{
	printf("��ǰ����Ϊ��\n");
	while (pHead)
	{
		printf("%d ", pHead->data);
		pHead = pHead->next;
	}
	putchar('\n');
}

void merge(pLNode_t* toHead1, pLNode_t* toTail1, pLNode_t* toHead2, pLNode_t* toTail2)//������2�ϲ�������1��
{
	pLNode_t pCur1 = *toHead1, pCur2 = *toHead2;
	pLNode_t pPer1 = NULL, pPer2 = NULL;
	if (pCur2->data < pCur1->data)	//������2С������1��һ�������ȷŵ�����1ǰ��
	{
		while (pCur2->data < pCur1->data)
		{
			pPer2 = pCur2;
			pCur2 = pCur2->next;
		}
		pPer2->next = pCur1;
		*toHead1 = *toHead2;
	}
	while (pCur1 && pCur2)
	{
		while (pCur1 && pCur1->data < pCur2->data)
		{
			pPer1 = pCur1;
			pCur1 = pCur1->next;
		}
		if (pCur1 == NULL)
		{
			break;
		}
		pPer1->next = pCur2;
		pPer1 = pPer1->next;
		pCur2 = pCur2->next;
		pPer1->next = pCur1;
	}
	if (pCur2)
	{
		(*toTail1)->next = pCur2;
		*toTail1 = *toTail2;
	}
	*toHead2 = NULL;
	*toTail2 = NULL;
}

int main()
{
	pLNode_t pHead1 = NULL, pTail1 = NULL, pHead2 = NULL, pTail2 = NULL;
	int newData;
	int delData;
	printf("����һ������������ɵ�һ������\n");
	while (scanf("%d", &newData) != EOF)//������뷨��������1
	{
		insertOrder(&pHead1, &pTail1, newData);
	}
	print(pHead1);
	printf("����һ������������ɵڶ�������\n");
	while (scanf("%d", &newData) != EOF)//����������2
	{
		insertOrder(&pHead2, &pTail2, newData);
	}
	print(pHead2);
	printf("��������������ϲ���һ����������...\n");
	merge(&pHead1, &pTail1, &pHead2, &pTail2);
	print(pHead1);
	system("pause");
}