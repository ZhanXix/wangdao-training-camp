/*
����һ������n��Ԫ�ص��������飬�ҳ������е�����Ԫ��x��yʹ��abs(x - y)ֵ��С
*/

#include <stdio.h>
#include <stdlib.h> 

//û�뵽�Ż�˼·��Ŀǰ��˼·��������Ȼ���ҵ�Ԫ��
int cmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}
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
		printf("����һ��%d������Ԫ�ص�����a:\n", len);
		for (int i = 0; i < len; ++i)
		{
			scanf("%d", &arr[i]);
		}
		//����
		qsort(arr, len, sizeof(int), cmp);
		//�ҵ�Ҫ�������Ԫ��x��y
		int result = abs(arr[0] - arr[1]);
		int x = arr[0];
		int y = arr[1];
		for (int i = 1; i < len-1; ++i)
		{
			if (abs(arr[i] - arr[i + 1]) < result)
			{
				result = abs(arr[i] - arr[i + 1]);
				x = arr[i];
				y = arr[i + 1];
			}
		}
		printf("�ҳ������е�����Ԫ��%d��%dʹ����������ľ���ֵ��С����СֵΪ:%d\n", x,y,result);
		//�ͷſռ�
		free(arr);
		arr = NULL;
		rewind(stdin);
		printf("\n��Ҫ����������y:");
	} while (getchar() == 'y');
	system("pause");
}