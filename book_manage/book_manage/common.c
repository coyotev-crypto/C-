#include "common.h"

void menu(){
	printf("===============================\n");
    printf("��ӭʹ��ͼ�����ϵͳ\n");
    printf("1��¼���鼮��Ϣ\n");
	printf("2��¼��ѧ����Ϣ\n");
	printf("3���鿴¼���鼮��Ϣ\n");
	printf("4���鿴ѧ����Ϣ\n");
	printf("5�������鼮\n");
    printf("6���黹�鼮\n");
	printf("7�����ļ�¼\n");
	printf("0���˳�\n");
	printf("===============================\n");
}

/*
* ��ӡ������Ϣ
* @param file_path �����ļ���·��
* @param config_path �����ļ�·��
* @param operate_type �������� 0 �鼮,1ѧ����2������Ϣ
*/
int printf_file(char *file_path,char *config_path,int operate_type){
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	struct book book;
	struct student_info su_info;
	struct borrowing_records br;
	int is_first = 0;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		printf("�ļ���ʧ�ܣ�\n");
		return 2;
	}
	printf("\n");
	printf("==============================================================\n");
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&book,sizeof(struct book),1,fp);
						  /* data */
						 //   char no[5]; //���
						 //char book_name[128]; //����
						 //   char author[20]; //����
						 //   int reserve; //���
						 //   struct book *next;
						printf("��ţ�%s\t������%s\t���ߣ�%s\tʣ��ͼ�飺%d\n",book.no,book.book_name,book.author,book.reserve);
				}
			}else{
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct book),SEEK_CUR);
			}
			continue;
		}else if(node.type == STUDENT_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&su_info,sizeof(struct student_info),1,fp);
						//char id[11]; //ѧ��
						//char name[20]; //����
						//char class_name[128]; //�༶ 
						printf("ѧ�ţ�%s\t������%s\t�༶��%s\n",su_info.id,su_info.name,su_info.class_name);
				}
			}else{
			//�ļ�ָ���ƶ�
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct student_info),SEEK_CUR);
			}
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			if(node.type == operate_type){
				for(i = 0;i <node.end_position;i++){
					fread(&br,sizeof(struct borrowing_records),1,fp);
					if(strcmp(br.no,"-1") == 0 || strcmp(br.student_id,"-1")==0){
						continue;
					}
					find_book_file(file_path,config_path,br.no,&book);
					find_student_file(file_path,config_path,br.student_id,&su_info);
					if(is_first == 0){
						printf("ѧ�ţ�%s\t������%s\t�༶��%s\n",su_info.id,su_info.name,su_info.class_name);
						printf("�����鼮��\n");
						is_first=1;
					}
					printf("��ţ�%s\t������%s\t���ߣ�%s\n",book.no,book.book_name,book.author);
				}
			}else{
				//�ļ�ָ���ƶ�
				for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
			}
		}
	}
	printf("==============================================================\n");
	printf("\n");
	fclose(fp);
	fclose(cfp);
	return 1;
}


int find_student_file(char *file_path,char *config_path,char *des,struct student_info* su_info){
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
	}
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			for(i = 0;i<node.end_position;i++)
				fseek(fp,sizeof(struct book),SEEK_CUR);
			continue;
		}else if(node.type == STUDENT_TYPE){
			for(i = 0;i <node.end_position;i++){
					fread(su_info,sizeof(struct student_info),1,fp);
					if(strcmp(su_info->id,des) == 0){ //����ѧ����Ϣ
						fclose(fp);
						fclose(cfp);
						return 0;
					}
				}
			continue;
		}else if(node.type == BORROWING_RECORDS_TYPE){
			for(i = 0;i<node.end_position;i++)
					fseek(fp,sizeof(struct borrowing_records),SEEK_CUR);
		}
	}
	fclose(fp);
	fclose(cfp);
	return 1;
}


int find_book_file(char *file_path,char *config_path,char *des,struct book* book){
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
	}
	//��ȡ������Ϣ
	while((fread(&node,sizeof(struct book_manage),1,cfp)) == 1){
		//�鼮��Ϣ
		if(node.type == BOOK_TYPE){
			for(i = 0;i <node.end_position;i++){
				fread(book,sizeof(struct book),1,fp);
				if(strcmp(book->no,des) == 0){ //�����鼮��Ϣ
					fclose(fp);
					fclose(cfp);
					return 0;
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
	return 1;
}

int find_borrowing_records_file(char *file_path,char *config_path,struct borrowing_records *input_br,struct borrowing_records* br){
	FILE *fp;  //�洢���ݵ��ļ�ָ��
	FILE *cfp; //�洢�����ļ����ļ�ָ��
	int i;
	struct book_manage node;
	fp = fopen(file_path,"rb");
	cfp = fopen(config_path,"rb");
	if(!cfp || !fp){
		return 1;
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
				fread(br,sizeof(struct borrowing_records),1,fp);
				if(strcmp(br->no,"-1") == 0 || strcmp(br->student_id,"-1") == 0){
					continue;
				}
				if(strcmp(br->no,input_br->no) == 0 && strcmp(br->student_id,input_br->student_id) == 0){ //���ڽ�����Ϣ
					fclose(fp);
					fclose(cfp);
					return 0;
				}
			}
		}
	}
	fclose(fp);
	fclose(cfp);
	return 1;
}

void printf_book(char *file_path,char *config_path){
	 printf_file(file_path,config_path,BOOK_TYPE);
}


void printf_student(char *file_path,char *config_path){
	printf_file(file_path,config_path,STUDENT_TYPE);
}


void printf_borrowing_records(char *file_path,char *config_path){
	printf_file(file_path,config_path,BORROWING_RECORDS_TYPE);
}

void printf_config_info(char *config_path){
	struct book_manage book_manage;
	FILE *fp;
	fp = fopen(config_path,"ab+");
	if(!fp){
		printf("�ļ���ʧ�ܣ�\n");
		return;
	}
	while((fread(&book_manage,sizeof(struct book_manage),1,fp))==1){
		printf("����:%d\t����λ��:%d\n",book_manage.type,book_manage.end_position);
	}
	fclose(fp);
}