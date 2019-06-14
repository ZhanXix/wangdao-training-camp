#include "WordAnalysis.h"

int main()
{
	FILE* fp;
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	char buf[1024], word[64];			//�ֱ�洢��ȡ��һ���ַ���ȡ�õĵ���
	int i, j = 0;
	int pos;
	char c;
	int flag = 0;	//�ַ�����1���ַ�������2������3������4
	TokenCode_e token;					//���ʵ�token
	pTkWord_t TkHashTable[MAXKEY];		//���ʵĹ�ϣ��
	static TkWord_t KeyWords[] =		//��ʼ�����ʽ��
	{
		//�ؼ���
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
		//���͡������͡��ַ����ַ����ȳ���
		{TK_CINT,"���ͳ���",NULL },
		{TK_CFLOAT,"�����ͳ���", NULL},
		{TK_CCHAR,"�ַ�����", NULL},
		{TK_CSTR,"�ַ�������", NULL},
		//�����
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
		//����
		{0}
	};
	memset(TkHashTable, 0, sizeof(TkHashTable));
	Init_TkHashTable(TkHashTable, KeyWords, sizeof(KeyWords) / sizeof(TkWord_t));	//��ʼ����ϣ��
	printf("�ʷ�������ʼ����\n");
	printf("--------------------------------------------------\n\n");
	fp = fopen("CSourceFile.txt", "r");
	if (NULL == fp)
	{
		perror("fopen");
		goto error;
	}
	while (memset(buf, 0, sizeof(buf)), fgets(buf, sizeof(buf), fp) != NULL)//��һ��
	{
		for (i = 0; i < strlen(buf) + 1; ++i)	//֮����Ҫ��һ����Ϊ��Ҫ������\n
		{
			c = buf[i];
			if (0 == flag)
			{
				if ('\'' == c)	//�ַ���ʼ
				{
					flag = 1;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if ('\"' == c)	//�ַ�����ʼ
				{
					flag = 2;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISNUMBLE(c))	//���ֿ�ʼ
				{
					flag = 3;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISLETTER(c) || '_' == c)	//���ʿ�ʼ
				{

					flag = 4;
					j = 0;
					memset(word, 0, sizeof(word));
					word[j] = c;
					++j;
				}
				else if (ISNOTSPACE(c))	//��������
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
			else if (1 == flag)	//�ַ�
			{
				word[j] = c;
				if (c != '\n' && c != '\'')	//ֻ���������л���һ��'ʱ�����
				{
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=1
					flag = 0;
				}
			}
			else if (2 == flag)	//�ַ���
			{
				word[j] = c;
				if (c != '\n' && c != '\"')	//ֻ���������л���һ��"ʱ�����
				{
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=2
					flag = 0;
				}
			}
			else if (3 == flag || 30 == flag) //����
			{
				if (ISNUMBLE(c))
				{
					word[j] = c;
					++j;
				}
				else if ('.' == c)
				{
					flag = 30;	//������
					word[j] = c;
					++j;
				}
				else
				{
					Printf_PutinTkWord_Word(word, TkHashTable, flag);	//flag=3 or 30
					flag = 0;
					--i;	//��һ�λ���Ҫ�ж���һ���ַ�������ʲô����
				}
			}
			else if (4 == flag)	//����
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
