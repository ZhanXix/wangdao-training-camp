/*
ͳ�� "The_Holy_Bible_Res.txt" ���ַ��ĸ��������������ʵĸ�����ͳ�Ƶ��ʵĴ�Ƶ����ӡ�����Ƶ��ߵ�ǰ10�����ʼ����Ƶ��
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

void CreatNewCharNode(pCountChar* pNew, char c)	//������char���
{
	*pNew = (pCountChar)malloc(sizeof(CountChar_t));
	(*pNew)->theChar = c;
	(*pNew)->count = 1;
	(*pNew)->pNextChar = NULL;
}
//�����char���
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
			if (c < (pCur->theChar))	//�������
			{
				CreatNewCharNode(&pNew, c);
				pNew->pNextChar = pCur;
				if (NULL == pPre)	//��ͷ���ǰ�����
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
		if (NULL == pCur)//��β�������
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
	printf("���� -- %d\n", NumOfLine);
	printf("�ַ����� -- %d\n", NumOfChar);
}

void CreatNewWordNode(pCountWord* pNew, char* word)	//������word���
{
	*pNew = (pCountWord)malloc(sizeof(CountWord_t));
	strcpy((*pNew)->theWord, word);
	(*pNew)->count = 1;
	(*pNew)->pNextWord = NULL;
}
//�����word���
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
					pPre->pNextWord = pCur->pNextWord;	//ȡ�½��
					while (pCountCur != pCur)
					{
						if (pCountCur->count < pCur->count) {
							if (NULL == pCountPre)	//��ͷ���ǰ�����
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
		if (NULL == pCur)//��β�������
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
	printf("��Ƶ��ߵ�ǰ10������:\n");
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
	printf("�������� -- %d\n", NumOfWord);
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
	while (memset(buf, 0, sizeof(buf)), (fgets(buf, sizeof(buf), fp)) != NULL)//��һ��
	{
		for (i = 0; i < strlen(buf); ++i)	//�������е��ַ�
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
		//puts(buf);	//�������ڵ���
	}
	end = time(NULL);
	printCountChar(charHead);
	putchar('\n');
	printCountWord(wordHead);
	putchar('\n');
	printf("������ϣ���ʱ %d ��\n", end - start);
	fclose(fp);
error:
	system("pause");
}

/*
��������
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
����-- 32433
�ַ�����-- 3289980

��Ƶ��ߵ�ǰ10������:
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
��������-- 793931

������ϣ���ʱ 5 ��
*/

/* 
 * ��ѧ1����ʹ��windows�ӿڵõ����߾��ȵ�ʱ��
 * #include <windows.h>
 * GetTickCount
 * ����ӿڵķ���ֵ�ǲ���ϵͳ�����󾭹��ĺ�������������DWORD(typedef unsigned long DWORD)
 */
 
 /*
  * ��ѧ2-ʹ��Hash���������
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
