/*
 * 编译器第一步——词法分析 
 * V1.0
 * by ChengXuan 2019/6/14
 * 分析一份C语言程序的内容，将函数名设置为灰色，将关键字设置为绿色，将整型、浮点型、字符、字符串等常量设置为褐色，将运算符设置为红色
 * 非常简陋
 * 暂时没写判断#include<>内的内容，这里会当成普通的函数名之类着色,待优化
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>

#define MAXKEY 1024		//哈希表长度

#define ISNUMBLE(c) (c >= '0' && c <= '9')
#define ISNOTNUMBLE(c) (c<'0'||c>'9')
#define ISLETTER(c) ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
#define ISNOTSPACE(c) (' ' != c && '\t' != c && '\n' != c)

typedef struct TkWord
{
	int  tkCode;		//单词编号
	char spelling[32];		//单词
	struct TkWord* pNext;
}TkWord_t,*pTkWord_t;

/* 对所有运算符及关键字进行编号 */
typedef enum TokenCode
{
	//关键字
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

	//整型、浮点型、字符、字符串等常量
	TK_CINT,			//整型常量
	TK_CFLOAT,			//浮点型常量
	TK_CCHAR,			//字符常量
	TK_CSTR,			//字符串常量

	//运算符
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
	TK_EOF,				// 文件结束符

	//函数名等
	TK_IDENT
}TokenCode_e;	//未考虑逻辑与，逻辑或，逻辑非等逻辑运算符，自增自减运算符不考虑


/* ------- 函数声明 ------- */
//哈希公式
int elf_hash(char* key);

/* 初始化 */
//初始化哈希表
Init_TkHashTable(pTkWord_t TkHashTable[], TkWord_t KeyWords[], int len);

/* 输出 */
//将字符输出并放入TkWord结点,返回token值
int Printf_PutinTkWord_Word(char* word, pTkWord_t TkHashTable[], int flag);
