#include <stdio.h> 
#include <stdlib.h> 
#include <time.h>

#define N 10
#define R 100
#define SWAP(a,b){int tmp;tmp=a;a=b;b=tmp;}//�꣬�Ⱥ���Ч���Ըߣ������ظ�����

//windows�µ���������ջ�ռ�ֻ��1M

void arrPrint(int* arr);
void arrSelect(int* arr);
void arrInsert(int* arr);
void arrShell(int* arr);
void arrQuick(int* arr, int left, int right);
void arrHeap(int* arr);
void arrCount(int* arr);
