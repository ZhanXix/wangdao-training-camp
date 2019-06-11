/*删除单链表中重复的元素*/

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

void delRepeatLinkNode(pLNode_t pHead, pLNode_t* toTail)//删除链表中重复的元素
{
	pLNode_t pUndone = pHead;
	pLNode_t pPre, pCur;
	if (NULL == pUndone) //链表为空时
	{
		return;
	}
	while (pUndone)//链表不为空时
	{
		pPre = pUndone;
		pCur = pUndone->next;
		while (pCur)
		{
			if (pCur->data == pUndone->data)
			{
				if (pCur == *toTail)//删除的是尾结点
				{
					*toTail = pPre;
				}
				pPre->next = pCur->next;
				free(pCur);
				pCur = pPre->next;
			}
			else
			{
				pPre = pCur;
				pCur = pCur->next;
			}
		}
		pUndone = pUndone->next;
	}
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	int delData;
	printf("输入一组整数，以组成链表：\n");
	while (scanf("%d", &newData) != EOF)//尾插法建立链表
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	delRepeatLinkNode(pHead, &pTail);//删除重复元素
	print(pHead);
	system("pause");
}
