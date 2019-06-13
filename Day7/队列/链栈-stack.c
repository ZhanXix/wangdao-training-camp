#include "链栈-stack.h"

//初始化
void initStack(pStack_t stack)
{
	memset(stack, 0, sizeof(Stack_t));
}

//出栈  
void pop(pStack_t stack)
{
	pNode_t pCur = stack->phead;
	if (!stack->size)
	{
		printf("stack is empty\n");
		return;
	}
	stack->phead = stack->phead->pNext;
	stack->size--;
	free(pCur);
	pCur = NULL;
}

//入栈 
void push(pStack_t stack, int val)
{
	pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
	pNew->val = val;
	pNew->pNext = stack->phead;
	stack->phead = pNew;
	stack->size++;
}

//返回栈顶元素  
int top(pStack_t stack)   
{
	if (!stack->size)
	{
		printf("stack is empty\n");
		return -1;
	}
	return stack->phead->val;
}

//判断栈是否为空 
int empty(pStack_t stack)   
{
	return (!stack->size);
}

int size(pStack_t stack)  //返回栈中数据的元素个数 
{
	return stack->size;
}