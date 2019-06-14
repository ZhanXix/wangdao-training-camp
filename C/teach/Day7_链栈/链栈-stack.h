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
void pop(pStack_t stack);  //出栈  
void push(pStack_t stack, int val); //入栈 
int top(pStack_t stack);   //返回栈顶元素  
int empty(pStack_t stack);  //判断栈是否为空  
int size(pStack_t stack);  //返回栈中数据的元素个数 