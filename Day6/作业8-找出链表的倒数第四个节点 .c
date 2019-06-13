/*�ҳ�����ĵ������ĸ��ڵ� */

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

int findLNode(pLNode_t pHead, pLNode_t pTail, int n)//�ҳ�����ĵ�����n������
{
	pLNode_t pPre = pHead;
	pLNode_t pCur = pHead;
	int i;
	for (i = 0; i < n; ++i) {
		if (pCur)
		{
			pCur = pCur->next;
		}
		else
		{
			printf("���������Ȳ��㣡������Ҫ�ҵĽ�㡣\n");
			return;
		}
	}
	while (pCur)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	printf("����ĵ�����%d�����Ϊ %d\n", n, pPre->data);
	return pPre->data;
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
	findLNode(pHead, pTail, 4);
	system("pause");
}