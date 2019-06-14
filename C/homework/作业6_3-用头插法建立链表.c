/*用头插法建立链表*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertHead(pLNode_t* toHead, pLNode_t* toTail, int newData)
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
		insertHead(&pHead, &pTail, newData);
	}
	print(pHead);
	system("pause");
}