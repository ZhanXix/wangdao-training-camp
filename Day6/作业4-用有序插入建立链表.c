/*用有序插入建立链表*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertOrder(pLNode_t* toHead, pLNode_t* toTail, int newData)
{
	pLNode_t pNew;
	pNew = (pLNode_t)calloc(1, sizeof(LNode_t));
	pNew->data = newData;
	if (*toHead == NULL)
	{
		*toHead = pNew;
		*toTail = pNew;
	}
	else if ((*toHead)->data > newData)
	{
		pNew->next = *toHead;
		*toHead = pNew;
	}
	else if ((*toTail)->data <= newData)
	{
		(*toTail)->next = pNew;
		*toTail = pNew;
	}
	else
	{
		pLNode_t pCur = *toHead;
		pLNode_t pPer;
		while (pCur)
		{
			if (pCur->data > newData)
			{
				pPer->next = pNew;
				pNew->next = pCur;
				break;
			}
			pPer = pCur;
			pCur = pCur->next;
		}
	}
}
void print(pLNode_t pHead)
{
	while (pHead)
	{
		printf("%d ", pHead->data);
		pHead = pHead->next;
	}
	putchar('\n');
}
int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	while (scanf("%d", &newData) != EOF)
	{
		insertOrder(&pHead, &pTail, newData);
	}
	print(pHead);
	system("pause");
}