/*
 * ѧ������ϵͳ
 * V1.0
 * by ChengXuan 2019/6/15
 * ��ʱû��дconfigure.txt�ļ���ֱ�Ӱ��ļ�������"��ǰ·��\information\"��
 * ֧����������
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define STUDENT_NAME_LENTH	24
#define USER_NAME_LENTH		32
#define COURSE_NUMBER		10		//�γ̵�����������ݶ�Ϊ10
#define COURSE_NAME_LENTH	32

 /* ------ �ṹ�嶨�� ------ */
typedef struct student_information	//ѧ������Ϣ
{
	int student_id;					//ѧ��
	char student_name[STUDENT_NAME_LENTH];	//����
	double course_score[COURSE_NUMBER];		//�γ̷���
	struct student_information* pNext_student;	//��һ��ѧ����Ϣ
}Student_Information_t, * pStudent_Information_t;

typedef struct user_information		//�û��˻���Ϣ
{
	char user_name[USER_NAME_LENTH];		//�û���
	char user_password[USER_NAME_LENTH];	//����
	char user_is_administrator;		//Ϊ'N'��ʾ��ѧ����Ϊ'Y'��ʾ�ǹ���Ա
	struct user_information* pNext_user;
}User_Information_t, * pUser_Information_t;

typedef struct course_information		//�γ���Ϣ
{
	int course_id;						 //�γ̱��
	char course_name[COURSE_NAME_LENTH]; //�γ���
	struct course_information* pNext_course;
}Course_Information_t, * pCourse_Information_t;


/* ------ �������� ------ */
/* ��ʼ�� */
//���ļ�����û���ļ�����information�ļ����´����ļ�
void Init_Student_Information_Management_System(FILE** pfp_stu, FILE** pfp_usr, FILE** pfp_cou);
//������course���
void Create_New_Course_Information_Node(pCourse_Information_t* pHead_cou, pCourse_Information_t* pTail_cou, pCourse_Information_t pcou);
//������student���
void Create_New_Student_Information_Node(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, char* stu_buf, int cou_num);
//������user���
void Create_New_User_Information_Node(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr, pUser_Information_t pusr);
/* ��¼ */
void Sign_In(pUser_Information_t pusr, pUser_Information_t pHead_usr);

/* �˵� */
//�˵��������
void Wrong_Menu_Num();
/* ����Ա */
//0.����Ա�ܲ˵�
char Administrator_Menu();
//1.��ѯѧ����Ϣ
char Administrator_Menu_1();
//11.��ѯȫ��ѧ����Ϣ
char Print_pStudent_Information(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//12.��ѧ�Ų�ѯѧ����Ϣ
char Search_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//13.��������ѯѧ����Ϣ
char Search_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//2.���ѧ����Ϣ
char Add_pStudent_Information(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, pCourse_Information_t pHead_cou, int cou_num);
//3.�޸�ѧ����Ϣ
char Administrator_Menu_3();
//31.��ѧ���޸�ѧ����Ϣ
char Change_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//32.�������޸�ѧ����Ϣ
char Change_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//4.ɾ��ѧ����Ϣ
char Administrator_Menu_4();
//41.��ѧ��ɾ��ѧ����Ϣ
char Delete_pStudent_Information_By_id(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num);
//5.��ѯ�˻�
char Administrator_Menu_5();
//51.��ѯȫ���˻�
char Print_User_Information(pUser_Information_t pHead_usr);
//52.���˻�����ѯ
char Search_User_Information_By_account(pUser_Information_t pHead_usr);
//6.������˻�
char Add_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr);
//7.�޸��˻���Ϣ
char Change_User_Information(pUser_Information_t pHead_usr);
//8.ɾ���˻�
char Delete_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr);
/*ѧ��*/
//ѧ���ܲ˵�
char Student_Menu();