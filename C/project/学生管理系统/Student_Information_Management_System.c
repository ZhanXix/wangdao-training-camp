#include "Student_Information_Management_System.h"

//打开文件，若没有文件即在information文件夹下创建文件
void Init_Student_Information_Management_System(FILE** pfp_stu, FILE** pfp_usr, FILE** pfp_cou)
{
	*pfp_stu = fopen("information\\stu_inf.txt", "r+");
	if (NULL == *pfp_stu)
	{
		*pfp_stu = fopen("information\\stu_inf.txt", "w+");
	}
	*pfp_usr = fopen("information\\usr_inf.txt", "r+");
	if (NULL == *pfp_usr)
	{
		*pfp_usr = fopen("information\\usr_inf.txt", "w+");
		fprintf(*pfp_usr, "admin admin Y\n");		//创建管理员用户
		fseek(*pfp_usr, -15, SEEK_SET);
	}
	*pfp_cou = fopen("information\\cou_inf.txt", "r+");
	if (NULL == *pfp_cou)
	{
		*pfp_cou = fopen("information\\cou_inf.txt", "w+");
	}
	if (NULL == *pfp_stu || NULL == *pfp_usr || NULL == *pfp_cou)
	{
		perror("fopen");
	}
}

//创建新course结点
void Create_New_Course_Information_Node(pCourse_Information_t* ppHead_cou, pCourse_Information_t* ppTail_cou, pCourse_Information_t pcou)
{
	pCourse_Information_t pNew;
	pNew = (pCourse_Information_t)malloc(sizeof(Course_Information_t));
	memset(pNew, 0, sizeof(Course_Information_t));
	pNew->course_id = pcou->course_id;
	strcpy(pNew->course_name, pcou->course_name);
	if (NULL == *ppHead_cou)
	{
		*ppHead_cou = pNew;
		*ppTail_cou = pNew;
	}
	else
	{
		(*ppTail_cou)->pNext_course = pNew;
		*ppTail_cou = pNew;
	}
}

//创建新student结点
void Create_New_Student_Information_Node(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, char* stu_buf, int cou_num)
{
	int i = 0, j = 0, k = 0;
	int flag = 0;
	char score[20];
	pStudent_Information_t pNew;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	memset(pNew, 0, sizeof(Student_Information_t));
	sscanf(stu_buf, "%d%s", &pNew->student_id, &pNew->student_name);
	for (i = 0; stu_buf[i] != 0; ++i)	//解决成绩的问题，由于课程数目不定所以有点麻烦
	{
		if (' ' == stu_buf[i] && flag)
		{
			break;
		}
		else if (' ' == stu_buf[i])
		{
			flag = 1;
		}
	}
	for (j = 0; j < cou_num; ++j)
	{
		memset(score, 0, sizeof(score));
		k = 0;
		while (stu_buf[i] != 0)
		{
			++i;
			if (' ' == stu_buf[i])
			{
				break;
			}
			else
			{
				score[k] = stu_buf[i];
				++k;
			}
		}
		pNew->course_score[j] = atof(score);
	}
	if (NULL == *ppHead_stu)
	{
		*ppHead_stu = pNew;
		*ppTail_stu = pNew;
	}
	else
	{
		(*ppTail_stu)->pNext_student = pNew;
		*ppTail_stu = pNew;
	}
}

//创建新user结点
void Create_New_User_Information_Node(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr, pUser_Information_t pusr)
{
	pUser_Information_t pNew;
	pNew = (pUser_Information_t)malloc(sizeof(User_Information_t));
	memset(pNew, 0, sizeof(User_Information_t));
	strcpy(pNew->user_name, pusr->user_name);
	strcpy(pNew->user_password, pusr->user_password);
	pNew->user_is_administrator = pusr->user_is_administrator;
	if (NULL == *ppHead_usr)
	{
		*ppHead_usr = pNew;
		*ppTail_usr = pNew;
	}
	else
	{
		(*ppTail_usr)->pNext_user = pNew;
		*ppTail_usr = pNew;
	}
}

