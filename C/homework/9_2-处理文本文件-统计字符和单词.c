/*
统计 "The_Holy_Bible_Res.txt" 中字符的个数，行数，单词的个数，统计单词的词频并打印输出词频最高的前10个单词及其词频。
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct count_char
{
	char theChar;
	unsigned count;
	struct count_char* pNextChar;
}CountChar_t, * pCountChar;

typedef struct count_word
{
	char theWord[20];
	unsigned count;
	struct count_word* pNextWord;
}CountWord_t, * pCountWord;

void CreatNewCharNode(pCountChar* pNew, char c)	//创建新char结点
{
	*pNew = (pCountChar)malloc(sizeof(CountChar_t));
	(*pNew)->theChar = c;
	(*pNew)->count = 1;
	(*pNew)->pNextChar = NULL;
}
//添加新char结点
void addChar(char c, pCountChar* charHead, pCountChar* charTail)
{
	pCountChar pCur = *charHead, pPre = NULL;
	pCountChar pNew;
	if (NULL == pCur)
	{
		CreatNewCharNode(&pNew, c);
		*charHead = pNew;
		*charTail = pNew;
	}
	else
	{
		while (pCur)
		{
			if (c == (pCur->theChar))
			{
				pCur->count++;
				return;
			}
			if (c < (pCur->theChar))	//有序插入
			{
				CreatNewCharNode(&pNew, c);
				pNew->pNextChar = pCur;
				if (NULL == pPre)	//在头结点前面插入
				{
					*charHead = pNew;
				}
				else
				{
					pPre->pNextChar = pNew;
				}
				break;
			}
			pPre = pCur;
			pCur = pCur->pNextChar;
		}
		if (NULL == pCur)//在尾结点后插入
		{
			CreatNewCharNode(&pNew, c);
			pPre->pNextChar = pNew;
			*charTail = pNew;
		}
	}
}
void printCountChar(pCountChar charHead)
{
	pCountChar pCur = charHead;
	int NumOfChar = 0;
	int NumOfLine = 0;
	while (pCur)
	{
		if ('\n' == pCur->theChar)
		{
			printf("\\n -- %d\n", pCur->count);
			NumOfLine = pCur->count + 1;
		}
		else if ('\t' == pCur->theChar)
		{
			printf("\\t -- %d\n", pCur->count);
		}
		else if (' ' == pCur->theChar)
		{
			printf("space -- %d\n", pCur->count);
		}
		else
		{
			printf("%c -- %d\n", pCur->theChar, pCur->count);
			NumOfChar += pCur->count;
		}
		pCur = pCur->pNextChar;
	}
	printf("行数 -- %d\n", NumOfLine);
	printf("字符总数 -- %d\n", NumOfChar);
}

void CreatNewWordNode(pCountWord* pNew, char* word)	//创建新word结点
{
	*pNew = (pCountWord)malloc(sizeof(CountWord_t));
	strcpy((*pNew)->theWord, word);
	(*pNew)->count = 1;
	(*pNew)->pNextWord = NULL;
}
//添加新word结点
void addWord(char* word, pCountWord* wordHead, pCountWord* wordTail)
{
	if (0 == word[0])
	{
		return;
	}
	pCountWord pCur = *wordHead, pPre = NULL;
	pCountWord pNew;
	pCountWord pCountCur = *wordHead, pCountPre = NULL;
	if (NULL == pCur)
	{
		CreatNewWordNode(&pNew, word);
		*wordHead = pNew;
		*wordTail = pNew;
	}
	else
	{
		while (pCur)
		{
			if (strcmp(pCur->theWord, word) == 0)
			{
				pCur->count++;
				if (pPre != NULL && pPre->count < pCur->count)
				{
					pPre->pNextWord = pCur->pNextWord;	//取下结点
					while (pCountCur != pCur)
					{
						if (pCountCur->count < pCur->count) {
							if (NULL == pCountPre)	//在头结点前面插入
							{
								pCur->pNextWord = *wordHead;
								*wordHead = pCur;
							}
							else
							{
								pCountPre->pNextWord = pCur;
								pCur->pNextWord = pCountCur;
							}
							break;
						}
						pCountPre = pCountCur;
						pCountCur = pCountCur->pNextWord;
					}
				}
				return;
			}
			pPre = pCur;
			pCur = pCur->pNextWord;
		}
		if (NULL == pCur)//在尾结点后插入
		{
			CreatNewWordNode(&pNew, word);
			pPre->pNextWord = pNew;
			*wordTail = pNew;
		}
	}
}
void printCountWord(pCountWord wordHead)
{
	pCountWord pCur = wordHead;
	int i;
	int NumOfWord = 0;
	printf("词频最高的前10个单词:\n");
	for (i = 0; i < 10; ++i)
	{

		printf("%s -- %d\n", pCur->theWord, pCur->count);
		NumOfWord += pCur->count;
		pCur = pCur->pNextWord;
	}
	while (pCur)
	{
		NumOfWord += pCur->count;
		pCur = pCur->pNextWord;
	}
	printf("单词总数 -- %d\n", NumOfWord);
}

int main()
{
	FILE* fp;
	time_t start, end;
	char buf[5000], word[20] = { 0 };
	int i = 0, j = 0;
	int NumOfAllChar = 0, NumOfAllWord = 0;
	pCountChar charHead = NULL, charTail = NULL;
	pCountWord wordHead = NULL, wordTail = NULL;
	fp = fopen("The_Holy_Bible_Res.txt", "r");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	start = time(NULL);
	while (memset(buf, 0, sizeof(buf)), (fgets(buf, sizeof(buf), fp)) != NULL)//读一行
	{
		for (i = 0; i < strlen(buf); ++i)	//处理这行的字符
		{
			addChar(buf[i], &charHead, &charTail);
			if (buf[i] == ' ' || buf[i] == '\n' || buf[i] == '\t' || (buf[i] >= '0' && buf[i] <= '9'))
			{
				word[j] = '\0';
				addWord(word, &wordHead, &wordTail);
				j = 0;
				memset(word, 0, sizeof(word));
			}
			else
			{
				word[j] = buf[i];
				++j;
			}
		}
		//puts(buf);	//本行用于调试
	}
	end = time(NULL);
	printCountChar(charHead);
	putchar('\n');
	printCountWord(wordHead);
	putchar('\n');
	printf("处理完毕，用时 %d 秒\n", end - start);
	fclose(fp);
error:
	system("pause");
}

/*
处理结果：
\t-- 31102
\n-- 32432
space-- 965712
0 -- 2706
1 -- 14287
2 -- 10073
3 -- 6358
4 -- 4580
5 -- 3745
6 -- 3346
7 -- 3115
8 -- 2944
9 -- 2804
a-- 275987
b-- 48721
c-- 54900
d-- 157907
e-- 411640
f-- 83345
g-- 55068
h-- 282887
i-- 193866
j-- 8979
k-- 22281
l-- 129993
m-- 80261
n-- 224739
o-- 242558
p-- 43117
q-- 953
r-- 169688
s-- 190459
t-- 316722
u-- 83358
v-- 30422
w-- 65310
x-- 1490
y-- 58321
z-- 3050
行数-- 32433
字符总数-- 3289980

词频最高的前10个单词:
the-- 64045
and -- 51714
of-- 34765
to-- 13643
that-- 12916
in-- 12674
he-- 10431
shall-- 9837
unto-- 9003
for -- 8985
单词总数-- 793931

处理完毕，用时 5 秒
*/

/* 
 * 教学1——使用windows接口得到更高精度的时间
 * #include <windows.h>
 * GetTickCount
 * 这个接口的返回值是操作系统启动后经过的毫秒数，类型是DWORD(typedef unsigned long DWORD)
 */
 
 /*
  * 教学2-使用Hash来做这道题
  *
int elf_hash(char *key)
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
			h ^= g >> 24;
		h &= ~g;
	}
	return h % MAXKEY;
}
  *	  
  */
