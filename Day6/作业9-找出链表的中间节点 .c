/*找出链表的中间节点*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertTail(pLNode_t* toHead, pLNode_t* toTail, int newData)//尾插法
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

void print(pLNode_t pHead)//输出链表数据
{
	printf("当前链表为：\n");
	while (pHead)
	{
		printf("%d ", pHead->data);
		pHead = pHead->next;
	}
	putchar('\n');
}

int findMidNode(pLNode_t pHead, pLNode_t pTail)//找到链表的中间结点
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
		printf("链表的中间结点为 %d\n", pCur->next->data);
	}
	else
	{
		printf("链表的中间结点为 %d 和 %d\n", pCur->data,pCur->next->data);
	}
	return pCur->data;
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	printf("输入一组整数，以组成链表：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	findMidNode(pHead, pTail);//找到链表的中间结点
	system("pause");
}