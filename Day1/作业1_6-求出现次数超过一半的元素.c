/*
����һ��n������Ԫ�ص�����a��������һ��Ԫ�س��ִ�������n / 2�������Ԫ�ء�
(xzע�����Ԫ��һ������)
*/

#include <stdio.h>
#include <stdlib.h> 

int main()
{
	int* arr = NULL;
	int len = 0;
	do
	{
		//��������
		printf("������������ĳ���:\n");
		scanf("%d", &len);
		arr = (int*)malloc(len * sizeof(int));
		printf("����һ��%d������Ԫ�ص�����a��������һ��Ԫ�س��ִ�������һ��:\n", len);
		for (int i = 0; i < len; ++i)
		{
			scanf("%d", &arr[i]);
		}
		//������ִ�������һ���Ԫ��
		int count = 1;	//������
		int lastNum = arr[0];	//��һ�������Ԫ��
		for (int i = 1; i < len; ++i) {
			if (arr[i] == lastNum)
			{
				++count;
			}
			else
			{
				--count;
				if (count < 0)
				{
					lastNum = arr[i];
					count = 1;
				}
			}
		}
		printf("���ִ�������һ���Ԫ��Ϊ %d\n", lastNum);
		//�ͷſռ�
		free(arr);
		arr = NULL;
		rewind(stdin);
		printf("\n��Ҫ����������y:");
	} while (getchar() == 'y');
	system("pause");
}

//��ѧ������ʹ�ü�������