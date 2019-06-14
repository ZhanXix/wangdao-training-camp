/*
将一个链表逆置。 如： 1->2 ->3 ->4 ->5 ->NULL， 输出: 5 -> 4 -> 3 ->2 ->1 -> NULL
*/

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

void reverseLinkList(pLNode_t* toHead, pLNode_t* toTail)//逆置链表
{
	pLNode_t pPre, pCur, pNext;
	if (*toHead == *toTail)//链表只有一个结点或链表为空
	{
		return;
	}
	if ((*toHead)->next == *toTail)//链表只有两个结点
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
		pCur->next = pPre;	//逆置结点指向
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
	printf("输入一组整数，以组成链表：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	printf("逆置链表...\n");
	reverseLinkList(&pHead, &pTail);
	print(pHead);
	system("pause");
}
