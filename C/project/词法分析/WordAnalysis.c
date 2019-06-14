#include "WordAnalysis.h"

//��ϣ��ʽ
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

//��ʼ����ϣ��
Init_TkHashTable(pTkWord_t TkHashTable[], TkWord_t KeyWords[], int len)
{
	int i, pos;
	pTkWord_t pCur, pPre;
	for (i = 0; i < len - 1; ++i)
	{
		pos = elf_hash(KeyWords[i].spelling);
		if (NULL == TkHashTable[pos])
		{
			TkHashTable[pos] = &KeyWords[i];	//�����ϣ����Ӧλ��
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

//���ַ����������TkWord���,����tokenֵ
int Printf_PutinTkWord_Word(char* word, pTkWord_t TkHashTable[], int flag)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	int ret;
	int pos = elf_hash(word);
	pTkWord_t pNew;
	pTkWord_t pPre = NULL, pCur = TkHashTable[pos];
	while (pCur)
	{
		if (strcmp(pCur->spelling, word) == 0)
		{
			ret = pCur->tkCode;
			if (ret >= TK_IDENT)	//����
			{
				SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//��ɫ
				printf("%s",word);
			}
			else if (ret >= TK_PLUS)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
				printf("%s",word);
			}
			else if (ret >= TK_CINT)
			{
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//��ɫ
				printf("%s",word);
			}
			else
			{
				SetConsoleTextAttribute(h, FOREGROUND_GREEN | FOREGROUND_INTENSITY);//��ɫ
				printf("%s",word);
			}
			return ret;
		}
		pPre = pCur;
		pCur = pCur->pNext;
	}
	if (NULL == pCur)
	{
		pNew = (pTkWord_t)malloc(sizeof(TkWord_t));	//�����½��
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
		case 1:	//�ַ�����
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//��ɫ
			printf("%s",word);
			pNew->tkCode = TK_CCHAR;
			return pNew->tkCode;
		case 2:	//�ַ�������
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//��ɫ
			printf("%s",word);
			pNew->tkCode = TK_CSTR;
			return pNew->tkCode;
		case 3:	//���ͳ���
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//��ɫ
			printf("%s",word);
			pNew->tkCode = TK_CINT;
			return pNew->tkCode;
		case 30:	//�����ͳ���
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_GREEN);//��ɫ
			printf("%s",word);
			pNew->tkCode = TK_CFLOAT;
			return pNew->tkCode;
		default:	//��������
			SetConsoleTextAttribute(h, FOREGROUND_INTENSITY);//��ɫ
			printf("%s",word)                                                                                                                                                                                                                                                                                                     ;
			pNew->tkCode = TK_IDENT;
			return pNew->tkCode;
		}
	}
}