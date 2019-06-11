/*
��һ���������á� �磺 1->2 ->3 ->4 ->5 ->NULL�� ���: 5 -> 4 -> 3 ->2 ->1 -> NULL
*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertTail(pLNode_t* toHead, pLNode_t* toTail, int newData)//β�巨
{
	pLNode_t pNew;
	pNew = (pLNode_t)calloc(1, sizeof(LNode_t));
	pNew->data = newData;
	if (*toHead == NULL)
	{
		*toHead = pNew;
		*toTail = pNew;
	}
	else
	{
		(*toTail)->next = pNew;
		*toTail = pNew;
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

void reverseLinkList(pLNode_t* toHead, pLNode_t* toTail)//��������
{
	pLNode_t pPre, pCur, pNext;
	if (*toHead == *toTail)//����ֻ��һ����������Ϊ��
	{
		return;
	}
	if ((*toHead)->next == *toTail)//����ֻ���������
	{
		(*toHead)->next = NULL;
		(*toTail)->next = *toHead;
		*toHead = *toTail;
		*toTail = (*toHead)->next;
		return;
	}
	pPre = *toHead;
	pCur = (*toHead)->next;
	pPre->next = NULL;
	pNext = pCur->next;
	while (pCur)
	{
		pCur->next = pPre;	//���ý��ָ��
		pPre = pCur;
		pCur = pNext;
		if (pNext)
		{
			pNext = pNext->next;
		}
	}
	*toTail = *toHead;
	*toHead = pPre;
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	int delData;
	printf("����һ�����������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	printf("��������...\n");
	reverseLinkList(&pHead, &pTail);
	print(pHead);
	system("pause");
}