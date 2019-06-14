#include "层次建立二叉树-tree.h"

//前序遍历
void preOrder(pNode_t root)
{
	if (root)
	{
		putchar(root->c);
		preOrder(root->pleft);
		preOrder(root->pright);
	}
}

//中序遍历
void midOrder(pNode_t root)
{
	if (root)
	{
		midOrder(root->pleft);
		putchar(root->c);
		midOrder(root->pright);
	}
}

//后序遍历
void lastOrder(pNode_t root)
{
	if (root)
	{
		lastOrder(root->pleft);
		lastOrder(root->pright);
		putchar(root->c);
	}
}

//层次建树
void buildBinaryTree(pNode_t* treeRoot, pQueue_t* queHead, pQueue_t* queTail, Elemtype val)
{
	pNode_t treeNew = (pNode_t)calloc(1, sizeof(Node_t));
	pQueue_t queNew = (pQueue_t)calloc(1, sizeof(Queue_t));
	pQueue_t queCur = *queHead;
	treeNew->c = val;
	queNew->insertPos = treeNew;
	if (NULL == *treeRoot)
	{
		*treeRoot = treeNew;
		*queHead = queNew;
		*queTail = queNew;
	}
	else
	{
		//插入队列
		(*queTail)->pNext = queNew;
		*queTail = queNew;
		//插入树
		if (NULL == queCur->insertPos->pleft)
		{
			queCur->insertPos->pleft = treeNew;
		}
		else if (NULL == queCur->insertPos->pright)
		{
			queCur->insertPos->pright = treeNew;
			*queHead = queCur->pNext;
			free(queCur);
			queCur = NULL;
		}
	}
}

//销毁队列
void destroyQueue(pQueue_t* queHead, pQueue_t* queTail)
{
	pQueue_t pCur = *queHead;
	while (pCur)
	{
		*queHead = pCur->pNext;
		free(pCur);
		pCur = *queHead;
	}
	*queTail = NULL;
}