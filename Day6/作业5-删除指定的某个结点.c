/*ɾ��ָ����ĳ�����*/

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

void delLinkNode(pLNode_t* toHead, pLNode_t* toTail, int delData)
{
	pLNode_t pPer;
	pLNode_t pCur = *toHead;
	if (NULL == *toHead)
	{
		printf("��������Ϊ�գ�\n");
		return;
	}
	if (*toHead == *toTail)	//����ֻ��һ�����
	{
		if ((*toHead)->data != delData)
		{
			printf("����û��ƥ������ݣ�\n");
			return;
		}
		else
		{
			free(*toHead);
			*toHead = NULL;
			*toTail = NULL;
		}
	}
	else if ((*toHead)->data == delData)//����ͷ���Ӧ�ñ�ɾ��
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
				if (NULL == pCur->next)//ɾ��β���
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
			printf("����û��ƥ������ݣ�\n");
			return;
		}
	}
}

int main()
{
	pLNode_t pHead = NULL, pTail = NULL;
	int newData;
	int delData;
	printf("����һ�����������������\n");
	while (scanf("%d", &newData) != EOF)//β�巨��������
	{
		insertTail(&pHead, &pTail, newData);
	}
	print(pHead);
	while (printf("����Ҫɾ�����Ǹ�������ݣ�\n"), scanf("%d", &delData) != EOF)
	{
		delLinkNode(&pHead, &pTail, delData);
		print(pHead);
	}
	system("pause");
}