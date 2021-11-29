#include "student_manage.h"
#include "book_manage.h"
#include "common.h"

void input_books(struct book* head,char *file_paht,char *config_path);
void input_students(struct student_info* head,char *file_path,char *config_path);

int main(int argc,char *argv[]){
	
	int cmd = 1;
	char file_path[] = "图书管理.dat";
	char config_path[] = "图书管理.config";
	struct book *book_head = NULL;
	struct book_manage *m_head = NULL;
	struct student_info *su_head = NULL;
	book_head = (struct book*)malloc(sizeof(struct book));
	m_head = (struct book_manage*)malloc(sizeof(struct book_manage));
	su_head = (struct student_info*)malloc(sizeof(struct student_info));
	book_head->next=NULL;
	m_head->next=NULL;
	su_head->next=NULL;
    menu();
	while(cmd){
		printf("请输入（0~9）：");
		scanf("%d",&cmd);
		switch(cmd){
			case 1:
				input_books(book_head,file_path,config_path);
				break;
			case 2:
				input_students(su_head,file_path,config_path);
				break;
			case 3:
				printf_book(file_path,config_path);
				break;
			case 4:
				printf_student(file_path,config_path);
				break;
			case 5:
				borrow_books(file_path,config_path);
				break;
			case 6:
			    return_the_book(file_path,config_path);
				break;
			case 7:
				printf_borrowing_records(file_path,config_path);
				break;
			default:
				exit(1);
				break;
		}
	}
    return 0;
}


/**
* 录入书籍信息
*/
void input_books(struct book* head,char *file_path,char *config_path){
	char ch;
	while(1){
		input_book(head,file_path,config_path);
		printf("是否继续录入（Y/N）：");
		//无缓存区，有回显
		ch = getche();
		printf("\n");
		if(ch != 'Y'){
			//将当前链表写入文件
			write_book(head,file_path);
			//写入配置文件
			write_manage_info(BOOK_TYPE,get_book_list_size(head),config_path);
			//printf_config_info(config_path);
			//清空当前链表
			clear_book_list(head);
			break;
		}
	}
}

/*
* 录入学生信息
*/
void input_students(struct student_info* head,char *file_path,char *config_path){
	char ch;
	while(1){
		input_student(head,file_path,config_path);
		printf("是否继续录入（Y/N）：");
		//无缓存区，有回显
		ch = getche();
		printf("\n");
		if(ch != 'Y'){
			//将当前链表写入文件
			write_student(head,file_path);
			//写入配置文件
			write_manage_info(STUDENT_TYPE,get_student_list_size(head),config_path);
			//printf_config_info(config_path);
			//清空当前链表
			clear_student_list(head);
			break;
		}
	}
}