//登录
void Sign_In(pUser_Information_t pusr, pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pUser_Information_t pCur;
	char c;
	char psw[USER_NAME_LENTH];
	int i;

	/* ------ 开始输入 ------ */
sign_in:
	memset(pusr, 0, sizeof(User_Information_t));	//重置pusr
	memset(psw, 0, sizeof(psw));		//重置密码
	pCur = pHead_usr;		//重置指针
	i = 0;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------ 登录 ------------|\n");
	printf("| \n");
	printf("| 用户名：");
	gets(pusr->user_name, sizeof(pusr->user_name), stdin);
	if (pusr->user_name[USER_NAME_LENTH - 1] != 0)	//用户名长度超限
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("** 错误 ** 用户名过长！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("| 需要重新登录\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	else if (0 == pusr->user_name[0])	//未输入用户名
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("** 错误 ** 请输入用户名！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("| 需要重新登录\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	rewind(stdin);
	printf("| 密码：");
	while ((c = getch()) != '\r')
	{
		if ('\b' == c)	//输入退格
		{
			if (i > 0)	//之前输入过密码
			{
				printf("\b \b");
				if (USER_NAME_LENTH - 1 >= i)
				{
					psw[i] = 0;
				}
				--i;
			}
			else//之前并没有输密码
			{
				continue;
			}
		}
		else//输入回车之外的其他字符-均视作密码
		{
			if (USER_NAME_LENTH - 1 >= i)
			{
				psw[i] = c;
			}
			printf("*");
			++i;
		}
	}
	printf("\n");
	if (psw[USER_NAME_LENTH - 1] != 0)	//密码长度超限
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("** 错误 ** 密码过长！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("| 需要重新登录\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	else if (0 == psw[0])	//未输入密码
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("** 错误 ** 请输入密码！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("| 需要重新登录\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	strcpy(pusr->user_password, psw);
	/* ------ 输入完成 ------ */

	/* ------ 开始匹配 ------ */
	while (pCur)
	{
		if (0 == strcmp(pusr->user_name, pCur->user_name) && 0 == strcmp(pusr->user_password, pCur->user_password))
		{
			printf("| \n");
			printf("| 登录成功！\n");
			pusr->user_is_administrator = pCur->user_is_administrator;
			return;
		}
		pCur = pCur->pNext_user;
	}
	if (NULL == pCur)	//匹配失败
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("** 错误 ** 用户名或密码不正确！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("| 需要重新登录\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
}

//菜单输入错误
void Wrong_Menu_Num()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	printf(" \n");
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
	printf("  ** 错误 ** 菜单输入错误！\n");
	SetConsoleTextAttribute(h, 0xf);	//白色
	printf("  需要重新输入\n");
}

//管理员菜单
char Administrator_Menu()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------ 管理员功能菜单 ------------|\n");
	printf("|                                        |\n");
	printf("|             1.查询学生信息             |\n");
	printf("|             2.添加学生信息             |\n");
	printf("|             3.修改学生信息             |\n");
	printf("|             4.删除学生信息             |\n");
	printf("|             5.查询账户                 |\n");
	printf("|             6.添加新账户               |\n");
	printf("|             7.修改账户信息             |\n");
	printf("|             8.删除账户                 |\n");
	printf("|             9.退出系统                 |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu0:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	if (menu_num >= '1' && menu_num <= '9')
	{
		menu_num -= '0';
	}
	else
	{
		Wrong_Menu_Num();
		goto menu0;
	}
	return menu_num;
}

//管理员菜单1.查询学生信息
char Administrator_Menu_1()
{
	char menu_num;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------- 查询学生信息 -------------|\n");
	printf("|                                        |\n");
	printf("|              1.查询全部                |\n");
	printf("|              2.按学号查询              |\n");
	printf("|              3.按姓名查询              |\n");
	printf("|              4.返回                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu1:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 11;
	case '2':
		return 12;
	case '3':
		return 13;
	case '4':
		return 14;
	default:
		Wrong_Menu_Num();
		goto menu1;
		break;
	}
}
//11.查询全部学生信息
char Print_pStudent_Information(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	pStudent_Information_t pCur_stu = pHead_stu;
	pCourse_Information_t pCur_cou = pHead_cou;
	int i;
	char menu_num;
	system("cls");
	printf(" \n");
	if (pCur_stu)
	{
		printf("|------------- 全部学生信息 -------------|\n");
		printf("\n");
		printf("      学号                姓名");
		while (pCur_cou)
		{
			printf("%10s", pCur_cou->course_name);
			pCur_cou = pCur_cou->pNext_course;
		}
		printf("\n");
		while (pCur_stu)
		{
			printf("%10d%20s", pCur_stu->student_id, pCur_stu->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				printf("%10.2f", pCur_stu->course_score[i]);
			}
			printf("\n");
			pCur_stu = pCur_stu->pNext_student;
		}
	}
	else
	{
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供查询的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
	printf("\n");
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
menu11:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 1;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu11;
		break;
	}
}
//12.按学号查询学生信息
char Search_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pCur_stu;
	pCourse_Information_t pCur_cou;
	int i;
	int id = -1;
	char menu_num;
	system("cls");
menu120:
	pCur_stu = pHead_stu;
	pCur_cou = pHead_cou;
	printf(" \n");
	if (pCur_stu)
	{
		printf("|------------- 查询学生信息 -------------|\n");
		printf("\n");
		printf("请输入学号：");
		rewind(stdin);
		scanf("%d", &id);
		while (pCur_stu)
		{
			if (id == pCur_stu->student_id)
			{
				break;
			}
			pCur_stu = pCur_stu->pNext_student;
		}
		if (NULL == pCur_stu)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 学号不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入学号\n");
			goto menu120;
		}
		else
		{
			printf(" \n");
			printf("      学号                姓名");
			while (pCur_cou)
			{
				printf("%10s", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
			}
			printf("\n");
			printf("%10d%20s", pCur_stu->student_id, pCur_stu->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				printf("%10.2f", pCur_stu->course_score[i]);
			}
			printf("\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供查询的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
	printf("\n");
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu12:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 1;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu12;
		break;
	}
}
//13.按姓名查询学生信息
char Search_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pCur_stu;
	pCourse_Information_t pCur_cou;
	int i;
	char name[STUDENT_NAME_LENTH] = { 0 };
	char menu_num;
	system("cls");
menu130:
	pCur_stu = pHead_stu;
	pCur_cou = pHead_cou;
	printf(" \n");
	if (pCur_stu)
	{
		printf("|------------- 查询学生信息 -------------|\n");
		printf("\n");
		printf("请输入姓名：");
		rewind(stdin);
		scanf("%s", name);
		while (pCur_stu)
		{
			if (0 == strcmp(pCur_stu->student_name, name))
			{
				break;
			}
			pCur_stu = pCur_stu->pNext_student;
		}
		if (NULL == pCur_stu)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 姓名不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入姓名\n");
			goto menu130;
		}
		else
		{
			printf(" \n");
			printf("      学号                姓名");
			while (pCur_cou)
			{
				printf("%10s", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
			}
			printf("\n");
			printf("%10d%20s", pCur_stu->student_id, pCur_stu->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				printf("%10.2f", pCur_stu->course_score[i]);
			}
			printf("\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供查询的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
	printf("\n");
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu13:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 1;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu13;
		break;
	}
}

//管理员菜单2.添加学生信息
char Add_pStudent_Information(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pNew, pCur_stu;
	pCourse_Information_t pCur_cou;
	FILE* fp_stu;
	int i;
	char menu_num;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	system("cls");
menu2:
	memset(pNew, 0, sizeof(Student_Information_t));		//重置pnew
	i = 0;
	pCur_cou = pHead_cou;
	pCur_stu = *ppHead_stu;
	printf("\n");
	printf("|------------- 添加学生信息 -------------|\n\n");
	printf(" 请按如下格式添加学生基础信息：\n");
	printf("学号  姓名\n");
	rewind(stdin);
	if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
	{
	error_menu2:
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 错误 ** 输入格式错误！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("  请重新输入\n");
		goto menu2;
	}
	while (pCur_stu)
	{
		if (pCur_stu->student_id == pNew->student_id)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 输入学号错误！已存在该学号\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入\n");
			goto menu2;
		}
		pCur_stu = pCur_stu->pNext_student;
	}
	printf("\n 请继续按如下格式添加学生课程分数：\n");
	while (pCur_cou)
	{
		printf(" %s分数：", pCur_cou->course_name);
		pCur_cou = pCur_cou->pNext_course;
		rewind(stdin);
		if (scanf("%lf", &pNew->course_score[i]) != 1)
		{
			goto error_menu2;
		}
		++i;
	}
	printf("\n");
	if (NULL == *ppHead_stu)
	{
		*ppHead_stu = pNew;
		*ppTail_stu = pNew;
	}
	else
	{
		(*ppTail_stu)->pNext_student = pNew;
		*ppTail_stu = pNew;
	}
	fp_stu = fopen("information\\stu_inf.txt", "a");
	fprintf(fp_stu, "%d %s", pNew->student_id, pNew->student_name);
	for (i = 0; i < cou_num; ++i)
	{
		fprintf(fp_stu, " %lf", pNew->course_score[i]);
	}
	fprintf(fp_stu, "\n");
	fclose(fp_stu);
	printf("\n 添加学生信息成功！\n");
	printf("	1.返回主菜单\n");
	printf("	2.退出程序\n");
	printf("\n");
menu21:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 14;
	case '2':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//管理员菜单3.修改学生信息
char Administrator_Menu_3()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- 修改学生信息 -------------|\n");
	printf("|                                        |\n");
	printf("|              1.按学号修改              |\n");
	printf("|              2.按姓名修改              |\n");
	printf("|              3.返回                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu3:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 31;
	case '2':
		return 32;
	case '3':
		return 14;
	default:
		Wrong_Menu_Num();
		goto menu3;
		break;
	}
}
//31.按学号修改学生信息
char Change_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pCur_stu, pExam_stu, pCur = pHead_stu;
	pCourse_Information_t pCur_cou;
	pStudent_Information_t pNew;
	FILE* fp_stu;
	char stu_buf[sizeof(Student_Information_t)];
	int i;
	int id = -1;
	char menu_num;
	char change_num;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	system("cls");
menu31:
	pCur_stu = pHead_stu;
	pCur_cou = pHead_cou;
	printf(" \n");
	if (pCur_stu)
	{
		printf("|------------- 修改学生信息 -------------|\n");
		printf("\n");
		printf("请输入学号：");
		rewind(stdin);
		scanf("%d", &id);
		while (pCur_stu)
		{
			if (id == pCur_stu->student_id)
			{
				break;
			}
			pCur_stu = pCur_stu->pNext_student;
		}
		if (NULL == pCur_stu)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 学号不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入学号\n");
			goto menu31;
		}
		else
		{
			printf("\n当前学生信息：\n");
			printf("      学号                姓名");
			while (pCur_cou)
			{
				printf("%10s", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
			}
			printf("\n");
			printf("%10d%20s", pCur_stu->student_id, pCur_stu->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				printf("%10.2f", pCur_stu->course_score[i]);
			}
		menu2:
			memset(pNew, 0, sizeof(Student_Information_t));		//重置pnew
			pExam_stu = pHead_stu;
			pCur_cou = pHead_cou;
			printf("\n\n请按如下格式输入修改后的学生信息：\n");
			printf("学号 姓名\n");
			rewind(stdin);
			if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
			{
			error_menu2:
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
				printf("  ** 错误 ** 输入格式错误！\n");
				SetConsoleTextAttribute(h, 0xf);	//白色
				printf("  请重新输入\n");
				goto menu2;
			}
			while (pExam_stu)
			{
				if (pExam_stu != pCur_stu && pExam_stu->student_id == pNew->student_id)
				{
					printf(" \n");
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
					printf("  ** 错误 ** 输入学号错误！已存在该学号\n");
					SetConsoleTextAttribute(h, 0xf);	//白色
					printf("  请重新输入\n");
					goto menu2;
				}
				pExam_stu = pExam_stu->pNext_student;
			}
			printf("\n 请继续按如下格式修改学生课程分数：\n");
			i = 0;
			while (pCur_cou)
			{
				printf(" %s分数：", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
				rewind(stdin);
				if (scanf("%lf", &pNew->course_score[i]) != 1)
				{
					goto error_menu2;
				}
				++i;
			}
			printf("\n");
			pCur_stu->student_id = pNew->student_id;
			strcpy(pCur_stu->student_name, pNew->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				pCur_stu->course_score[i] = pNew->course_score[i];
			}
			//结点修改完成
			//开始重写文件
			fp_stu = fopen("information\\stu_inf.txt", "w+");
			while (pCur)
			{
				fprintf(fp_stu, "%d %s", pCur->student_id, pCur->student_name);
				for (i = 0; i < cou_num; ++i)
				{
					fprintf(fp_stu, " %lf", pCur->course_score[i]);
				}
				fprintf(fp_stu, "\n");
				pCur = pCur->pNext_student;
			}
			fclose(fp_stu);
			printf("\n修改学生信息成功！\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供修改的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
menu20:
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu21:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 3;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}
//32.按姓名修改学生信息
char Change_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pCur_stu, pExam_stu, pCur = pHead_stu;
	pCourse_Information_t pCur_cou;
	pStudent_Information_t pNew;
	FILE* fp_stu;
	char stu_buf[sizeof(Student_Information_t)];
	int i;
	char name[STUDENT_NAME_LENTH] = { 0 };
	char menu_num;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	system("cls");
menu31:
	pCur_stu = pHead_stu;
	pCur_cou = pHead_cou;
	printf(" \n");
	if (pCur_stu)
	{
		printf("|------------- 修改学生信息 -------------|\n");
		printf("\n");
		printf("请输入姓名：");
		rewind(stdin);
		scanf("%s", name);
		while (pCur_stu)
		{
			if (0 == strcmp(pCur_stu->student_name, name))
			{
				break;
			}
			pCur_stu = pCur_stu->pNext_student;
		}
		if (NULL == pCur_stu)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 姓名不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入姓名\n");
			goto menu31;
		}
		else
		{
			printf("\n当前学生信息：\n");
			printf("      学号                姓名");
			while (pCur_cou)
			{
				printf("%10s", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
			}
			printf("\n");
			printf("%10d%20s", pCur_stu->student_id, pCur_stu->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				printf("%10.2f", pCur_stu->course_score[i]);
			}
		menu2:
			memset(pNew, 0, sizeof(Student_Information_t));		//重置pnew
			pExam_stu = pHead_stu;
			pCur_cou = pHead_cou;
			printf("\n\n请按如下格式输入修改后的学生信息：\n");
			printf("学号 姓名\n");
			rewind(stdin);
			if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
			{
			error_menu2:
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
				printf("  ** 错误 ** 输入格式错误！\n");
				SetConsoleTextAttribute(h, 0xf);	//白色
				printf("  请重新输入\n");
				goto menu2;
			}
			while (pExam_stu)
			{
				if (pExam_stu != pCur_stu && pExam_stu->student_id == pNew->student_id)
				{
					printf(" \n");
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
					printf("  ** 错误 ** 输入学号错误！已存在该学号\n");
					SetConsoleTextAttribute(h, 0xf);	//白色
					printf("  请重新输入\n");
					goto menu2;
				}
				pExam_stu = pExam_stu->pNext_student;
			}
			printf("\n 请继续按如下格式修改学生课程分数：\n");
			i = 0;
			while (pCur_cou)
			{
				printf(" %s分数：", pCur_cou->course_name);
				pCur_cou = pCur_cou->pNext_course;
				rewind(stdin);
				if (scanf("%lf", &pNew->course_score[i]) != 1)
				{
					goto error_menu2;
				}
				++i;
			}
			printf("\n");
			pCur_stu->student_id = pNew->student_id;
			strcpy(pCur_stu->student_name, pNew->student_name);
			for (i = 0; i < cou_num; ++i)
			{
				pCur_stu->course_score[i] = pNew->course_score[i];
			}
			//结点修改完成
			//开始重写文件
			fp_stu = fopen("information\\stu_inf.txt", "w+");
			while (pCur)
			{
				fprintf(fp_stu, "%d %s", pCur->student_id, pCur->student_name);
				for (i = 0; i < cou_num; ++i)
				{
					fprintf(fp_stu, " %lf", pCur->course_score[i]);
				}
				fprintf(fp_stu, "\n");
				pCur = pCur->pNext_student;
			}
			fclose(fp_stu);
			printf("\n修改学生信息成功！\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供修改的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
menu20:
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu21:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 3;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//管理员菜单4.删除学生信息
char Administrator_Menu_4()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- 删除学生信息 -------------|\n");
	printf("|                                        |\n");
	printf("|              1.按学号删除              |\n");
	printf("|              2.按姓名删除              |\n");
	printf("|              3.返回                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu3:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 41;
	case '2':
		return 42;
	case '3':
		return 14;
	default:
		Wrong_Menu_Num();
		goto menu3;
		break;
	}
}
//41.按学号删除学生信息
char Delete_pStudent_Information_By_id(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pPre, pCur;
	FILE* fp_stu;
	char menu_num;
	int id;
	int i;
	system("cls");
menu41:
	pCur = *ppHead_stu;
	pPre = NULL;
	printf(" \n");
	if (pCur)
	{
		printf("|------------- 删除学生信息 -------------|\n");
		printf("\n");
		printf("请输入要删除的学号：");
		rewind(stdin);
		scanf("%d", &id);
		while (pCur)
		{
			if (id == pCur->student_id)
			{
				break;
			}
			pPre = pCur;
			pCur = pCur->pNext_student;
		}
		if (NULL == pCur)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 学号不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入学号\n");
			goto menu41;
		}
		else
		{
			printf("\n  当前要删除的学生信息：\n");
			printf("      学号                姓名\n");
			printf("%10d%20s", pCur->student_id, pCur->student_name);
			printf("\n  确认删除？\n");
			printf("  1.确认\n");
			printf("  2.取消\n");
			printf("  3.直接返回上一级\n");
			printf("  4.直接返回主菜单\n");
		menu42:
			printf("\n");
			printf("  请输入菜单编号：");
			rewind(stdin);
			menu_num = getchar();
			rewind(stdin);
			switch (menu_num)
			{
			case '1':
				break;;
			case '2':
				goto menu41;
			case '3':
				return 4;
			case '4':
				return 14;
			default:
				Wrong_Menu_Num();
				goto menu42;
				break;
			}//switch
			//开始删除结点
			if (NULL == pPre)
			{
				*ppHead_stu = pCur->pNext_student;
				if (NULL == pCur->pNext_student)
				{
					*ppTail_stu = NULL;
				}
			}
			else
			{
				pPre->pNext_student = pCur->pNext_student;
				if (NULL == pCur->pNext_student)
				{
					*ppTail_stu = pPre;
				}
			}
			free(pCur);
			pCur = *ppHead_stu;
			//开始重写文件
			fp_stu = fopen("information\\stu_inf.txt", "w+");
			while (pCur)
			{
				fprintf(fp_stu, "%d %s", pCur->student_id, pCur->student_name);
				for (i = 0; i < cou_num; ++i)
				{
					fprintf(fp_stu, " %lf", pCur->course_score[i]);
				}
				fprintf(fp_stu, "\n");
				pCur = pCur->pNext_student;
			}
			printf("\n删除学生信息成功！\n");
			fclose(fp_stu);
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供删除的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu21:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 4;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}
//42.按姓名删除学生信息
char Delete_pStudent_Information_By_name(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pStudent_Information_t pPre, pCur;
	FILE* fp_stu;
	char name[STUDENT_NAME_LENTH] = { 0 };
	int i;
	char menu_num;
	system("cls");
menu41:
	pCur = *ppHead_stu;
	pPre = NULL;
	printf(" \n");
	if (pCur)
	{
		printf("|------------- 删除学生信息 -------------|\n");
		printf("\n");
		printf("请输入要删除的姓名：");
		rewind(stdin);
		scanf("%s", name);
		while (pCur)
		{
			if (0 == strcmp(name, pCur->student_name))
			{
				break;
			}
			pPre = pCur;
			pCur = pCur->pNext_student;
		}
		if (NULL == pCur)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 姓名不匹配！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入姓名\n");
			goto menu41;
		}
		else
		{
			printf("\n  当前要删除的学生信息：\n");
			printf("      学号                姓名\n");
			printf("%10d%20s", pCur->student_id, pCur->student_name);
			printf("\n  确认删除？\n");
			printf("  1.确认\n");
			printf("  2.取消\n");
			printf("  3.直接返回上一级\n");
			printf("  4.直接返回主菜单\n");
		menu42:
			printf("\n");
			printf("  请输入菜单编号：");
			rewind(stdin);
			menu_num = getchar();
			rewind(stdin);
			switch (menu_num)
			{
			case '1':
				break;;
			case '2':
				goto menu41;
			case '3':
				return 4;
			case '4':
				return 14;
			default:
				Wrong_Menu_Num();
				goto menu42;
				break;
			}//switch
			//开始删除结点
			if (NULL == pPre)
			{
				*ppHead_stu = pCur->pNext_student;
				if (NULL == pCur->pNext_student)
				{
					*ppTail_stu = NULL;
				}
			}
			else
			{
				pPre->pNext_student = pCur->pNext_student;
				if (NULL == pCur->pNext_student)
				{
					*ppTail_stu = pPre;
				}
			}
			free(pCur);
			pCur = *ppHead_stu;
			//开始重写文件
			fp_stu = fopen("information\\stu_inf.txt", "w+");
			while (pCur)
			{
				fprintf(fp_stu, "%d %s", pCur->student_id, pCur->student_name);
				for (i = 0; i < cou_num; ++i)
				{
					fprintf(fp_stu, " %lf", pCur->course_score[i]);
				}
				fprintf(fp_stu, "\n");
				pCur = pCur->pNext_student;
			}
			printf("\n删除学生信息成功！\n");
			fclose(fp_stu);
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 提示 ** 当前没有可供删除的学生信息！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
	}
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
	printf("\n");
menu21:
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 4;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//管理员菜单5.查询账户
char Administrator_Menu_5()
{
	char menu_num;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------- 查询账户信息 -------------|\n");
	printf("|                                        |\n");
	printf("|              1.查询全部                |\n");
	printf("|              2.按账户名查询            |\n");
	printf("|              3.返回                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu1:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 51;
	case '2':
		return 52;
	case '3':
		return 14;
	default:
		Wrong_Menu_Num();
		goto menu1;
		break;
	}
}
//51.查询全部账户
char Print_User_Information(pUser_Information_t pHead_usr)
{
	pUser_Information_t pCur = pHead_usr;
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|---------------------------------- 全部账户信息 ----------------------------------|\n");
	printf("\n");
	printf("                            账户                            密码    管理员权限\n");
	while (pCur)
	{
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		pCur = pCur->pNext_user;
	}
	printf("\n");
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
menu11:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 5;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu11;
		break;
	}
}
//52.按账户名查询
char Search_User_Information_By_account(pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pUser_Information_t pCur;
	char menu_num;
	char account[USER_NAME_LENTH] = { 0 };
	system("cls");
menu52:
	pCur = pHead_usr;
	printf(" \n");
	printf("|---------------------------------- 查询账户信息 ----------------------------------|\n");
	printf("\n");
	printf("请输入账户名：");
	rewind(stdin);
	scanf("%s", account);
	while (pCur)
	{
		if (0 == strcmp(pCur->user_name, account))
		{
			break;
		}
		pCur = pCur->pNext_user;
	}
	if (NULL == pCur)
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 错误 ** 账户名不匹配！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("  请重新输入账户名\n");
		goto menu52;
	}
	else
	{
		printf(" \n");
		printf("                            账户                            密码    管理员权限\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
	}
	printf("\n");
	printf("	1.返回上一级\n");
	printf("	2.返回主菜单\n");
	printf("	3.退出程序\n");
menu11:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 5;
	case '2':
		return 14;
	case '3':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu11;
		break;
	}
}

//管理员菜单6.添加新账户
char Add_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pUser_Information_t pNew, pCur;
	FILE* fp_usr;
	int i;
	char menu_num;
	char acc[USER_NAME_LENTH] = { 0 }, psw[USER_NAME_LENTH] = { 0 };
	char admin = 'N';
	pNew = (pUser_Information_t)malloc(sizeof(User_Information_t));
	system("cls");
menu2:
	memset(pNew, 0, sizeof(User_Information_t));		//重置pnew
	memset(acc, 0, USER_NAME_LENTH);
	memset(psw, 0, USER_NAME_LENTH);
	pCur = *ppHead_usr;
	printf(" \n");
	printf("|---------------------------------- 添加账户信息 ----------------------------------|\n");
	printf("\n");
	printf("请依次输入账户名、密码、管理员权限（Y或N），以空格分隔：\n");
	rewind(stdin);
	if (scanf("%s %s %c", acc, psw, &admin) != 3 || acc[USER_NAME_LENTH - 1] != 0 || psw[USER_NAME_LENTH - 1] != 0 || (admin != 'Y' && admin != 'N'))
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 错误 ** 输入格式错误！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("  请重新输入\n");
		goto menu2;
	}
	while (pCur)
	{
		if (0 == strcmp(pCur->user_name, acc))
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 输入账户错误！已存在该账户\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入\n");
			goto menu2;
		}
		pCur = pCur->pNext_user;
	}
	strcpy(pNew->user_name, acc);
	strcpy(pNew->user_password, psw);
	pNew->user_is_administrator = admin;
	if (NULL == *ppHead_usr)
	{
		*ppHead_usr = pNew;
		*ppTail_usr = pNew;
	}
	else
	{
		(*ppTail_usr)->pNext_user = pNew;
		*ppTail_usr = pNew;
	}
	fp_usr = fopen("information\\usr_inf.txt", "a");
	fprintf(fp_usr, "%s %s %c\n", pNew->user_name, pNew->user_password, pNew->user_is_administrator);
	fclose(fp_usr);
	printf("\n 添加账户成功！\n");
	printf("	1.返回主菜单\n");
	printf("	2.退出程序\n");
menu21:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 14;
	case '2':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//管理员菜单7.修改账户信息
char Change_User_Information(pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pUser_Information_t pCur, pPre;
	FILE* fp_usr;
	char menu_num;
	char acc[USER_NAME_LENTH] = { 0 }, psw[USER_NAME_LENTH] = { 0 };
	char admin = 'N';
	system("cls");
menu52:
	pCur = pHead_usr;
	printf(" \n");
	printf("|---------------------------------- 修改账户 ----------------------------------|\n");
	printf("\n");
	printf("请输入要修改的账户名：");
	rewind(stdin);
	scanf("%s", acc);
	while (pCur)
	{
		if (0 == strcmp(pCur->user_name, acc))
		{
			break;
		}
		pCur = pCur->pNext_user;
	}
	if (NULL == pCur)
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 错误 ** 账户名不匹配！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("  请重新输入账户名\n");
		goto menu52;
	}
	else
	{
		printf("\n  当前要修改的账户信息：\n");
		printf(" \n");
		printf("                            账户                            密码    管理员权限\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		printf("\n  确认修改？\n");
		printf("  1.确认\n");
		printf("  2.取消\n");
		printf("  3.直接返回主菜单\n");
	menu42:
		printf("\n");
		printf("  请输入菜单编号：");
		rewind(stdin);
		menu_num = getchar();
		rewind(stdin);
		switch (menu_num)
		{
		case '1':
			break;
		case '2':
			goto menu52;
		case '3':
			return 14;
		default:
			Wrong_Menu_Num();
			goto menu42;
			break;
		}//switch
		//开始修改结点
		printf("\n");
	menu53:
		memset(acc, 0, USER_NAME_LENTH);
		memset(psw, 0, USER_NAME_LENTH);
		printf("请依次输入账户名、密码、管理员权限（Y或N），以空格分隔：\n");
		rewind(stdin);
		if (scanf("%s %s %c", acc, psw, &admin) != 3 || acc[USER_NAME_LENTH - 1] != 0 || psw[USER_NAME_LENTH - 1] != 0 || (admin != 'Y' && admin != 'N'))
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
			printf("  ** 错误 ** 输入格式错误！\n");
			SetConsoleTextAttribute(h, 0xf);	//白色
			printf("  请重新输入\n");
			goto menu53;
		}
		pPre = pHead_usr;
		while (pPre)
		{
			if (pPre != pCur && 0 == strcmp(pPre->user_name, acc))
			{
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
				printf("  ** 错误 ** 输入账户错误！已存在该账户\n");
				SetConsoleTextAttribute(h, 0xf);	//白色
				printf("  请重新输入\n");
				goto menu53;
			}
			pPre = pPre->pNext_user;
		}
		//开始修改结点
		strcpy(pCur->user_name, acc);
		strcpy(pCur->user_password, psw);
		pCur->user_is_administrator = admin;
		//开始重写文件
		fp_usr = fopen("information\\usr_inf.txt", "w+");
		pCur = pHead_usr;
		while (pCur)
		{
			fprintf(fp_usr, "%s %s %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
			pCur = pCur->pNext_user;
		}
		printf("\n修改账户信息成功！\n");
		fclose(fp_usr);
	}
	printf("	1.返回主菜单\n");
	printf("	2.退出程序\n");
menu21:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 14;
	case '2':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//管理员菜单8.删除账户
char Delete_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//辅助输出色彩
	pUser_Information_t pCur, pPre;
	FILE* fp_usr;
	char menu_num;
	char account[USER_NAME_LENTH] = { 0 };
	system("cls");
menu52:
	pCur = *ppHead_usr;
	pPre = NULL;
	printf(" \n");
	printf("|---------------------------------- 删除账户 ----------------------------------|\n");
	printf("\n");
	printf("请输入要删除的账户名：");
	rewind(stdin);
	scanf("%s", account);
	while (pCur)
	{
		if (0 == strcmp(pCur->user_name, account))
		{
			break;
		}
		pPre = pCur;
		pCur = pCur->pNext_user;
	}
	if (NULL == pCur)
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//红色
		printf("  ** 错误 ** 账户名不匹配！\n");
		SetConsoleTextAttribute(h, 0xf);	//白色
		printf("  请重新输入账户名\n");
		goto menu52;
	}
	else
	{
		printf("\n  当前要删除的账户信息：\n");
		printf(" \n");
		printf("                            账户                            密码    管理员权限\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		printf("\n  确认删除？\n");
		printf("  1.确认\n");
		printf("  2.取消\n");
		printf("  3.直接返回主菜单\n");
	menu42:
		printf("\n");
		printf("  请输入菜单编号：");
		rewind(stdin);
		menu_num = getchar();
		rewind(stdin);
		switch (menu_num)
		{
		case '1':
			break;
		case '2':
			goto menu52;
		case '3':
			return 14;
		default:
			Wrong_Menu_Num();
			goto menu42;
			break;
		}//switch
		//开始删除结点
		if (NULL == pPre)
		{
			*ppHead_usr = pCur->pNext_user;
			if (NULL == pCur->pNext_user)
			{
				*ppTail_usr = NULL;
			}
		}
		else
		{
			pPre->pNext_user = pCur->pNext_user;
			if (NULL == pCur->pNext_user)
			{
				*ppTail_usr = pPre;
			}
		}
		free(pCur);
		pCur = *ppHead_usr;
		//开始重写文件
		fp_usr = fopen("information\\usr_inf.txt", "w+");
		while (pCur)
		{
			fprintf(fp_usr, "%s %s %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
			pCur = pCur->pNext_user;
		}
		printf("\n删除账户信息成功！\n");
		fclose(fp_usr);
	}
	printf("	1.返回主菜单\n");
	printf("	2.退出程序\n");
menu21:
	printf("\n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	switch (menu_num)
	{
	case '1':
		return 14;
	case '2':
		return 9;
	default:
		Wrong_Menu_Num();
		goto menu21;
		break;
	}
}

//学生菜单
char Student_Menu()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- 查询学生信息 -------------|\n");
	printf("|                                        |\n");
	printf("|              1.按学号查询              |\n");
	printf("|              2.按姓名查询              |\n");
	printf("|              3.退出程序                |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu0:
	printf(" \n");
	printf("  请输入菜单编号：");
	rewind(stdin);
	menu_num = getchar();
	rewind(stdin);
	if (menu_num >= '1' && menu_num <= '3')
	{
		menu_num -= '0';
		menu_num++;
	}
	else
	{
		Wrong_Menu_Num();
		goto menu0;
	}
	return menu_num;
}