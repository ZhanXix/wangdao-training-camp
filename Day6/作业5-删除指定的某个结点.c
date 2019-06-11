/*删除指定的某个结点*/

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

void delLinkNode(pLNode_t* toHead, pLNode_t* toTail, int delData)
{
	pLNode_t pPer;
	pLNode_t pCur = *toHead;
	if (NULL == *toHead)
	{
		printf("错误：链表为空！\n");
		return;
	}
	if (*toHead == *toTail)	//链表只有一个结点
	{
		if ((*toHead)->data != delData)
		{
			printf("错误：没有匹配的数据！\n");
			return;
		}
		else
		{
			free(*toHead);
			*toHead = NULL;
			*toTail = NULL;
		}
	}
	else if ((*toHead)->data == delData)//链表头结点应该被删除
	{
		*toHead = (*toHead)->next;
		free(pCur);
	}
	else
	{

		while (pCur)
		{
			if (pCur->data == delData)
			{
				pPer->next = pCur->next;
				if (NULL == pCur->next)//删除尾结点
				{
					*toTail = pPer;
				}
				free(pCur);
				break;
			}
			else
			{
				pPer = pCur;
				pCur = pCur->next;
			}
		}
		if (NULL == pCur)
		{
			printf("错误：没有匹配的数据！\n");
			return;
		}
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
	while (printf("输入要删除的那个结点数据：\n"), scanf("%d", &delData) != EOF)
	{
		delLinkNode(&pHead, &pTail, delData);
		print(pHead);
	}
	system("pause");
}