/*找出链表的倒数第四个节点 */

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

int findLNode(pLNode_t pHead, pLNode_t pTail, int n)//找出链表的倒数第n个数据
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
			printf("错误：链表长度不足！不存在要找的结点。\n");
			return;
		}
	}
	while (pCur)
	{
		pPre = pPre->next;
		pCur = pCur->next;
	}
	printf("链表的倒数第%d个结点为 %d\n", n, pPre->data);
	return pPre->data;
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
	findLNode(pHead, pTail, 4);
	system("pause");
}