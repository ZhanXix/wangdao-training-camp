/*
 * 学生管理系统
 * V1.0
 * by ChengXuan 2019/6/15
 * 暂时没有写configure.txt文件，直接把文件放在了"当前路径\information\"下
 * 支持中文姓名
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <conio.h>

#define STUDENT_NAME_LENTH	24
#define USER_NAME_LENTH		32
#define COURSE_NUMBER		10		//课程的最大数量：暂定为10
#define COURSE_NAME_LENTH	32

 /* ------ 结构体定义 ------ */
typedef struct student_information	//学生的信息
{
	int student_id;					//学号
	char student_name[STUDENT_NAME_LENTH];	//姓名
	double course_score[COURSE_NUMBER];		//课程分数
	struct student_information* pNext_student;	//下一个学生信息
}Student_Information_t, * pStudent_Information_t;

typedef struct user_information		//用户账户信息
{
	char user_name[USER_NAME_LENTH];		//用户名
	char user_password[USER_NAME_LENTH];	//密码
	char user_is_administrator;		//为'N'表示是学生，为'Y'表示是管理员
	struct user_information* pNext_user;
}User_Information_t, * pUser_Information_t;

typedef struct course_information		//课程信息
{
	int course_id;						 //课程编号
	char course_name[COURSE_NAME_LENTH]; //课程名
	struct course_information* pNext_course;
}Course_Information_t, * pCourse_Information_t;


/* ------ 函数声明 ------ */
/* 初始化 */
//打开文件，若没有文件即在information文件夹下创建文件
void Init_Student_Information_Management_System(FILE** pfp_stu, FILE** pfp_usr, FILE** pfp_cou);
//创建新course结点
void Create_New_Course_Information_Node(pCourse_Information_t* pHead_cou, pCourse_Information_t* pTail_cou, pCourse_Information_t pcou);
//创建新student结点
void Create_New_Student_Information_Node(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, char* stu_buf, int cou_num);
//创建新user结点
void Create_New_User_Information_Node(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr, pUser_Information_t pusr);
/* 登录 */
void Sign_In(pUser_Information_t pusr, pUser_Information_t pHead_usr);

/* 菜单 */
//菜单输入错误
void Wrong_Menu_Num();
/* 管理员 */
//0.管理员总菜单
char Administrator_Menu();
//1.查询学生信息
char Administrator_Menu_1();
//11.查询全部学生信息
char Print_pStudent_Information(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//12.按学号查询学生信息
char Search_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//13.按姓名查询学生信息
char Search_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//2.添加学生信息
char Add_pStudent_Information(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, pCourse_Information_t pHead_cou, int cou_num);
//3.修改学生信息
char Administrator_Menu_3();
//31.按学号修改学生信息
char Change_pStudent_Information_By_id(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//32.按姓名修改学生信息
char Change_pStudent_Information_By_name(pStudent_Information_t pHead_stu, pCourse_Information_t pHead_cou, int cou_num);
//4.删除学生信息
char Administrator_Menu_4();
//41.按学号删除学生信息
char Delete_pStudent_Information_By_id(pStudent_Information_t* ppHead_stu, pStudent_Information_t* ppTail_stu, int cou_num);
//5.查询账户
char Administrator_Menu_5();
//51.查询全部账户
char Print_User_Information(pUser_Information_t pHead_usr);
//52.按账户名查询
char Search_User_Information_By_account(pUser_Information_t pHead_usr);
//6.添加新账户
char Add_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr);
//7.修改账户信息
char Change_User_Information(pUser_Information_t pHead_usr);
//8.删除账户
char Delete_User_Information(pUser_Information_t* ppHead_usr, pUser_Information_t* ppTail_usr);
/*学生*/
//学生总菜单
char Student_Menu();