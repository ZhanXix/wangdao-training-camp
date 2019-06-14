#include "层次建立二叉树-tree.h"

#define N 10
int main()
{
	Elemtype val;
	pNode_t treeRoot = NULL;
	pQueue_t queHead = NULL, queTail = NULL;
	while (scanf("%c", &val) != EOF)
	{
		if ('\n' == val)
		{
			break;
		}
		buildBinaryTree(&treeRoot, &queHead, &queTail, val);
	}
	destroyQueue(&queHead, &queTail);
	preOrder(treeRoot);
	putchar('\n');
	midOrder(treeRoot);
	putchar('\n');
	lastOrder(treeRoot);
	putchar('\n');
	system("pause");
}
