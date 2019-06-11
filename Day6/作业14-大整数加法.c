/*
�������ӷ���
������������������������ֵ���ܳ���һ�����ͱ������ܱ�ʾ�ķ�Χ���� �ӷ���
*/

//��ǰ�������⣬��ʱ�õ����������洢���ݣ�����ʹ������
#include <stdio.h> 
#include <stdlib.h> 

typedef struct LNode
{
	int data;
	struct LNode* next;
}LNode_t, * pLNode_t;

void insertHead(pLNode_t* toHead, pLNode_t* toTail, int newData)//ͷ�巨
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

void print(pLNode_t pHead)//�����������,����ǰ�õĺ�������������޸�
{
	//printf("��ǰ����Ϊ��\n");
	while (pHead)
	{
		printf("%d", pHead->data);
		pHead = pHead->next;
	}
	putchar('\n');
}

void reverseLinkList(pLNode_t* toHead, pLNode_t* toTail)//��������
{
	pLNode_t pPre, pCur, pNext;
	if (*toHead == *toTail)//����ֻ��һ����������Ϊ��
	{
		return;
	}
	if ((*toHead)->next == *toTail)//����ֻ���������
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
		pCur->next = pPre;	//���ý��ָ��
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
		printf("�����������\n");
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
	if (addFlag)	//��Ҫ�����λ
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
	printf("�����������������Իس�������\n");
	while (scanf("%c", &newNum))//ͷ�巨��������һ
	{
		if ('\n' == newNum)
		{
			break;
		}
		newData = (int)(newNum - '0');
		insertHead(&pHead1, &pTail1, newData);
	}
	while (scanf("%c", &newNum))//ͷ�巨���������
	{
		if ('\n' == newNum)
		{
			break;
		}
		newData = (int)(newNum - '0');
		insertHead(&pHead2, &pTail2, newData);
	}
	printf("���������...\n");
	addLinkListNum(pHead1, &pTail1, pHead2, &pTail2);
	reverseLinkList(&pHead1, &pHead2);//��������
	print(pHead1);
	system("pause");
}
