/*
1.将包含字符数字的字符串分开,使得分开后的字符串前一部分是数字后一部分是字母。
例如“h1ell2o3” ->”123hello”
*/

#include <stdio.h>
#include <stdlib.h>

int main()
{
	char str[51] = { 0 };
	int lastNum;	//表示最后一个排好序的数字所在位置
	int now;	//表示当前处理位置
	char temp;
	printf("输入一串包含字符和数字的字符串(最长50个字符)：\n");
	while (gets(str) != 0)
	{
		for (lastNum = 0, now = 0; now < strlen(str); ++now)
		{
			if (str[now] >= '0' && str[now] <= '9')
			{
				temp = str[now];
				for (int i = now; i > lastNum; --i)
				{//将之前的字母向后移位
					str[i] = str[i - 1];
				}
				str[lastNum] = temp;
				lastNum++;
			}
		}
		printf("处理结果：");
		puts(str);
		printf("\n输入一串包含字符和数字的字符串(最长50个字符)：\n");
	}
	system("pause");
}

/*
* 教学：用O(1)实现：可以使用快排的思想，把数字放到前面，把字母放到后面
* 不过不能直接交换，而应该使用插入排序思想，每次移动一串字符串，以避免顺序混乱
* 移动一串字符可以用memmove
*/