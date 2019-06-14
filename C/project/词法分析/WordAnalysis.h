/*
 * ��������һ�������ʷ����� 
 * V1.0
 * by ChengXuan 2019/6/14
 * ����һ��C���Գ�������ݣ�������������Ϊ��ɫ�����ؼ�������Ϊ��ɫ�������͡������͡��ַ����ַ����ȳ�������Ϊ��ɫ�������������Ϊ��ɫ
 * �ǳ���ª
 * ��ʱûд�ж�#include<>�ڵ����ݣ�����ᵱ����ͨ�ĺ�����֮����ɫ,���Ż�
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAXKEY 1024		//��ϣ����

#define ISNUMBLE(c) (c >= '0' && c <= '9')
#define ISNOTNUMBLE(c) (c<'0'||c>'9')
#define ISLETTER(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define ISNOTSPACE(c) (' ' != c && '\t' != c && '\n' != c)

typedef struct TkWord
{
	int  tkCode;		//���ʱ��
	char spelling[32];		//����
	struct TkWord* pNext;
}TkWord_t,*pTkWord_t;

/* ��������������ؼ��ֽ��б�� */
typedef enum TokenCode
{
	//�ؼ���
	KW_VOID,			//void
	KW_CHAR,			//char
	KW_SHORT,			//short
	KW_INT,				//int
	KW_UNSIGNED,		//unsigned
	KW_LONG,			//long
	KW_FLOAT,			//float
	KW_DOUBLE,			//double
	KW_STRUCT,			//struct
	KW_IF,				//if
	KW_ELSE,			//else
	KW_WHILE,			//while
	KW_FOR,				//for
	KW_CONTINUE,		//continue
	KW_BREAK,			//break
	KW_GOTO,			//goto
	KW_RETURN,			//return
	KW_SIZEOF,			//sizeof

	//���͡������͡��ַ����ַ����ȳ���
	TK_CINT,			//���ͳ���
	TK_CFLOAT,			//�����ͳ���
	TK_CCHAR,			//�ַ�����
	TK_CSTR,			//�ַ�������

	//�����
	TK_PLUS,			// +
	TK_MINUS,			// -
	TK_STAR,			// *
	TK_DIVIDE,			// /
	TK_MOD,				// %
	TK_ASSIGN,			// =
	TK_EQ,				// ==
	TK_NEQ,				// !=
	TK_LT,				// <
	TK_LEQ,				// <=
	TK_GT,				// >
	TK_GEQ,				// >=
	TK_DOT,				// .
	TK_POINTSTO,		// ->
	TK_AND,				// &
	TK_OR,				// |
	TK_NOT,				// !
	TK_OPENPA,			// (
	TK_CLOSEPA,			// )
	TK_OPENBR,			// [
	TK_CLOSEBR,			// ]
	TK_BEGIN,			// {
	TK_END,				// }
	TK_SEMICOLON,		// ;
	TK_COMMA,			// ,
	TK_ELLIPSIS,		// ...
	TK_EOF,				// �ļ�������

	//��������
	TK_IDENT
}TokenCode_e;	//δ�����߼��룬�߼����߼��ǵ��߼�������������Լ������������


/* ------- �������� ------- */
//��ϣ��ʽ
int elf_hash(char* key);

/* ��ʼ�� */
//��ʼ����ϣ��
Init_TkHashTable(pTkWord_t TkHashTable[], TkWord_t KeyWords[], int len);

/* ��� */
//���ַ����������TkWord���,����tokenֵ
int Printf_PutinTkWord_Word(char* word, pTkWord_t TkHashTable[], int flag);
