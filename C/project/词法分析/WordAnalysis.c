#include "WordAnalysis.h"

//哈希公式
int elf_hash(char* key)
{
	int h = 0, g;
	while (*key)
	{
		h = (h << 4) + *key++;
		g = h & 0xf0000000;
		if (g)
		{
			h ^= g >> 24;
		}
		h &= ~g;
	}
	return h % MAXKEY;
}

//初始化哈希表
Init_TkHashTable(pTkWord_t TkHashTable[], TkWord_t KeyWords[], int len)
{
	int i, pos;
	pTkWord_t pCur, pPre;
	for (i = 0; i < len - 1; ++i)
	{
		pos = elf_hash(KeyWords[i].spelling);
		if (NULL == TkHashTable[pos])
		{
			TkHashTable[pos] = &KeyWords[i];	//插入哈希表相应位置
		}
		else
		{
			pCur = TkHashTable[pos];
			while (pCur)
			{
				pPre = pCur;
				pCur = pCur->pNext;
			}
			pPre->pNext = &KeyWords[i];
		}
	}
}

//将字符输出并放入TkWord结点,返回token值
int Printf_PutinTkWord_Word(char* word, pTkWord_t TkHashTable[], int flag)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	int ret;
	int pos = elf_hash(word);
	pTkWord_t pNew;
	pTkWord_t pPre = NULL, pCur = TkHashTable[pos];
	while (pCur)
	{
		if (strcmp(pCur->spelling, word) == 0)
		{
			ret = pCur->tkCode;
			if (ret >= TK_IDENT)	//其他
			{
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//灰色
				printf("%s",word);
			}
			else if (ret >= TK_PLUS)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
				printf("%s",word);
			}
			else if (ret >= TK_CINT)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//褐色
				printf("%s",word);
			}
			else
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//绿色
				printf("%s",word);
			}
			return ret;
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (NULL == pCur)
	{
		pNew = (pTkWord_t)malloc(sizeof(TkWord_t));	//建立新结点
		memset(pNew, 0, sizeof(TkWord_t));
		strcpy(pNew->spelling, word);
		if (NULL == pPre)
		{
			TkHashTable[pos] = pNew;
		}
		else
		{
			pPre->pNext = pNew;
		}
		switch (flag)
		{
		case 1:	//字符常量
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//褐色
			printf("%s",word);
			pNew->tkCode = TK_CCHAR;
			return pNew->tkCode;
		case 2:	//字符串常量
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//褐色
			printf("%s",word);
			pNew->tkCode = TK_CSTR;
			return pNew->tkCode;
		case 3:	//整型常量
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//褐色
			printf("%s",word);
			pNew->tkCode = TK_CINT;
			return pNew->tkCode;
		case 30:	//浮点型常量
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//褐色
			printf("%s",word);
			pNew->tkCode = TK_CFLOAT;
			return pNew->tkCode;
		default:	//其他单词
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//灰色
			printf("%s",word)                                                                                                                                                                                                                                                                                                     ;
			pNew->tkCode = TK_IDENT;
			return pNew->tkCode;
		}
	}
}