/*�ҳ�������м�ڵ�*/

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

int findMidNode(pLNode_t pHead, pLNode_t pTail)//�ҵ�������м���
{
	int len = 0, i;
	pLNode_t pCur = pHead;
	while (pCur)
	{
		len++;
		pCur = pCur->next;
	}
	pCur = pHead;
	for (i = 0; i < len / 2 - 1; i++)
	{
		pCur = pCur->next;
	}
	if (len % 2)
	{
		printf("������м���Ϊ %d\n", pCur->next->data);
	}
	else
	{
		printf("������м���Ϊ %d �� %d\n", pCur->data,pCur->next->data);
	}
	return pCur->data;
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	printf("����һ�����������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	findMidNode(pHead, pTail);//�ҵ�������м���
	system("pause");
}