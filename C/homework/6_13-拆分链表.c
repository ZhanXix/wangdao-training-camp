/*
��һ�������֣�����������λ���ϵĽڵ㹹��һ������ż��λ���ϵĽڵ㹹����һ ������ 
���磺
	L��1 -> 2 -> 3 ->4 ->5 ->6 ->7 ->8 ->9 -> NULL 
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

void insertTail(pLNode_t* toHead, pLNode_t* toTail, int newData)//β�巨
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

void print(pLNode_t pHead)//�����������
{
	printf("��ǰ����Ϊ��\n");
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
	if (NULL == pCur1)//����Ϊ��
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
	//���ϣ�������ǰ�������.pCur1��pCur2�ֱ�ָ�������������ͷ���,pCurָ��δ�����������
	while (pCur)
	{
		pCur = pCur->next;
		if (i % 2 == 0)	//�������
		{
			pCur1->next = pPre;
			pCur1 = pCur1->next;
		}
		else//ż�����
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
	printf("����һ�����������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead1, &pTail1, newData);
	}
	print(pHead1);
	printf("�������...\n");
	devideLinkList(pHead1, &pTail1, &pHead2, &pTail2);
	print(pHead1);
	print(pHead2);
	system("pause");
}

