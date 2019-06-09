/*
��103��������������50�������������Σ�3����������һ�Σ� �ҳ�������һ�ε���3������
*/

#include <stdio.h> 
#include <stdlib.h> 

int findTwo(int a[], int len, int heap1, int* find2, int* find3)
{
	int x = 0;
	for (int i = 0; i < len; ++i) {
		if (a[i] != heap1)
		{
			x ^= a[i];
		}
	}	//�õ���������ͬ�����������
	int y = x & -x;	//���λΪ1���Ǹ���
	//�ֳ����ѣ��ֱ���������
	for (int i = 0; i < len; ++i) {
		if (a[i] ^ heap1) {	//ȷ��a[i]���ǵ�һ�����ҳ����Ǹ���
			if (a[i] & y) {
				*find2 ^= a[i];
			}
			else {
				*find3 ^= a[i];
			}
		}
	}
}
#define N 9
int main()
{
	int a[N] = { 2,3,2,4,4,5,6,7,6 };
	int x1 = 0, x2 = 0, x3 = 0;	//���
	int heap1 = 0, heap2 = 0;	//���ѵĽ��
	int count1 = 0, count2 = 0;	//���ѵ�Ԫ����Ŀ
	int split = 1;	//���ڷָ�����
	for (int i = 0; i < 32; ++i)
	{
		split = split << 1;	//ÿ�ν�split����һλ
		for (int j = 0; j < N; ++j)
		{
			if (a[j] & split)
			{
				heap1 ^= a[j];
				++count1;
			}
			else
			{
				heap2 ^= a[j];
				++count2;
			}
		}
		if (count2 % 2 && heap1 != 0)
		{
			x1 = heap2;
			findTwo(a, N, heap2, &x2, &x3);
			break;
		}
		else if (count1 % 2 && heap2 != 0)
		{
			x1 = heap1;
			findTwo(a, N, heap1, &x2, &x3);
			break;
		}
	}
	printf("������һ�ε���������Ϊ:%d %d %d\n", x1, x2, x3);
	system("pause");
}