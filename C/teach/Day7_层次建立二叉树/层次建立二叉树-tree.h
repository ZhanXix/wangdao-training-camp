#include <stdio.h>
#include <stdlib.h>

typedef char Elemtype;

typedef struct node_t
{
	Elemtype c;
	struct node_t* pleft;
	struct node_t* pright;
}Node_t,*pNode_t;

typedef struct queue_t
{
	pNode_t insertPos;
	struct queue_t* pNext;
}Queue_t,*pQueue_t;

void preOrder(pNode_t root);
void midOrder(pNode_t root);
void lastOrder(pNode_t root);
void buildBinaryTree(pNode_t* treeRoot, pQueue_t* queHead, pQueue_t* queTail, Elemtype val);
void destroyQueue(pQueue_t* queHead, pQueue_t* queTail);