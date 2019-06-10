#include "链表的增删改查-list.h"

int main()
{
	pStudent_t phead = NULL, ptail = NULL;
	int num;
	while (scanf("%d",&num)!=EOF)
	{
		//listHeadInsert(&phead,&ptail,num);
		//listTailInsert(&phead, &ptail, num);
		listSortInsert(&phead, &ptail, num);
	}
	listPrint(phead);
	system("pause");
}