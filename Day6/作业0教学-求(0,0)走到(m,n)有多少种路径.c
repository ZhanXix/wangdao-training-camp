#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
	int x, y;
}node;

int cnt;
node nd[100];	//存储路径
int ff(int a, int b, int x, int y, int step)
{
	int i;
	if (a == x && b == y)
	{
		cnt++;
		for (i = 0; i <= step; i++)
		{
			printf("(%d,%d) ", nd[i].x, nd[i].y);
		}
		printf("\n");
		return;
	}
	else
	{
		if (x < a && y <= b)	//向右走
		{
			nd[step + 1].x = x + 1;
			nd[step + 1].y = y;
			ff(a, b, x + 1, y, step + 1);
		}
		if (y < b && x <= a)	//向上走
		{
			nd[step + 1].x = x;
			nd[step + 1].y = y + 1;
			ff(a, b, x, y + 1, step + 1);
		}
	}
}


int main()
{
	int a, b;
	while (scanf("%d%d", &a, &b) != EOF)
	{
		//cnt = 0;
		nd[0].x = nd[0].y = 0;
		ff(a, b, 0, 0, 0);
		printf("%d\n", cnt);
	}
	system("pause");
}
