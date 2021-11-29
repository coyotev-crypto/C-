#include "book_manage.h"
#include "common.h"


/**
����ͼ����Ϣ
*/
void input_book(struct book *head,char *file_path,char *config_path){
	struct book *new_book;
	struct book fb;
	new_book = (struct book*)malloc(sizeof(struct book));
	printf("������ͼ���ţ�");
	scanf("%s",new_book->no);
	//�Ѿ�����
	if(find_book(head,new_book->no) == 0 || find_book_file(file_path,config_path,new_book->no,&fb) == 0){
		free(new_book);
		printf("ͼ���Ѿ�¼�룡\n");
		return;
	}
	printf("������������");
	scanf("%s",new_book->book_name);
	printf("���������ߣ�");
	scanf("%s",new_book->author);
	printf("�������棺");
	scanf("%d",&new_book->reserve);
	new_book->next = head->next;
	head->next = new_book;
}


/**
 * ����ͼ����Ϣ
 * @param no ����ͼ���id,�����ļ����Ҳ���ȡ���ڴ���
 * @return int 1�ɹ�,0ʧ��
 */
int find_book(struct book* head,char *no){
	//1���ȴ������ж�ȡ��Ϣ
	struct book* p;
	p = head->next;
	while(p!=NULL){
		if(strcmp(p->no,no) == 0){
			return 0;
		}
		p = p->next;
	}
	return 1;
}

/**
 * ��ͼ����Ϣд�뵽�ļ���
 * ��ɴ�����ʱ��д���ļ�
 */
void write_book(struct book *head,char *file_path){
	struct book *p;
	FILE *fp;
	p = head->next;
	fp = fopen(file_path,"ab+");
	if(!fp){
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	while(p != NULL){
		fwrite(p,sizeof(struct book),1,fp);
		p = p->next;
	}
	fclose(fp);
}

/**
* ��յ�ǰ�����ͷ��ڴ�
*/
void clear_book_list(struct book *head){
	struct book *p;
	struct book *del;
	p = head->next;
	while(p!=NULL){
		del = p;
		p = del->next;
		free(del);
	}
	head->next = NULL;
}

int get_book_list_size(struct book *head){
	struct book *p;
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

/*
* д�������ļ�
*/
void write_manage_info(int type,int size,char *config_path){
	struct book_manage *node;
	struct book_manage *last_book_manage;
	long book_manage_sizeof;
	FILE *fp;
	book_manage_sizeof = sizeof(struct book_manage);
	node = (struct book_manage*)malloc(book_manage_sizeof);
	last_book_manage = (struct book_manage*)malloc(sizeof(struct book_manage));
	fp = fopen(config_path,"ab+");
	if(!fp){
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
    last_manage_info(last_book_manage,config_path);
	//��һ�δ����ļ�
	if(last_book_manage == NULL){
		node -> type = type;
		node->end_position=size;
		fwrite(node,book_manage_sizeof,1,fp);
	}else if(last_book_manage->type == type){ //У�����������Ƿ���ͬ
		fclose(fp);
		fp = fopen(config_path,"rb+");
		//�޸�����
		last_book_manage->end_position += size;
		//printf("�޸����ݣ�%d\t%d\t%d\t%d\n",type,last_book_manage->type,last_book_manage->start_position,last_book_manage->end_position);
		//����ԭ�ȵĽṹ������
		//1����λ�����һ���ṹ��
		fseek(fp,0,SEEK_END);
		fseek(fp,-book_manage_sizeof,SEEK_CUR);
		//2���޸�
		fwrite(last_book_manage,book_manage_sizeof,1,fp);
	}else{
		//��ͬ���͵���������
		node -> type = type;
		node->end_position=size;	
		fwrite(node,book_manage_sizeof,1,fp);
	}
	fclose(fp);
}


void last_manage_info(struct book_manage* last_book_manage,char *config_path){
	FILE *fp;
	long offset = 0;
	long book_manage_sizeof;
	book_manage_sizeof = sizeof(struct book_manage);
	fp = fopen(config_path,"rb");
	if(!fp){
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	//��λ���ļ�ĩβ
	fseek(fp,0,SEEK_END);
	offset = ftell(fp);
	//printf("��ǰλ�ã�%d",offset);
	if(offset > 0){
		//��������һ���ļ���ָ��λ��
		fseek(fp,-book_manage_sizeof,SEEK_CUR);
		fread(last_book_manage,book_manage_sizeof,1,fp);
		//printf("ͼ������:%d\t��ʼλ��:%d\t����λ��:%d\n",last_book_manage->type,last_book_manage->start_position,last_book_manage->end_position);
	}
	fclose(fp);
}

/*
* 1������ѧ��ѧ��
* 2��У����Ϣ�Ƿ����
* 3����������
* 4��У�����Ƿ����
* 5��У�鵱ǰ�Ƿ����鼮�ɽ���
* 6���鼮��Ϣ�޸�����д��
* 7�����һ�����ļ�¼
*/
void borrow_books(char *file_path,char *config_path){
	struct book find_book;
	struct borrowing_records *br;
	struct student_info su_info;
	br = (struct borrowing_records*) malloc(sizeof(struct borrowing_records));
	printf("������ѧ��ѧ�ţ�");
	scanf("%s",br->student_id);
	if(find_student_file(file_path,config_path,br->student_id,&su_info) != 0){
		printf("ѧ����Ϣ������\n");
		return;
	}
	printf("����������鼮��ţ�");
	scanf("%s",br->no);
	if(find_book_file(file_path,config_path,br->no,&find_book) != 0){
		printf("�鼮��Ϣ������\n");
		return;
	}
	if(find_book.reserve == 0){
		printf("û��ͼ��ɽ��ģ������ʱ������\n");
		return;
	}
	//д����ļ�¼
	write_borrow_books_count(file_path,config_path,br);
	write_manage_info(BORROWING_RECORDS_TYPE,1,config_path);
	//�޸�ͼ����Ϣ
	find_book.reserve--;
	change_book(file_path,config_path,&find_book);
	printf("���ĳɹ���\n");
}

void change_book(char *file_path,char *config_path,struct book *change_book){
	//1�����ҵ���ǰbook�ļ�λ��
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	struct book book;
	long book_size;
	book_size = sizeof(struct book);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("�ļ���ʧ�ܣ�\n");
	}
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(&book,book_size,1,fp);
				if(strcmp(book.no,change_book->no) == 0){ //�����鼮��Ϣ
					fseek(fp,-book_size,SEEK_CUR);
					fwrite(change_book,book_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
				}
			}
			continue;
		}else if(node.type == STUDENT_TYPE){
			//�ļ�ָ���ƶ�
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct student_info),SEEK_CUR);
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
		}
	}
	fclose(fp);
	fclose(cfp);
}

