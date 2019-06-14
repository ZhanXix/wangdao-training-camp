#include "WordAnalysis.h"

int main()
{
	FILE* fp;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	char buf[1024], word[64];			//分别存储读取的一行字符和取得的单词
	int i, j = 0;
	int pos;
	char c;
	int flag = 0;	//字符常量1、字符串常量2、数字3、单词4
	TokenCode_e token;					//单词的token
	pTkWord_t TkHashTable[MAXKEY];		//单词的哈希表
	static TkWord_t KeyWords[] =		//初始化单词结点
	{
		//关键字
		{KW_VOID,"void",NULL},
		{KW_CHAR,"char",NULL},
		{KW_SHORT,"short",NULL},
		{KW_INT,"int",NULL},
		{KW_UNSIGNED,"unsigned",NULL},
		{KW_LONG,"long",NULL},
		{KW_FLOAT,"float",NULL},
		{KW_DOUBLE,"double",NULL},
		{KW_STRUCT,"struct",NULL},
		{KW_IF,"if",NULL},
		{KW_ELSE,"else",NULL },
		{KW_WHILE,"while", NULL},
		{KW_FOR,"for", NULL},
		{KW_CONTINUE,"continue", NULL},
		{KW_BREAK,"break", NULL},
		{KW_GOTO,"goto", NULL},
		{KW_RETURN,"return", NULL},
		{KW_SIZEOF,	"sizeof", NULL},
		//整型、浮点型、字符、字符串等常量
		{TK_CINT,"整型常量",NULL },
		{TK_CFLOAT,"浮点型常量", NULL},
		{TK_CCHAR,"字符常量", NULL},
		{TK_CSTR,"字符串常量", NULL},
		//运算符
		{TK_PLUS,"+",NULL },
		{TK_MINUS,"-",NULL},
		{TK_STAR,"*",NULL},
		{TK_DIVIDE,"/", NULL},
		{TK_MOD, "%", NULL},
		{TK_ASSIGN,"=", NULL},
		{TK_EQ,"==", NULL},
		{TK_NEQ,"!=", NULL},
		{TK_LT,"<", NULL},
		{TK_LEQ,"<=", NULL},
		{TK_GT,">", NULL},
		{TK_GEQ,">=", NULL},
		{TK_DOT,".", NULL},
		{TK_POINTSTO,"->", NULL},
		{TK_AND,"&", NULL},
		{TK_OR,"|", NULL},
		{TK_NOT,"!", NULL},
		{TK_OPENPA,"(", NULL},
		{TK_CLOSEPA,")", NULL},
		{TK_OPENBR,"[", NULL},
		{TK_CLOSEBR,"]", NULL},
		{TK_BEGIN,"{", NULL},
		{TK_END,"}", NULL},
		{TK_SEMICOLON,";", NULL},
		{TK_COMMA,",", NULL},
		{TK_ELLIPSIS,"...", NULL},
		{TK_EOF, "EOF", NULL},
		//其他
		{0}
	};
	memset(TkHashTable, 0, sizeof(TkHashTable));
	Init_TkHashTable(TkHashTable, KeyWords, sizeof(KeyWords) / sizeof(TkWord_t));	//初始化哈希表
	printf("词法分析开始……\n");
	printf("--------------------------------------------------\n\n");
	fp = fopen("CSourceFile.txt", "r");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf), fp) != NULL)//读一行
	{
		for (i = 0; i < strlen(buf) + 1; ++i)	//之所以要加一是因为需要读最后的\n
		{
			c = buf[i];
			if (0 == flag)
			{
				if ('\'' == c)	//字符开始
				{
					flag = 1;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if ('\"' == c)	//字符串开始
				{
					flag = 2;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISNUMBLE(c))	//数字开始
				{
					flag = 3;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISLETTER(c) || '_' == c)	//单词开始
				{

					flag = 4;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISNOTSPACE(c))	//其他符号
				{
					flag = 5;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else
				{
					putchar(c);
					continue;
				}
			}//if (0 == flag)
			else if (1 == flag)	//字符
			{
				word[j] = c;
				if (c != '\n' && c != '\'')	//只有遇到换行或另一个'时才输出
				{
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=1
					flag = 0;
				}
			}
			else if (2 == flag)	//字符串
			{
				word[j] = c;
				if (c != '\n' && c != '\"')	//只有遇到换行或另一个"时才输出
				{
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=2
					flag = 0;
				}
			}
			else if (3 == flag || 30 == flag) //数字
			{
				if (ISNUMBLE(c))
				{
					word[j] = c;
					++j;
				}
				else if ('.' == c)
				{
					flag = 30;	//浮点型
					word[j] = c;
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=3 or 30
					flag = 0;
					--i;	//下一次还需要判断这一个字符到底是什么类型
				}
			}
			else if (4 == flag)	//单词
			{
				if (ISNUMBLE(c) || ISLETTER(c) || '_' == c)
				{
					word[j] = c;
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=4
					flag = 0;
					--i;
				}
			}
			else if (5 == flag)
			{
				if (('=' == c && ('=' == word[0] || '!' == word[0] || '<' == word[0] || '>' == word[0])) || ('>' == c && '-' == word[0]))
				{//== != <= >= ->
					word[1] = c;
					Printf_PutinTkWord_Word(word, TkHashTable, flag);
					flag = 0;
				}
				else
				{
					--i;
					Printf_PutinTkWord_Word(word, TkHashTable, flag);
					flag = 0;
				}
			}
			else
			{
				printf("ERROR FLAG!\n");
				goto error;
			}
		}//for (i = 0; i < strlen(buf) + 1; ++i)
	}
	SetConsoleTextAttribute(h, 0xf);
	printf("\n\n--------------------------------------------------\n");
error:
	system("pause");
}
