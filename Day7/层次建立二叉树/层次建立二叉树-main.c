#include "��ν���������-tree.h"

#define N 10
int main()
{
	Elemtype c[] = "ABCDEFGHIJ";
	pNode_t p[N];
	int i, j = 0;
	for (i = 0; i < N; ++i)
	{
		p[i] = (pNode_t)calloc(1, sizeof(Node_t));
		p[i]->c = c[i];
	}
	for (i = 1; i < N; i++)//������Ҫ������Ԫ��
	{
		if (NULL == p[j]->pleft)//�ڴ�Ƚ���Ԫ��
		{
			p[j]->pleft = p[i];
		}
		else if (NULL == p[j]->pright)
		{
			p[j]->pright = p[i];
			j++;
		}
	}
	preOrder(p[0]);
	putchar('\n');
	midOrder(p[0]);
	putchar('\n');
	lastOrder(p[0]);
	putchar('\n');
	system("pause");
}