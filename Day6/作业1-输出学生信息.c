/*
��һ��ѧ���ṹ�壬�����ݳ�Ա�У�ѧ�ţ�������3�ſγ̡�
�Ӽ���������5��ѧ������Ϣ��
Ҫ�������
(1) ����ѧ�ŵ������ȫ��ѧ����Ϣ��ÿ��ѧ������Ϣһ�С�(��ʽ�� ѧ�� ���� ���� 1 ���� 2 ���� 3 �ܷ�)
(2) ���ÿ�ſγ���߷ֵ�ѧ������Ϣ
(3) ���ÿ�ſγ̵�ƽ����
(4) �����ܷ����ѧ������
*/

#include <stdio.h> 
#include <stdlib.h> 

typedef struct student
{
	int id;
	char* name[20];
	float score[3];
	float total;
}Student_t, * pStudent_t;

int cmp1(const void* a, const void* b)
{
	return(*(pStudent_t)a).id > (*(pStudent_t)b).id ? 1 : -1;
}
int cmp2(const void* a, const void* b)
{
	return(*(pStudent_t)a).total > (*(pStudent_t)b).total? -1 : 1;
}
int main()
{
	Student_t s[5];
	pStudent_t p[5];
	int i, j;
	do
	{
		printf("����5��ѧ������Ϣ:\n");
		for (i = 0; i < 5; ++i)
		{
			scanf("%d%s%f%f%f", &s[i].id, s[i].name, &s[i].score[0], &s[i].score[1], &s[i].score[2]);
			s[i].total = s[i].score[0] + s[i].score[1] + s[i].score[2];
			p[i] = &s[i];
		}
		printf("--------------------------------------\n");
		printf("��ѧ�ŵ��������\n");
		qsort(*p, 5, sizeof(Student_t), cmp1);
		for (i = 0; i < 5; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", p[i]->id, p[i]->name, p[i]->score[0], p[i]->score[1], p[i]->score[2], p[i]->total);
		}
		printf("--------------------------------------\n");
		pStudent_t maxScore[3] = { &s[0],&s[0], &s[0] };
		for (i = 1; i < 5; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				if (s[i].score[j] > maxScore[j]->score[j])
				{
					maxScore[j] = &s[i];
				}
			}
		}
		printf("���Ʒ�����ߵ���λѧ���ֱ�Ϊ��\n");
		for (int i = 0; i < 3; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", maxScore[i]->id, maxScore[i]->name, maxScore[i]->score[0], maxScore[i]->score[1], maxScore[i]->score[2], maxScore[i]->total);
		}
		printf("--------------------------------------\n");
		float ave[3] = { 0 };
		for (i = 0; i < 5; ++i)
		{
			for (j = 0; j < 3; ++j)
			{
				ave[j] += s[i].score[j];
			}
		}
		printf("ÿ�ſγ̵�ƽ���ֱַ�Ϊ��%5.2f %5.2f %5.2f\n", ave[0] / 5, ave[1] / 5, ave[2] / 5);
		printf("--------------------------------------\n");
		printf("�����ܷ����ѧ��������\n");
		qsort(*p, 5, sizeof(Student_t), cmp2);
		for (i = 0; i < 5; ++i)
		{
			printf("%d\t%s\t%5.1f\t%5.1f\t%5.1f\t%5.1f\n", p[i]->id, p[i]->name, p[i]->score[0], p[i]->score[1], p[i]->score[2], p[i]->total);
		}
		rewind(stdin);
		printf("\nҪ������������y...");
	} while (getchar() == 'y');
	system("pause");
}