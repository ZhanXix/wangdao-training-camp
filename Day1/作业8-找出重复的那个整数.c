/*
��������1001��Ԫ�ص����飬���д����1 - 1000֮�ڵ�������ֻ��һ���������ظ��ģ����ҳ������
��ʾ�� A1 + �� + A1001 �C(1 + �� + 1000)
*/

#include <stdio.h>
#include <stdlib.h> 

int main()
{
	int arr[1001];
	int result = 0;
	for (int i = 0; i < 1001; ++i)
	{//��������
		if (i == 555)
		{
			arr[i] = 999;	//�ظ�����
		}
		else if (i < 555)
		{
			arr[i] = i + 1;
		}
		else
		{
			arr[i] = i;
		}
	}
	//�ҳ��ظ�����
	for (int i = 0; i < 1001; ++i) {
		result = result + arr[i] - i;
	}
	printf("�������ظ����Ǹ�����Ϊ:%d\n",  result);
	system("pause");
}
