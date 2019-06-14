/*判断两个链表是否相交， 如果相交， 计算交点*/

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

void giveTailNext(pLNode_t pHead, pLNode_t pTail, int n)	//上一题此函数用于创造链表环，这一次用来创造交点
{
	int i;
	pLNode_t pCur = pHead;
	if (n == 0)
	{
		return;
	}
	for (i = 0; i < n - 1; ++i)
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

pLNode_t findRepeatNode(pLNode_t pHead1, pLNode_t pHead2)	//查找两个链表是否相交
{
	pLNode_t pCur1 = pHead1, pCur2 = pHead2;
	int len1 = 0, len2 = 0;
	int difflen, i;
	if (NULL==pCur1 || NULL==pCur2)
	{
		printf("这两个链表不相交！\n");
		return NULL;
	}
	while (pCur1->next)
	{
		len1++;
		pCur1 = pCur1->next;
	}
	while (pCur2->next)
	{
		len2++;
		pCur2 = pCur2->next;
	}
	if (pCur1 != pCur2)
	{
		printf("这两个链表不相交！\n");
		return NULL;
	}
	else
	{
		pCur1 = pHead1;
		pCur2 = pHead2;
		if (len1>len2)
		{
			for (i = 0; i < len1-len2; ++i)
			{
				pCur1 = pCur1->next;
			}
		}
		else
		{
			for (i = 0; i < len2 - len1; ++i)
			{
				pCur2 = pCur2->next;
			}
		}
		while (pCur1)
		{
			if(pCur1 == pCur2)
			{
				printf("这两个链表相交！交点为%d\n",pCur1->data);
				return pCur1;
			}
			pCur1 = pCur1->next;
			pCur2 = pCur2->next;
		}
	}
}

int main()
{
	pLNode_t pHead1 = NULL, pTail1 = NULL;
	pLNode_t pHead2 = NULL, pTail2 = NULL;
	int newData;
	int n;
	printf("输入一组整数，以组成链表一：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead1, &pTail1, newData);
	}
	print(pHead1);
	printf("输入一组整数，以组成链表二：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead2, &pTail2, newData);
	}
	printf("输入链表二尾的下一个结点是链表一中第几个结点（若为空，输入0）:\n"); //用于测试查找交点的效果
	scanf("%d", &n);
	giveTailNext(pHead1, pTail2, n);
	findRepeatNode(pHead1, pHead2);
	system("pause");
}