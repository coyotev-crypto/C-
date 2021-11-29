/*
* ѧ����Ϣ����
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
 * ����ѧ������
 * У���Ƿ���ڸ�ѧ��
 * ������¼��
 */
void input_student(struct student_info *head,char *file_path,char *config_path){
	struct student_info *new_node;
	struct student_info find_su;
	new_node = (struct student_info*)malloc(sizeof(struct student_info));
	printf("������ѧ�ţ�");
	scanf("%s",new_node->id);
	//�Ѿ�����
	if(find_student(head,new_node->id) == 0 || find_student_file(file_path,config_path,new_node->id,&find_su) == 0){
		free(new_node);
		printf("��ǰѧ����Ϣ�Ѿ�¼�룡\n");
		return;
	}
	printf("������������");
	scanf("%s",new_node->name);
	printf("������༶��");
	scanf("%s",new_node->class_name);
	new_node->next = head->next;
	head->next = new_node;
	//free(new_book);
}

/**
 * ����ѧ����Ϣ
 * @param head ����ָ��ͷ
 * @param no ����ͼ���id,�����ļ����Ҳ���ȡ���ڴ���
 * @return int 0�ɹ�,1ʧ��
 */
int find_student(struct student_info* head,char *id){
	//1���ȴ������ж�ȡ��Ϣ
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
* ���ļ��в����Ƿ���ڵ�ǰѧ��
* @param no ͼ��id
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
 * ��ѧ����Ϣд�뵽�ļ���
 * ��ɴ�����ʱ��д���ļ�
 * @param head ͷ�ڵ�
 * @param file_path �ļ�λ��
 */
void write_student(struct student_info *head,char *file_path){
	struct student_info *p;
	FILE *fp;
	p = head->next;
	fp = fopen(file_path,"ab+");
	if(!fp){
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	while(p != NULL){
		fwrite(p,sizeof(struct student_info),1,fp);
		p = p->next;
	}
	fclose(fp);
}

/**
* ��յ�ǰ�����ͷ��ڴ�
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