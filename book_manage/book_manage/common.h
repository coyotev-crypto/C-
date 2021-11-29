#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define BOOK_TYPE 0
#define STUDENT_TYPE 1
#define BORROWING_RECORDS_TYPE 2

//存在问题: 不能在指定位置直接插入文件
//解决方案: 将需要插入文件后面的数据读取到另外一个文件中,插入完成后在重新将文件重新写入
//缺陷: 如果写入后面的内容过多存在性能问题

//解决方案二：
//采用配置文件的方式进行维护文件
//图书管理系统主要信息,当前链表保存到另一个文件，当作配置文件config
struct book_manage
{
    /* data */
    int type; //类型0图书信息，1学生信息，2借阅信息
	int end_position; //结束位置
	struct book_manage *next;
};

//图书信息
struct book
{
    /* data */
    char no[5]; //编号
	char book_name[128]; //书名
    char author[20]; //作者
    int reserve; //库存
    struct book *next;
};
//学生信息
struct student_info
{
    /* data */
    char id[11]; //学号
    char name[20]; //姓名
    char class_name[128]; //班级
    struct student_info *next;
};
//借阅记录
struct borrowing_records 
{
    /* data */
    char student_id[11];
    char no[5];
    struct borrowing_records *next;
};


void menu();
/*
* 打印数据信息
* @param file_path 查找文件的路径
* @param config_path 配置文件路径
* @param operate_type 操作类型 0 书籍,1学生，2借阅信息
*/
int printf_file(char *file_path,char *config_path,int operate_type);

int find_student_file(char *file_path,char *config_path,char *des,struct student_info* su_info);

int find_book_file(char *file_path,char *config_path,char *des,struct book* book);

int find_borrowing_records_file(char *file_path,char *config_path,struct borrowing_records *input_br,struct borrowing_records* br);

/**
 * 从文件中读取图书列表并输出到终端
 * @param file_paht 文件位置
 * @param config_path 配置文件路径
 */
void printf_book(char *file_path,char *config_path);
/**
 * 从文件中读取学生列表并输出到终端
 * @param file_paht 文件位置
 * @param config_path 配置文件路径
 */
void printf_student(char *file_path,char *config_path);

//打印配置信息
void printf_config_info(char *config_path);

//借阅记录
void printf_borrowing_records(char *file_path,char *config_path);