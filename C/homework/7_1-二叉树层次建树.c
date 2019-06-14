/*��ɶ������Ĳ�ν���*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct BiTree	//���������ṹ
{
	char data;
	struct BiTree* left, * right;
}BiTree_t, * pBiTree_t;

typedef struct InsertQueue	//���븨�����нṹ
{
	pBiTree_t InsertLeaf;	//Ҫ�����Ҷ��
	struct InsertQueue* next;
}InsertQueue_t, * pInsertQueue_t;

void destroyQueue(pInsertQueue_t* toFront, pInsertQueue_t* toRear)//���ٶ���
{
	pInsertQueue_t pCur = *toFront;
	while (pCur)
	{
		*toFront = pCur->next;
		free(pCur);
		pCur = *toFront;
	}
	*toRear = NULL;
}

void MidOrder_OutputBiTree(pBiTree_t root)//����������
{
	if (root)
	{
		MidOrder_OutputBiTree(root->left);
		putchar(root->data);
		MidOrder_OutputBiTree(root->right);
	}
}

void InsertLeaf(pBiTree_t* toRoot, pInsertQueue_t* toFront, pInsertQueue_t* toRear, char NewData)//��ν���
{
	pBiTree_t pNew = (pBiTree_t)calloc(1, sizeof(BiTree_t));
	pInsertQueue_t qNew = (pInsertQueue_t)calloc(1, sizeof(InsertQueue_t));
	pInsertQueue_t qCur;
	pNew->data = NewData;
	qNew->InsertLeaf = pNew;
	if (NULL == *toRoot)
	{
		*toFront = qNew;
		*toRear = qNew;
		*toRoot = pNew;
	}
	else
	{
		(*toRear)->next = qNew;
		*toRear = qNew;
		if (NULL==((*toFront)->InsertLeaf)->left)
		{
			((*toFront)->InsertLeaf)->left = pNew;
		}
		else
		{
			((*toFront)->InsertLeaf)->right = pNew;
			qCur = *toFront;
			*toFront = qCur->next;
			free(qCur);
		}
	}
}

int main()
{
	char NewData;
	pBiTree_t root = NULL;
	pInsertQueue_t front = NULL, rear = NULL;
	while (scanf("%c", &NewData))
	{
		if ('\n' == NewData)
		{
			break;
		}
		InsertLeaf(&root, &front, &rear, NewData);
	}
	destroyQueue(&front, &rear);//�ÿո�������
	MidOrder_OutputBiTree(root);//��������������֤
	putchar('\n');
	system("pause");
}