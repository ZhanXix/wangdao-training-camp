/*�жϵ������Ƿ��л�*/

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

void giveTailNext(pLNode_t pHead, pLNode_t pTail, int n)	//��������
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
			printf("�������û�������㣡\n");
			return;
		}
	}
	pTail->next = pCur;
}

pLNode_t findLinkListCircle(pLNode_t pHead)	//�жϵ������Ƿ��л�
{
	pLNode_t pShort = pHead, pLong = pHead;
	while (pLong && pLong->next)
	{
		pShort = pShort->next;
		pLong = pLong->next->next;
		if (pShort == pLong)
		{
			printf("�������л���\n");
			return pLong;
		}
	}
	printf("�������޻���\n");
	return NULL;
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	int n;
	printf("����һ�����������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	printf("��������β����һ������������еڼ�����㣨��Ϊ�գ�����0��:\n");//���ڲ��Բ���������Ч��
	scanf("%d", &n);
	giveTailNext(pHead, pTail, n);
	findLinkListCircle(pHead);
	system("pause");
}