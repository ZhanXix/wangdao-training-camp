/*
4.ɾ��һ���������ظ���Ԫ�ء����� 1,2,2,2,3,3,3,4,4,5,5,5,6,6,6 -> 1,2,3,4,5,6
(�����ظ����־�����)
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	int* arr;
	int lastNum, count, len;
	printf("������Ҫ��������鳤�ȣ�\n");
	while (scanf("%d", &len)!=EOF) {
		arr = (int*)malloc(4*len);
		printf("������Ҫ��������飺\n");
		for (int i = 0; i < len; ++i) {
			scanf("%d", arr+i);
		}
		lastNum = arr[0];//��һ�����������
		count = 0;//��ǰ��Ҫ��λ����Ŀ
		for (int i = 1; i < len; ++i)
		{
			if (arr[i] == lastNum)
			{
				count++;
			}
			else
			{
				arr[i - count] = arr[i];
				lastNum = arr[i];
			}
		}
		len -= count;
		arr = (int*)realloc(arr,4*len);//��С���鳤��
		printf("��������");
		for (int i = 0; i < len; ++i) {
			printf("%d ", *(arr + i));
		}
		free(arr);
		arr = NULL;
		printf("\n\n������Ҫ��������鳤��(0��ʾ��������)��\n");
	}
	system("pause");
}