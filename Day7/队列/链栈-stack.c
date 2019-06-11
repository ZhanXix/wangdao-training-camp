#include "��ջ-stack.h"

//��ʼ��
void initStack(pStack_t stack)
{
	memset(stack, 0, sizeof(Stack_t));
}

//��ջ  
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

//��ջ 
void push(pStack_t stack, int val)
{
	pNode_t pNew = (pNode_t)calloc(1, sizeof(Node_t));
	pNew->val = val;
	pNew->pNext = stack->phead;
	stack->phead = pNew;
	stack->size++;
}

//����ջ��Ԫ��  
int top(pStack_t stack)   
{
	if (!stack->size)
	{
		printf("stack is empty\n");
		return -1;
	}
	return stack->phead->val;
}

//�ж�ջ�Ƿ�Ϊ�� 
int empty(pStack_t stack)   
{
	return (!stack->size);
}

int size(pStack_t stack)  //����ջ�����ݵ�Ԫ�ظ��� 
{
	return stack->size;
}