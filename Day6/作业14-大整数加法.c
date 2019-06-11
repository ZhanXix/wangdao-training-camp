/*
大整数加法。
（计算两个整数（该整数的值可能超过一个整型变量所能表示的范围）的 加法）
*/

//以前做过这题，当时用的是数组来存储数据，现在使用链表
#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertHead(pLNode_t* toHead, pLNode_t* toTail, int newData)//头插法
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
		pNew->next = *toHead;
		*toHead = pNew;
	}
}

void print(pLNode_t pHead)//输出链表数据,和以前用的函数相比有少许修改
{
	//printf("当前链表为：\n");
	while (pHead)
	{
		printf("%d", pHead->data);
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

void addLinkListNum(pLNode_t pHead1, pLNode_t* toTail1, pLNode_t pHead2, pLNode_t* toTail2)
{
	pLNode_t pCur1 = pHead1, pCur2 = pHead2;
	pLNode_t pPre1, pPre2;
	int addFlag = 0;
	if (NULL == pCur1 || NULL == pCur2)
	{
		printf("数据输入错误！\n");
		return;
	}
	while (pCur1 && pCur2)
	{
		pCur1->data += pCur2->data + addFlag;
		if (pCur1->data > 9)
		{
			pCur1->data -= 10;
			addFlag = 1;
		}
		else
		{
			addFlag = 0;
		}
		pPre1 = pCur1;
		pCur1 = pCur1->next;
		pPre2 = pCur2;
		pCur2 = pCur2->next;
	}
	while (pCur1)
	{
		pCur1->data += addFlag;
		if (pCur1->data > 9 && pCur1->next)
		{
			pCur1->data -= 10;
			addFlag = 1;
		}
		else
		{
			addFlag = 0;
			break;
		}
		pCur1 = pCur1->next;
	}
	if (pCur2)
	{
		pPre1->next = pCur2;
		*toTail1 = *toTail2;
		*toTail2 = pPre2;
		pPre2->next = NULL;
		while (pCur2)
		{
			pCur2->data += addFlag;
			if (pCur2->data > 9 && pCur2->next)
			{
				pCur2->data -= 10;
				addFlag = 1;
			}
			else
			{
				addFlag = 0;
				break;
			}
			pCur2 = pCur2->next;
		}
	}
	if (addFlag)	//需要额外进位
	{
		pPre1->data += 10;
	}
}

int main()
{
	pLNode_t pHead1 = NULL, pTail1 = NULL;
	pLNode_t pHead2 = NULL, pTail2 = NULL;
	char newNum;
	int newData;
	printf("输入两个大整数，以回车结束：\n");
	while (scanf("%c", &newNum))//头插法建立链表一
	{
		if ('\n' == newNum)
		{
			break;
		}
		newData = (int)(newNum - '0');
		insertHead(&pHead1, &pTail1, newData);
	}
	while (scanf("%c", &newNum))//头插法建立链表二
	{
		if ('\n' == newNum)
		{
			break;
		}
		newData = (int)(newNum - '0');
		insertHead(&pHead2, &pTail2, newData);
	}
	printf("大整数相加...\n");
	addLinkListNum(pHead1, &pTail1, pHead2, &pTail2);
	reverseLinkList(&pHead1, &pHead2);//逆置链表
	print(pHead1);
	system("pause");
}
