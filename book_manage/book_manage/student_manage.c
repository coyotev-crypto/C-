/*
* 学生信息管理
*/
#include "student_manage.h"
#include "common.h"

struct student_info* init_student_info(){
    struct student_info *head;
    head = (struct student_info*)malloc(sizeof(struct student_info));
    head->next = NULL;
    return head;
}

/**
 * 创建学生链表
 * 校验是否存在该学生
 * 不存在录入
 */
void input_student(struct student_info *head,char *file_path,char *config_path){
	struct student_info *new_node;
	struct student_info find_su;
	new_node = (struct student_info*)malloc(sizeof(struct student_info));
	printf("请输入学号：");
	scanf("%s",new_node->id);
	//已经存在
	if(find_student(head,new_node->id) == 0 || find_student_file(file_path,config_path,new_node->id,&find_su) == 0){
		free(new_node);
		printf("当前学生信息已经录入！\n");
		return;
	}
	printf("请输入性名：");
	scanf("%s",new_node->name);
	printf("请输入班级：");
	scanf("%s",new_node->class_name);
	new_node->next = head->next;
	head->next = new_node;
	//free(new_book);
}

/**
 * 查找学生信息
 * @param head 链表指针头
 * @param no 查找图书的id,进行文件查找不读取到内存中
 * @return int 0成功,1失败
 */
int find_student(struct student_info* head,char *id){
	//1、先从链表中读取信息
	struct student_info* p;
	p = head->next;
	while(p!=NULL){
		if(strcmp(p->id,id) == 0){
			return 0;
		}
		p = p->next;
	}
	return 1;
}

/**
* 从文件中查找是否存在当前学生
* @param no 图书id
*/
int find_file_student(char *file_path,char *no){

	return 0;
}


int get_student_list_size(struct student_info *head){
	struct student_info *p;
	int lenght = 0;
	p = head->next;
	if(p == NULL){
		return 0;
	}
	while(p != NULL){
		lenght++;
		p = p->next;
	}
	return lenght;
}

/**
 * 将学生信息写入到文件中
 * 完成创建的时候写入文件
 * @param head 头节点
 * @param file_path 文件位置
 */
void write_student(struct student_info *head,char *file_path){
	struct student_info *p;
	FILE *fp;
	p = head->next;
	fp = fopen(file_path,"ab+");
	if(!fp){
		printf("文件打开失败！\n");
		return;
	}
	while(p != NULL){
		fwrite(p,sizeof(struct student_info),1,fp);
		p = p->next;
	}
	fclose(fp);
}

/**
* 清空当前链表释放内存
*/
void clear_student_list(struct student_info *head){
	struct student_info *p;
	struct student_info *del;
	p = head->next;
	while(p!=NULL){
		del = p;
		p = del->next;
		free(del);
	}
	head->next = NULL;
}