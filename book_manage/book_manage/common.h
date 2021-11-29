#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
#define BOOK_TYPE 0
#define STUDENT_TYPE 1
#define BORROWING_RECORDS_TYPE 2

//��������: ������ָ��λ��ֱ�Ӳ����ļ�
//�������: ����Ҫ�����ļ���������ݶ�ȡ������һ���ļ���,������ɺ������½��ļ�����д��
//ȱ��: ���д���������ݹ��������������

//�����������
//���������ļ��ķ�ʽ����ά���ļ�
//ͼ�����ϵͳ��Ҫ��Ϣ,��ǰ�����浽��һ���ļ������������ļ�config
struct book_manage
{
    /* data */
    int type; //����0ͼ����Ϣ��1ѧ����Ϣ��2������Ϣ
	int end_position; //����λ��
	struct book_manage *next;
};

//ͼ����Ϣ
struct book
{
    /* data */
    char no[5]; //���
	char book_name[128]; //����
    char author[20]; //����
    int reserve; //���
    struct book *next;
};
//ѧ����Ϣ
struct student_info
{
    /* data */
    char id[11]; //ѧ��
    char name[20]; //����
    char class_name[128]; //�༶
    struct student_info *next;
};
//���ļ�¼
struct borrowing_records 
{
    /* data */
    char student_id[11];
    char no[5];
    struct borrowing_records *next;
};


void menu();
/*
* ��ӡ������Ϣ
* @param file_path �����ļ���·��
* @param config_path �����ļ�·��
* @param operate_type �������� 0 �鼮,1ѧ����2������Ϣ
*/
int printf_file(char *file_path,char *config_path,int operate_type);

int find_student_file(char *file_path,char *config_path,char *des,struct student_info* su_info);

int find_book_file(char *file_path,char *config_path,char *des,struct book* book);

int find_borrowing_records_file(char *file_path,char *config_path,struct borrowing_records *input_br,struct borrowing_records* br);

/**
 * ���ļ��ж�ȡͼ���б�������ն�
 * @param file_paht �ļ�λ��
 * @param config_path �����ļ�·��
 */
void printf_book(char *file_path,char *config_path);
/**
 * ���ļ��ж�ȡѧ���б�������ն�
 * @param file_paht �ļ�λ��
 * @param config_path �����ļ�·��
 */
void printf_student(char *file_path,char *config_path);

//��ӡ������Ϣ
void printf_config_info(char *config_path);

//���ļ�¼
void printf_borrowing_records(char *file_path,char *config_path);