void write_borrow_books_count(char *file_path,char *config_path,struct borrowing_records *br){
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	int br_size;
	struct book_manage node;
	br_size = sizeof(struct borrowing_records);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return;
	}
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct book),SEEK_CUR);
			continue;
		}else if(node.type == STUDENT_TYPE){
			//�ļ�ָ���ƶ�
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct student_info),SEEK_CUR);
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(br,br_size,1,fp);
				if(strcmp(br->no,"-1") == 0 || strcmp(br->student_id,"-1") == 0){
					fseek(fp,-br_size,SEEK_CUR);
					fwrite(br,br_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
				}
			}
		}
	}
	fwrite(br,br_size,1,fp);
	fclose(fp);
	fclose(cfp);
}
/*
* �黹�鼮��Ϣ
* 1������ѧ����Ϣ
* 2������黹ͼ����
* 3�����ҽ��ļ�¼
* 4�����ļ�¼�޸�
* 5��ͼ����Ϣ�޸�
*/
void return_the_book(char *file_path,char *config_path){
	struct book find_book;
	struct borrowing_records *br;
	struct borrowing_records find_br;
	struct student_info su_info;
	br = (struct borrowing_records*) malloc(sizeof(struct borrowing_records));
	printf("������ѧ��ѧ�ţ�");
	scanf("%s",br->student_id);
	if(find_student_file(file_path,config_path,br->student_id,&su_info) != 0){
		printf("ѧ����Ϣ������\n");
		return;
	}
	printf("������黹�鼮��ţ�");
	scanf("%s",br->no);
	if(find_book_file(file_path,config_path,br->no,&find_book) != 0){
		printf("�鼮��Ϣ������\n");
		return;
	}
	//���ҽ��ļ�¼
	if(find_borrowing_records_file(file_path,config_path,br,&find_br) != 0){
		printf("�����ڽ��ļ�¼\n");
		return;
	}
	//�޸Ľ��ļ�¼
	change_borrow_books(file_path,config_path,&find_br);
	//�޸�ͼ����Ϣ
	find_book.reserve++;
	change_book(file_path,config_path,&find_book);
	printf("�黹�ɹ�\n");
}


void change_borrow_books(char *file_path,char *config_path,struct borrowing_records *br){
	//1�����ҵ���ǰ���ļ�¼�ļ�λ��
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	struct borrowing_records borrowing_record;
	long br_size;
	br_size = sizeof(struct borrowing_records);
	fp = fopen(file_path,"rb+");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("�ļ���ʧ�ܣ�\n");
	}
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct book),SEEK_CUR);
			continue;
		}else if(node.type == STUDENT_TYPE){
			//�ļ�ָ���ƶ�
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct student_info),SEEK_CUR);
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(&borrowing_record,br_size,1,fp);
				if(strcmp(borrowing_record.no,"-1") == 0 || strcmp(borrowing_record.student_id,"-1") == 0){
					continue;
				}
				if(strcmp(br->no,borrowing_record.no) == 0 && strcmp(br->student_id,borrowing_record.student_id) == 0){ //���ڽ�����Ϣ
					fseek(fp,-br_size,SEEK_CUR);
					//����ļ������渴��
					strcpy(br->no,"-1");
					strcpy(br->student_id,"-1");
					fwrite(br,br_size,1,fp);
					fclose(fp);
					fclose(cfp);
					return;
				}
			}
		}
	}
	fclose(fp);
	fclose(cfp);
}