/*完成二叉树的层次建树*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct BiTree	//二叉树结点结构
{
	char data;
	struct BiTree* left, * right;
}BiTree_t, * pBiTree_t;

typedef struct InsertQueue	//插入辅助队列结构
{
	pBiTree_t InsertLeaf;	//要插入的叶子
	struct InsertQueue* next;
}InsertQueue_t, * pInsertQueue_t;

void destroyQueue(pInsertQueue_t* toFront, pInsertQueue_t* toRear)//销毁队列
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

void MidOrder_OutputBiTree(pBiTree_t root)//中序遍历输出
{
	if (root)
	{
		MidOrder_OutputBiTree(root->left);
		putchar(root->data);
		MidOrder_OutputBiTree(root->right);
	}
}

void InsertLeaf(pBiTree_t* toRoot, pInsertQueue_t* toFront, pInsertQueue_t* toRear, char NewData)//层次建树
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
	destroyQueue(&front, &rear);//置空辅助队列
	MidOrder_OutputBiTree(root);//中序遍历输出以验证
	putchar('\n');
	system("pause");
}