#include <stdio.h> 
#include <stdlib.h> 

typedef struct tag
{
	int val;
	struct tag* pNext;
}Node_t, * pNode_t;

typedef struct
{
	pNode_t phead;
	int size;
}Stack_t, * pStack_t;

void initStack(pStack_t stack);
void pop(pStack_t stack);  //��ջ  
void push(pStack_t stack, int val); //��ջ 
int top(pStack_t stack);   //����ջ��Ԫ��  
int empty(pStack_t stack);  //�ж�ջ�Ƿ�Ϊ��  
int size(pStack_t stack);  //����ջ�����ݵ�Ԫ�ظ��� 