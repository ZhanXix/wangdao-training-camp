#include "Student_Information_Management_System.h"

int main()
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);	//�������ɫ��
	char stu_buf[sizeof(Student_Information_t)];
	pStudent_Information_t pHead_stu = NULL, pTail_stu = NULL;
	pUser_Information_t pusr;
	pUser_Information_t pHead_usr = NULL, pTail_usr = NULL;
	pCourse_Information_t pcou;
	pCourse_Information_t pHead_cou = NULL, pTail_cou = NULL;
	int cou_num = 0;	//�γ�����
	char menu_flag = 0;
	FILE* fp_stu, * fp_usr, * fp_cou;

	/* ------ ��ʼ�� ------ */
	SetConsoleTextAttribute(h, 0xf);	//��ɫ
	Init_Student_Information_Management_System(&fp_stu, &fp_usr, &fp_cou);  //���ļ�����û���ļ�����information�ļ����´����ļ�
	pcou = (pCourse_Information_t)malloc(sizeof(Course_Information_t));
	pusr = (pUser_Information_t)malloc(sizeof(User_Information_t));
	while (memset(pcou, 0, sizeof(Course_Information_t)), fscanf(fp_cou, "%d%s", &pcou->course_id, &pcou->course_name) != EOF)
	{
		Create_New_Course_Information_Node(&pHead_cou, &pTail_cou, pcou);
		++cou_num;
		if (cou_num > COURSE_NUMBER)
		{
			printf("���󣺿γ��������ޣ�\n");
			goto end;
		}
	}
	while (memset(stu_buf, 0, sizeof(stu_buf)), (fgets(stu_buf, sizeof(stu_buf), fp_stu)) != NULL)
	{
		Create_New_Student_Information_Node(&pHead_stu, &pTail_stu, stu_buf, cou_num);
	}
	while (memset(pusr, 0, sizeof(User_Information_t)), fscanf(fp_usr, "%s%s %c", &pusr->user_name, &pusr->user_password, &pusr->user_is_administrator) != EOF)
	{
		Create_New_User_Information_Node(&pHead_usr, &pTail_usr, pusr);
	}
	fclose(fp_stu);
	fclose(fp_usr);
	fclose(fp_cou);
	/* ------ ��ʼ����� ------ */

	/* ------ ��¼ ------ */
	Sign_In(pusr, pHead_usr);
	printf("| ");
	system("pause");
	/* ------ ��¼��� ------ */

	/* ------ �˵� ------ */
	while ('Y' == pusr->user_is_administrator)	//����Ա�û�
	{
		switch (menu_flag)
		{
		case 0:
			menu_flag = Administrator_Menu();
			break;
		case 1:
			menu_flag = Administrator_Menu_1();
			break;
		case 11:
			menu_flag = Print_pStudent_Information(pHead_stu, pHead_cou, cou_num);
			break;
		case 12:
			menu_flag = Search_pStudent_Information_By_id(pHead_stu, pHead_cou, cou_num);
			break;
		case 13:
			menu_flag = Search_pStudent_Information_By_name(pHead_stu, pHead_cou, cou_num);
			break;
		case 14:
			menu_flag = 0;
			break;
		case 2:
			menu_flag = Add_pStudent_Information(&pHead_stu, &pTail_stu, pHead_cou, cou_num);
			break;
		case 3:
			menu_flag = Administrator_Menu_3();
			break;
		case 31:
			menu_flag = Change_pStudent_Information_By_id(pHead_stu, pHead_cou, cou_num);
			break;
		case 32:
			menu_flag = Change_pStudent_Information_By_name(pHead_stu, pHead_cou, cou_num);
			break;
		case 4:
			menu_flag = Administrator_Menu_4();
			break;
		case 41:
			menu_flag = Delete_pStudent_Information_By_id(&pHead_stu, &pTail_stu, cou_num);
			break;
		case 42:
			menu_flag = Delete_pStudent_Information_By_name(&pHead_stu, &pTail_stu, cou_num);
			break;
		case 5:
			menu_flag = Administrator_Menu_5();
			break;
		case 51:
			menu_flag = Print_User_Information(pHead_usr);
			break;
		case 52:
			menu_flag = Search_User_Information_By_account(pHead_usr);
			break;
		case 6:
			menu_flag = Add_User_Information(&pHead_usr, &pTail_usr);
			break;
		case 7:
			menu_flag = Change_User_Information(pHead_usr);
			break;
		case 8:
			menu_flag = Delete_User_Information(&pHead_usr, &pTail_usr);
			break;
		case 9:
			return 0;	//�˳�����
		default:
			printf("ERROR in menu flag\n");
			menu_flag = 0;
			break;
		}
	}
	while ('N' == pusr->user_is_administrator)
	{
		switch (menu_flag) {
		case 0:
		case 1:
		case 14:
			menu_flag = Student_Menu();
			break;
		case 2:
			menu_flag = Search_pStudent_Information_By_id(pHead_stu, pHead_cou, cou_num);
			break;
		case 3:
			menu_flag = Search_pStudent_Information_By_name(pHead_stu, pHead_cou, cou_num);
			break;
		case 4:
			return 0;	//�˳�����
		default:
			printf("ERROR in menu flag\n");
			menu_flag = 0;
			break;
		}
	}
	/* ------ �˵����� ------ */

	/* ------ ������� ------ */
end:
	system("pause");
}