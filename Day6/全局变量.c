#include <stdio.h> 
#include <stdlib.h> 

int k = 0;//ȫ�ֱ���
void print()
{
	k++;
	printf("I am print k = %d\n", k);
}
//ȫ�ֱ����Ķ��Ѷ�����
int main()
{
	int i = 5;//�ͽ�ԭ��
	printf("I am main i = %d\n", i);
	print();
	print();
	system("pause");
}
