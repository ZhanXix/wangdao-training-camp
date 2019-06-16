#include "Student_Information_Management_System.h"

//���ļ�����û���ļ�����information�ļ����´����ļ�
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
		fprintf(*pfp_usr, "admin admin Y\n");		//��������Ա�û�
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

//������course���
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

//������student���
void Create_New_Student_Information_Node(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, char* stu_buf, int cou_num)
{
	int i = 0, j = 0, k = 0;
	int flag = 0;
	char score[20];
	pStudent_Information_t pNew;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	memset(pNew, 0, sizeof(Student_Information_t));
	sscanf(stu_buf, "%d%s", &pNew->student_id, &pNew->student_name);
	for (i = 0; stu_buf[i] != 0; ++i)	//����ɼ������⣬���ڿγ���Ŀ���������е��鷳
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

//������user���
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

//��¼
void Sign_In(pUser_Information_t pusr, pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pUser_Information_t pCur;
	char c;
	char psw[USER_NAME_LENTH];
	int i;

	/* ------ ��ʼ���� ------ */
sign_in:
	memset(pusr, 0, sizeof(User_Information_t));	//����pusr
	memset(psw, 0, sizeof(psw));		//��������
	pCur = pHead_usr;		//����ָ��
	i = 0;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------ ��¼ ------------|\n");
	printf("| \n");
	printf("| �û�����");
	gets(pusr->user_name, sizeof(pusr->user_name), stdin);
	if (pusr->user_name[USER_NAME_LENTH - 1] != 0)	//�û������ȳ���
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("** ���� ** �û���������\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("| ��Ҫ���µ�¼\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	else if (0 == pusr->user_name[0])	//δ�����û���
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("** ���� ** �������û�����\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("| ��Ҫ���µ�¼\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	rewind(stdin);
	printf("| ���룺");
	while ((c = getch()) != '\r')
	{
		if ('\b' == c)	//�����˸�
		{
			if (i > 0)	//֮ǰ���������
			{
				printf("\b \b");
				if (USER_NAME_LENTH - 1 >= i)
				{
					psw[i] = 0;
				}
				--i;
			}
			else//֮ǰ��û��������
			{
				continue;
			}
		}
		else//����س�֮��������ַ�-����������
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
	if (psw[USER_NAME_LENTH - 1] != 0)	//���볤�ȳ���
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("** ���� ** ���������\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("| ��Ҫ���µ�¼\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	else if (0 == psw[0])	//δ��������
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("** ���� ** ���������룡\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("| ��Ҫ���µ�¼\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
	strcpy(pusr->user_password, psw);
	/* ------ ������� ------ */

	/* ------ ��ʼƥ�� ------ */
	while (pCur)
	{
		if (0 == strcmp(pusr->user_name, pCur->user_name) && 0 == strcmp(pusr->user_password, pCur->user_password))
		{
			printf("| \n");
			printf("| ��¼�ɹ���\n");
			pusr->user_is_administrator = pCur->user_is_administrator;
			return;
		}
		pCur = pCur->pNext_user;
	}
	if (NULL == pCur)	//ƥ��ʧ��
	{
		printf("| \n");
		printf("| ");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("** ���� ** �û��������벻��ȷ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("| ��Ҫ���µ�¼\n");
		printf("| ");
		system("pause");
		goto sign_in;
	}
}

//�˵��������
void Wrong_Menu_Num()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	printf(" \n");
	SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
	printf("  ** ���� ** �˵��������\n");
	SetConsoleTextAttribute(h, 0xf);	//��ɫ
	printf("  ��Ҫ��������\n");
}

//����Ա�˵�
char Administrator_Menu()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------ ����Ա���ܲ˵� ------------|\n");
	printf("|                                        |\n");
	printf("|             1.��ѯѧ����Ϣ             |\n");
	printf("|             2.���ѧ����Ϣ             |\n");
	printf("|             3.�޸�ѧ����Ϣ             |\n");
	printf("|             4.ɾ��ѧ����Ϣ             |\n");
	printf("|             5.��ѯ�˻�                 |\n");
	printf("|             6.������˻�               |\n");
	printf("|             7.�޸��˻���Ϣ             |\n");
	printf("|             8.ɾ���˻�                 |\n");
	printf("|             9.�˳�ϵͳ                 |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu0:
	printf(" \n");
	printf("  ������˵���ţ�");
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

//����Ա�˵�1.��ѯѧ����Ϣ
char Administrator_Menu_1()
{
	char menu_num;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------- ��ѯѧ����Ϣ -------------|\n");
	printf("|                                        |\n");
	printf("|              1.��ѯȫ��                |\n");
	printf("|              2.��ѧ�Ų�ѯ              |\n");
	printf("|              3.��������ѯ              |\n");
	printf("|              4.����                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu1:
	printf(" \n");
	printf("  ������˵���ţ�");
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
//11.��ѯȫ��ѧ����Ϣ
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
		printf("|------------- ȫ��ѧ����Ϣ -------------|\n");
		printf("\n");
		printf("      ѧ��                ����");
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
		HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ���ѯ��ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
	printf("\n");
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
menu11:
	printf("\n");
	printf("  ������˵���ţ�");
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
//12.��ѧ�Ų�ѯѧ����Ϣ
char Search_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- ��ѯѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������ѧ�ţ�");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ѧ�Ų�ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������ѧ��\n");
			goto menu120;
		}
		else
		{
			printf(" \n");
			printf("      ѧ��                ����");
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
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ���ѯ��ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
	printf("\n");
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu12:
	printf("  ������˵���ţ�");
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
//13.��������ѯѧ����Ϣ
char Search_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- ��ѯѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������������");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ������ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ��������������\n");
			goto menu130;
		}
		else
		{
			printf(" \n");
			printf("      ѧ��                ����");
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
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ���ѯ��ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
	printf("\n");
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu13:
	printf("  ������˵���ţ�");
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

//����Ա�˵�2.���ѧ����Ϣ
char Add_pStudent_Information(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pStudent_Information_t pNew, pCur_stu;
	pCourse_Information_t pCur_cou;
	FILE* fp_stu;
	int i;
	char menu_num;
	pNew = (pStudent_Information_t)malloc(sizeof(Student_Information_t));
	system("cls");
menu2:
	memset(pNew, 0, sizeof(Student_Information_t));		//����pnew
	i = 0;
	pCur_cou = pHead_cou;
	pCur_stu = *ppHead_stu;
	printf("\n");
	printf("|------------- ���ѧ����Ϣ -------------|\n\n");
	printf(" �밴���¸�ʽ���ѧ��������Ϣ��\n");
	printf("ѧ��  ����\n");
	rewind(stdin);
	if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
	{
	error_menu2:
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ���� ** �����ʽ����\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("  ����������\n");
		goto menu2;
	}
	while (pCur_stu)
	{
		if (pCur_stu->student_id == pNew->student_id)
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ����ѧ�Ŵ����Ѵ��ڸ�ѧ��\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������\n");
			goto menu2;
		}
		pCur_stu = pCur_stu->pNext_student;
	}
	printf("\n ����������¸�ʽ���ѧ���γ̷�����\n");
	while (pCur_cou)
	{
		printf(" %s������", pCur_cou->course_name);
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
	printf("\n ���ѧ����Ϣ�ɹ���\n");
	printf("	1.�������˵�\n");
	printf("	2.�˳�����\n");
	printf("\n");
menu21:
	printf("  ������˵���ţ�");
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

//����Ա�˵�3.�޸�ѧ����Ϣ
char Administrator_Menu_3()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- �޸�ѧ����Ϣ -------------|\n");
	printf("|                                        |\n");
	printf("|              1.��ѧ���޸�              |\n");
	printf("|              2.�������޸�              |\n");
	printf("|              3.����                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu3:
	printf(" \n");
	printf("  ������˵���ţ�");
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
//31.��ѧ���޸�ѧ����Ϣ
char Change_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- �޸�ѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������ѧ�ţ�");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ѧ�Ų�ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������ѧ��\n");
			goto menu31;
		}
		else
		{
			printf("\n��ǰѧ����Ϣ��\n");
			printf("      ѧ��                ����");
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
			memset(pNew, 0, sizeof(Student_Information_t));		//����pnew
			pExam_stu = pHead_stu;
			pCur_cou = pHead_cou;
			printf("\n\n�밴���¸�ʽ�����޸ĺ��ѧ����Ϣ��\n");
			printf("ѧ�� ����\n");
			rewind(stdin);
			if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
			{
			error_menu2:
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
				printf("  ** ���� ** �����ʽ����\n");
				SetConsoleTextAttribute(h, 0xf);	//��ɫ
				printf("  ����������\n");
				goto menu2;
			}
			while (pExam_stu)
			{
				if (pExam_stu != pCur_stu && pExam_stu->student_id == pNew->student_id)
				{
					printf(" \n");
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
					printf("  ** ���� ** ����ѧ�Ŵ����Ѵ��ڸ�ѧ��\n");
					SetConsoleTextAttribute(h, 0xf);	//��ɫ
					printf("  ����������\n");
					goto menu2;
				}
				pExam_stu = pExam_stu->pNext_student;
			}
			printf("\n ����������¸�ʽ�޸�ѧ���γ̷�����\n");
			i = 0;
			while (pCur_cou)
			{
				printf(" %s������", pCur_cou->course_name);
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
			//����޸����
			//��ʼ��д�ļ�
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
			printf("\n�޸�ѧ����Ϣ�ɹ���\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ��޸ĵ�ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
menu20:
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu21:
	printf("  ������˵���ţ�");
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
//32.�������޸�ѧ����Ϣ
char Change_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- �޸�ѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������������");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ������ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ��������������\n");
			goto menu31;
		}
		else
		{
			printf("\n��ǰѧ����Ϣ��\n");
			printf("      ѧ��                ����");
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
			memset(pNew, 0, sizeof(Student_Information_t));		//����pnew
			pExam_stu = pHead_stu;
			pCur_cou = pHead_cou;
			printf("\n\n�밴���¸�ʽ�����޸ĺ��ѧ����Ϣ��\n");
			printf("ѧ�� ����\n");
			rewind(stdin);
			if (scanf("%d%s", &pNew->student_id, pNew->student_name) != 2)
			{
			error_menu2:
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
				printf("  ** ���� ** �����ʽ����\n");
				SetConsoleTextAttribute(h, 0xf);	//��ɫ
				printf("  ����������\n");
				goto menu2;
			}
			while (pExam_stu)
			{
				if (pExam_stu != pCur_stu && pExam_stu->student_id == pNew->student_id)
				{
					printf(" \n");
					SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
					printf("  ** ���� ** ����ѧ�Ŵ����Ѵ��ڸ�ѧ��\n");
					SetConsoleTextAttribute(h, 0xf);	//��ɫ
					printf("  ����������\n");
					goto menu2;
				}
				pExam_stu = pExam_stu->pNext_student;
			}
			printf("\n ����������¸�ʽ�޸�ѧ���γ̷�����\n");
			i = 0;
			while (pCur_cou)
			{
				printf(" %s������", pCur_cou->course_name);
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
			//����޸����
			//��ʼ��д�ļ�
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
			printf("\n�޸�ѧ����Ϣ�ɹ���\n");
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ��޸ĵ�ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
menu20:
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu21:
	printf("  ������˵���ţ�");
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

//����Ա�˵�4.ɾ��ѧ����Ϣ
char Administrator_Menu_4()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- ɾ��ѧ����Ϣ -------------|\n");
	printf("|                                        |\n");
	printf("|              1.��ѧ��ɾ��              |\n");
	printf("|              2.������ɾ��              |\n");
	printf("|              3.����                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu3:
	printf(" \n");
	printf("  ������˵���ţ�");
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
//41.��ѧ��ɾ��ѧ����Ϣ
char Delete_pStudent_Information_By_id(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- ɾ��ѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������Ҫɾ����ѧ�ţ�");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ѧ�Ų�ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������ѧ��\n");
			goto menu41;
		}
		else
		{
			printf("\n  ��ǰҪɾ����ѧ����Ϣ��\n");
			printf("      ѧ��                ����\n");
			printf("%10d%20s", pCur->student_id, pCur->student_name);
			printf("\n  ȷ��ɾ����\n");
			printf("  1.ȷ��\n");
			printf("  2.ȡ��\n");
			printf("  3.ֱ�ӷ�����һ��\n");
			printf("  4.ֱ�ӷ������˵�\n");
		menu42:
			printf("\n");
			printf("  ������˵���ţ�");
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
			//��ʼɾ�����
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
			//��ʼ��д�ļ�
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
			printf("\nɾ��ѧ����Ϣ�ɹ���\n");
			fclose(fp_stu);
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ�ɾ����ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu21:
	printf("  ������˵���ţ�");
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
//42.������ɾ��ѧ����Ϣ
char Delete_pStudent_Information_By_name(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
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
		printf("|------------- ɾ��ѧ����Ϣ -------------|\n");
		printf("\n");
		printf("������Ҫɾ����������");
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
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** ������ƥ�䣡\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ��������������\n");
			goto menu41;
		}
		else
		{
			printf("\n  ��ǰҪɾ����ѧ����Ϣ��\n");
			printf("      ѧ��                ����\n");
			printf("%10d%20s", pCur->student_id, pCur->student_name);
			printf("\n  ȷ��ɾ����\n");
			printf("  1.ȷ��\n");
			printf("  2.ȡ��\n");
			printf("  3.ֱ�ӷ�����һ��\n");
			printf("  4.ֱ�ӷ������˵�\n");
		menu42:
			printf("\n");
			printf("  ������˵���ţ�");
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
			//��ʼɾ�����
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
			//��ʼ��д�ļ�
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
			printf("\nɾ��ѧ����Ϣ�ɹ���\n");
			fclose(fp_stu);
		}
	}
	else
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ��ʾ ** ��ǰû�пɹ�ɾ����ѧ����Ϣ��\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
	}
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
	printf("\n");
menu21:
	printf("  ������˵���ţ�");
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

//����Ա�˵�5.��ѯ�˻�
char Administrator_Menu_5()
{
	char menu_num;
	system("cls");
	rewind(stdin);
	printf(" \n");
	printf("|------------- ��ѯ�˻���Ϣ -------------|\n");
	printf("|                                        |\n");
	printf("|              1.��ѯȫ��                |\n");
	printf("|              2.���˻�����ѯ            |\n");
	printf("|              3.����                    |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu1:
	printf(" \n");
	printf("  ������˵���ţ�");
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
//51.��ѯȫ���˻�
char Print_User_Information(pUser_Information_t pHead_usr)
{
	pUser_Information_t pCur = pHead_usr;
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|---------------------------------- ȫ���˻���Ϣ ----------------------------------|\n");
	printf("\n");
	printf("                            �˻�                            ����    ����ԱȨ��\n");
	while (pCur)
	{
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		pCur = pCur->pNext_user;
	}
	printf("\n");
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
menu11:
	printf("\n");
	printf("  ������˵���ţ�");
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
//52.���˻�����ѯ
char Search_User_Information_By_account(pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pUser_Information_t pCur;
	char menu_num;
	char account[USER_NAME_LENTH] = { 0 };
	system("cls");
menu52:
	pCur = pHead_usr;
	printf(" \n");
	printf("|---------------------------------- ��ѯ�˻���Ϣ ----------------------------------|\n");
	printf("\n");
	printf("�������˻�����");
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
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ���� ** �˻�����ƥ�䣡\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("  �����������˻���\n");
		goto menu52;
	}
	else
	{
		printf(" \n");
		printf("                            �˻�                            ����    ����ԱȨ��\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
	}
	printf("\n");
	printf("	1.������һ��\n");
	printf("	2.�������˵�\n");
	printf("	3.�˳�����\n");
menu11:
	printf("\n");
	printf("  ������˵���ţ�");
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

//����Ա�˵�6.������˻�
char Add_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pUser_Information_t pNew, pCur;
	FILE* fp_usr;
	int i;
	char menu_num;
	char acc[USER_NAME_LENTH] = { 0 }, psw[USER_NAME_LENTH] = { 0 };
	char admin = 'N';
	pNew = (pUser_Information_t)malloc(sizeof(User_Information_t));
	system("cls");
menu2:
	memset(pNew, 0, sizeof(User_Information_t));		//����pnew
	memset(acc, 0, USER_NAME_LENTH);
	memset(psw, 0, USER_NAME_LENTH);
	pCur = *ppHead_usr;
	printf(" \n");
	printf("|---------------------------------- ����˻���Ϣ ----------------------------------|\n");
	printf("\n");
	printf("�����������˻��������롢����ԱȨ�ޣ�Y��N�����Կո�ָ���\n");
	rewind(stdin);
	if (scanf("%s %s %c", acc, psw, &admin) != 3 || acc[USER_NAME_LENTH - 1] != 0 || psw[USER_NAME_LENTH - 1] != 0 || (admin != 'Y' && admin != 'N'))
	{
		printf(" \n");
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ���� ** �����ʽ����\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("  ����������\n");
		goto menu2;
	}
	while (pCur)
	{
		if (0 == strcmp(pCur->user_name, acc))
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** �����˻������Ѵ��ڸ��˻�\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������\n");
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
	printf("\n ����˻��ɹ���\n");
	printf("	1.�������˵�\n");
	printf("	2.�˳�����\n");
menu21:
	printf("\n");
	printf("  ������˵���ţ�");
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

//����Ա�˵�7.�޸��˻���Ϣ
char Change_User_Information(pUser_Information_t pHead_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pUser_Information_t pCur, pPre;
	FILE* fp_usr;
	char menu_num;
	char acc[USER_NAME_LENTH] = { 0 }, psw[USER_NAME_LENTH] = { 0 };
	char admin = 'N';
	system("cls");
menu52:
	pCur = pHead_usr;
	printf(" \n");
	printf("|---------------------------------- �޸��˻� ----------------------------------|\n");
	printf("\n");
	printf("������Ҫ�޸ĵ��˻�����");
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
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ���� ** �˻�����ƥ�䣡\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("  �����������˻���\n");
		goto menu52;
	}
	else
	{
		printf("\n  ��ǰҪ�޸ĵ��˻���Ϣ��\n");
		printf(" \n");
		printf("                            �˻�                            ����    ����ԱȨ��\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		printf("\n  ȷ���޸ģ�\n");
		printf("  1.ȷ��\n");
		printf("  2.ȡ��\n");
		printf("  3.ֱ�ӷ������˵�\n");
	menu42:
		printf("\n");
		printf("  ������˵���ţ�");
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
		//��ʼ�޸Ľ��
		printf("\n");
	menu53:
		memset(acc, 0, USER_NAME_LENTH);
		memset(psw, 0, USER_NAME_LENTH);
		printf("�����������˻��������롢����ԱȨ�ޣ�Y��N�����Կո�ָ���\n");
		rewind(stdin);
		if (scanf("%s %s %c", acc, psw, &admin) != 3 || acc[USER_NAME_LENTH - 1] != 0 || psw[USER_NAME_LENTH - 1] != 0 || (admin != 'Y' && admin != 'N'))
		{
			printf(" \n");
			SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
			printf("  ** ���� ** �����ʽ����\n");
			SetConsoleTextAttribute(h, 0xf);	//��ɫ
			printf("  ����������\n");
			goto menu53;
		}
		pPre = pHead_usr;
		while (pPre)
		{
			if (pPre != pCur && 0 == strcmp(pPre->user_name, acc))
			{
				printf(" \n");
				SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
				printf("  ** ���� ** �����˻������Ѵ��ڸ��˻�\n");
				SetConsoleTextAttribute(h, 0xf);	//��ɫ
				printf("  ����������\n");
				goto menu53;
			}
			pPre = pPre->pNext_user;
		}
		//��ʼ�޸Ľ��
		strcpy(pCur->user_name, acc);
		strcpy(pCur->user_password, psw);
		pCur->user_is_administrator = admin;
		//��ʼ��д�ļ�
		fp_usr = fopen("information\\usr_inf.txt", "w+");
		pCur = pHead_usr;
		while (pCur)
		{
			fprintf(fp_usr, "%s %s %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
			pCur = pCur->pNext_user;
		}
		printf("\n�޸��˻���Ϣ�ɹ���\n");
		fclose(fp_usr);
	}
	printf("	1.�������˵�\n");
	printf("	2.�˳�����\n");
menu21:
	printf("\n");
	printf("  ������˵���ţ�");
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

//����Ա�˵�8.ɾ���˻�
char Delete_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	pUser_Information_t pCur, pPre;
	FILE* fp_usr;
	char menu_num;
	char account[USER_NAME_LENTH] = { 0 };
	system("cls");
menu52:
	pCur = *ppHead_usr;
	pPre = NULL;
	printf(" \n");
	printf("|---------------------------------- ɾ���˻� ----------------------------------|\n");
	printf("\n");
	printf("������Ҫɾ�����˻�����");
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
		SetConsoleTextAttribute(h, FOREGROUND_RED | FOREGROUND_INTENSITY);	//��ɫ
		printf("  ** ���� ** �˻�����ƥ�䣡\n");
		SetConsoleTextAttribute(h, 0xf);	//��ɫ
		printf("  �����������˻���\n");
		goto menu52;
	}
	else
	{
		printf("\n  ��ǰҪɾ�����˻���Ϣ��\n");
		printf(" \n");
		printf("                            �˻�                            ����    ����ԱȨ��\n");
		printf("%32s%32s            %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
		printf("\n  ȷ��ɾ����\n");
		printf("  1.ȷ��\n");
		printf("  2.ȡ��\n");
		printf("  3.ֱ�ӷ������˵�\n");
	menu42:
		printf("\n");
		printf("  ������˵���ţ�");
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
		//��ʼɾ�����
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
		//��ʼ��д�ļ�
		fp_usr = fopen("information\\usr_inf.txt", "w+");
		while (pCur)
		{
			fprintf(fp_usr, "%s %s %c\n", pCur->user_name, pCur->user_password, pCur->user_is_administrator);
			pCur = pCur->pNext_user;
		}
		printf("\nɾ���˻���Ϣ�ɹ���\n");
		fclose(fp_usr);
	}
	printf("	1.�������˵�\n");
	printf("	2.�˳�����\n");
menu21:
	printf("\n");
	printf("  ������˵���ţ�");
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

//ѧ���˵�
char Student_Menu()
{
	char menu_num;
	system("cls");
	printf(" \n");
	printf("|------------- ��ѯѧ����Ϣ -------------|\n");
	printf("|                                        |\n");
	printf("|              1.��ѧ�Ų�ѯ              |\n");
	printf("|              2.��������ѯ              |\n");
	printf("|              3.�˳�����                |\n");
	printf("|                                        |\n");
	printf("|----------------------------------------|\n");
menu0:
	printf(" \n");
	printf("  ������˵���ţ�");
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