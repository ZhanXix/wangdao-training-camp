/*
将一个链表拆分（将链表奇数位置上的节点构成一个链表，偶数位置上的节点构成另一 个链表） 
例如：
	L：1 -> 2 -> 3 ->4 ->5 ->6 ->7 ->8 ->9 -> NULL 
	L1: 1 ->3 ->5 ->7 ->9 -> NULL ; 
	L2: 2 ->4 ->6 ->8 -> NULL
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

void devideLinkList(pLNode_t pHead1, pLNode_t* toTail1, pLNode_t* toHead2, pLNode_t* toTail2)
{
	pLNode_t pCur1 = pHead1, pCur2;
	pLNode_t pCur, pPre;
	int i = 0;
	if (NULL == pCur1)//链表为空
	{
		return;
	}
	pCur2 = pCur1->next;
	*toHead2 = pCur2;
	if (pCur2->next)
	{
		pCur = pCur2->next;
		pPre = pCur;
	}
	//以上，处理完前两个结点.pCur1和pCur2分别指向两个新链表的头结点,pCur指向未处理的链表结点
	while (pCur)
	{
		pCur = pCur->next;
		if (i % 2 == 0)	//奇数结点
		{
			pCur1->next = pPre;
			pCur1 = pCur1->next;
		}
		else//偶数结点
		{
			pCur2->next = pPre;
			pCur2 = pCur2->next;
		}
		pPre = pCur;
		++i;
	}
	pCur1->next = NULL;
	*toTail1 = pCur1;
	pCur2->next = NULL;
	*toTail2 = pCur2;
}

int main()
{
	pLNode_t pHead1 = NULL, pTail1 = NULL;
	pLNode_t pHead2 = NULL, pTail2 = NULL;
	int newData;
	printf("输入一组整数，以组成链表：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead1, &pTail1, newData);
	}
	print(pHead1);
	printf("拆分链表...\n");
	devideLinkList(pHead1, &pTail1, &pHead2, &pTail2);
	print(pHead1);
	print(pHead2);
	system("pause");
}

