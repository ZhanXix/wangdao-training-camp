/*判断单链表是否有环*/

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

void giveTailNext(pLNode_t pHead, pLNode_t pTail, int n)	//创造链表环
{
	int i;
	pLNode_t pCur = pHead;
	if (n == 0)
	{
		return;
	}
	for (i = 0; i < n-1; ++i)
	{
		if (pCur)
		{
			pCur = pCur->next;
		}
		else
		{
			printf("输入错误，没有这个结点！\n");
			return;
		}
	}
	pTail->next = pCur;
}

pLNode_t findLinkListCircle(pLNode_t pHead)	//判断单链表是否有环
{
	pLNode_t pShort = pHead, pLong = pHead;
	while (pLong && pLong->next)
	{
		pShort = pShort->next;
		pLong = pLong->next->next;
		if (pShort == pLong)
		{
			printf("该链表有环！\n");
			return pLong;
		}
	}
	printf("该链表无环！\n");
	return NULL;
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	int n;
	printf("输入一组整数，以组成链表：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	printf("输入链表尾的下一个结点是链表中第几个结点（若为空，输入0）:\n");//用于测试查找链表环的效果
	scanf("%d", &n);
	giveTailNext(pHead, pTail, n);
	findLinkListCircle(pHead);
	system("pause");
}