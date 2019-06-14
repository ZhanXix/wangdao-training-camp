/*�ж����������Ƿ��ཻ�� ����ཻ�� ���㽻��*/

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

void giveTailNext(pLNode_t pHead, pLNode_t pTail, int n)	//��һ��˺������ڴ�����������һ���������콻��
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
			printf("�������û�������㣡\n");
			return;
		}
	}
	pTail->next = pCur;
}

pLNode_t findRepeatNode(pLNode_t pHead1, pLNode_t pHead2)	//�������������Ƿ��ཻ
{
	pLNode_t pCur1 = pHead1, pCur2 = pHead2;
	int len1 = 0, len2 = 0;
	int difflen, i;
	if (NULL==pCur1 || NULL==pCur2)
	{
		printf("�����������ཻ��\n");
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
		printf("�����������ཻ��\n");
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
				printf("�����������ཻ������Ϊ%d\n",pCur1->data);
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
	printf("����һ�����������������һ��\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead1, &pTail1, newData);
	}
	print(pHead1);
	printf("����һ��������������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead2, &pTail2, newData);
	}
	printf("���������β����һ�����������һ�еڼ�����㣨��Ϊ�գ�����0��:\n"); //���ڲ��Բ��ҽ����Ч��
	scanf("%d", &n);
	giveTailNext(pHead1, pTail2, n);
	findRepeatNode(pHead1, pHead2);
	system("pause");
}